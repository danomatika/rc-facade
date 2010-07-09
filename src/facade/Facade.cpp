/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#include "Facade.h"

#include "Building.h"

using namespace visual;

// local class variables
FrameBuffer _frame;     /// facade framebuffer
Building _building;     /// building address mapping

Facade::Facade() :
	_pixels(NULL), _width(0), _height(0),
	_clearColor(0xFF000000), _drawColor(0xFFFFFFFF),
    _bWrapX(true), _bWrapY(true), _bShowSides(false), _bBlend(false),
    _bRectCenter(false), _bRectFill(false)
{}

Facade::Facade(std::string ip, unsigned int port) :
	_pixels(NULL), _width(0), _height(0),
    _clearColor(0xFF000000), _drawColor(0xFFFFFFFF),
    _bWrapX(true), _bWrapY(false), _bShowSides(false), _bBlend(false),
    _bRectCenter(false), _bRectFill(false)
{
    //setup(ip, port);
}

Facade::~Facade()
{
    if(_pixels != NULL)
    	delete [] _pixels;
}

void Facade::setup(std::string ip, unsigned int port)
{
    _frame.setup(ip, port);
    _width = _building.getNrCols();
    _height = _building.getNrRows();
    
    if(_pixels != NULL)
    	delete [] _pixels;
    _pixels = new uint8_t[_width*_height];
    
    memset(_pixels, 0, _width*_height);
}

void Facade::clear()
{
    if(_bShowSides)
    {
        _building.main_N.setColor(_frame, 0x66990000);
        _building.main_E.setColor(_frame, 0x66990099);
        _building.main_S.setColor(_frame, 0x66009900);
        _building.main_S_street.setColor(_frame, 0x66009999);
        _building.main_W.setColor(_frame, 0x66999900);

        _building.lab_N.setColor(_frame, 0x66000099);
        _building.lab_E.setColor(_frame, 0x66999999);
        _building.lab_S.setColor(_frame, 0x66666666);

    }
    else
        _frame.clear(_clearColor);
        
	memset(_pixels, _clearColor, _width*_height);
}

void Facade::send()
{
	/*
	for(unsigned int x = 0; x < _width; ++x)
    {
    	for(unsigned int y = 0; y < _height; ++y)
        {
        	uint32_t color = _pixels[y*_width+x];
            std::vector<Side*>& sides = _building.getSides();
            for(unsigned int i = 0; i < sides.size(); ++i)
            {
                sides[i]->setWindowColor(_frame, y, x, color, true);
            }
        }
    }
    */
    _frame.flush();
}

/* ***** SIDE SETTINGS ***** */

void Facade::setSidePos(FacadeSide side, int x, int y)
{
    _building.getSides().at((int) side)->setPos(y, x);
}

void Facade::moveSide(FacadeSide side, int xAmount, int yAmount)
{
	_building.getSides().at((int) side)->move(yAmount, xAmount);
}

void Facade::moveSides(int xAmount, int yAmount)
{
	std::vector<Side*>& sides = _building.getSides();
    for(unsigned int i = 0; i < sides.size(); ++i)
    {
        sides[i]->move(yAmount, xAmount);
    }
}

void Facade::enableSide(FacadeSide side, bool enabled)
{
    _building.getSides().at((int) side)->enable(enabled);
}

void Facade::flipSide(FacadeSide side, bool flipX, bool flipY)
{
    _building.getSides().at((int) side)->flipX(flipX);
    _building.getSides().at((int) side)->flipY(flipY);
}

void Facade::recomputeSize()
{
    _building.computeSize();
}

/* ***** SIDE GRAPHICS ***** */

void Facade::sideColor(FacadeSide side)
{
    _building.getSides().at((int) side)->setColor(_frame, _drawColor);
}

void Facade::sideRow(FacadeSide side, int row)
{
    _building.getSides().at((int) side)->setRowColor(_frame, row, _drawColor);
}

void Facade::sideCol(FacadeSide side, int col)
{
    _building.getSides().at((int) side)->setColColor(_frame, col, _drawColor);
}

void Facade::sidePixel(FacadeSide side, int x, int y)
{
    _building.getSides().at((int) side)->setWindowColor(_frame, y, x, _drawColor);
}

//uint32_t Facade::getSidePixel(FacadeSide side, int x, int y)
//{}
/*
uint32_t Facade::getPixel(int x, int y)
{
	return _frame.getColor(
}
*/
/* ***** BUILDING GRAPHICS ***** */

void blend()	{_frame.blend(true);}
void noBlend()	{_frame.blend(false);}

void Facade::pixel(int x, int y)
{
    int xPos = x, yPos = y;

    if(_bWrapX)
    {
        if(x >= _building.getNrCols())
            x = x - _building.getNrCols();
        else if(x < 0)
            xPos = _building.getNrCols() - x;
    }
    if(_bWrapY)
    {
        if(y >= _building.getNrRows())
            y = y - _building.getNrRows();
        else if(y < 0)
            yPos = _building.getNrRows() - y;
    }

	
    std::vector<Side*>& sides = _building.getSides();
    for(unsigned int i = 0; i < sides.size(); ++i)
    {
        sides[i]->setWindowColor(_frame, y, x, _drawColor, true);
    }
    
    //_pixels[x+y*_width] = _drawColor;
}

/* an improved Bresenham line drawing alogrithm
   from http://www.cs.unc.edu/~mcmillan/comp136/Lecture6/Lines.html */
void Facade::line(int x1, int y1, int x2, int y2)
{
    int dy = y2 - y1;
    int dx = x2 - x1;
    int stepx, stepy;

    if(dy < 0) {dy = -dy;  stepy = -1;} else {stepy = 1;}
    if(dx < 0) {dx = -dx;  stepx = -1;} else {stepx = 1;}
    dy <<= 1;                                                  // dy is now 2*dy
    dx <<= 1;                                                  // dx is now 2*dx

    pixel(x1, y1);
    if(dx > dy)
    {
        int fraction = dy - (dx >> 1);                         // same as 2*dy - dx
        while(x1 != x2)
        {
            if(fraction >= 0)
            {
                y1 += stepy;
                fraction -= dx;                                // same as fraction -= 2*dx
            }
            x1 += stepx;
            fraction += dy;                                    // same as fraction -= 2*dy
            pixel(x1, y1);
        }
    }
    else
    {
        int fraction = dx - (dy >> 1);
        while(y1 != y2)
        {
            if(fraction >= 0)
            {
                x1 += stepx;
                fraction -= dy;
            }
            y1 += stepy;
            fraction += dx;
            pixel(x1, y1);
        }
    }
}

void Facade::rect(int x, int y, int w, int h)//, bool drawFromCenter)
{
	if(_bRectFill)
    {
    	// box
        if(_bRectCenter)
        {
            for(int _y = y-h/2; _y < y+h/2; ++_y)
                line(x-w/2, _y, x+w/2-1, _y);
        }
        else
        {
            for(int _y = y; _y < y+h; _y++)
                line(x, _y, x+w-1, _y);
        }
    }
    else
    {
    	// rect
        if(_bRectCenter)
        {
            line(x-w/2, y-h/2, x+w/2-1, y-h/2);
            line(x-w/2, y-h/2, x-w/2, y+h/2-1);
            line(x+w/2-1, y+h/2-1, x-w/2, y+h/2-1);
            line(x+w/2-1, y+h/2-1, x+w/2-1, y-h/2);
        }
        else
        {
            line(x, y, x+w-1, y);
            line(x, y, x, y+h-1);
            line(x+w-1, y, x+w-1, y+h-1);
            line(x, y+h-1, x+w-1, y+h-1);
        }
    }
}
/*
void Facade::box(int x, int y, int w, int h, bool drawFromCenter)
{
    if(drawFromCenter)
    {
        for(int _y = y-h/2; _y < y+h/2; ++_y)
            line(x-w/2, _y, x+w/2-1, _y);
    }
    else
    {
        for(int _y = y; _y < y+h; _y++)
            line(x, _y, x+w-1, _y);
    }
}
*/
void Facade::circle(int x, int y, int r)//, uint32_t color)
{
    int f = 1 - r;
    int ddF_x = 0;
    int ddF_y = -2 * r;
    int _x = 0;
    int _y = r;

    pixel(x, y + r);
    pixel(x, y - r);
    pixel(x + r, y);
    pixel(x - r, y);

    while(_x < _y)
    {
        if(f >= 0)
        {
            _y--;
            ddF_y += 2;
            f += ddF_y;
        }
        _x++;
        ddF_x += 2;
        f += ddF_x + 1;
        pixel(x + _x, y + _y);
        pixel(x - _x, y + _y);
        pixel(x + _x, y - _y);
        pixel(x - _x, y - _y);
        pixel(x + _y, y + _x);
        pixel(x - _y, y + _x);
        pixel(x + _y, y - _x);
        pixel(x - _y, y - _x);
    }
}

void Facade::draw(int x, int y, bool debug)
{
    std::vector<Side*>& sides = _building.getSides();
    for(unsigned int i = 0; i < sides.size(); ++i)
    {
        sides[i]->draw(_frame, x, y, true);
    }
    
    if(debug)
    	drawGrid(x, y);
}

void Facade::drawGrid(int x, int y)
{
    int xPos = x, yPos = y;

    for(int r = 0; r < _building.getNrRows(); ++r)
    {
        for(int c = 0; c < _building.getNrCols(); ++c)
        {
           // if(r == _currentRow && c == _currentCol-1)
           //     Graphics::fill(0x00FFFF);
          //  else
                Graphics::noFill();
            Graphics::stroke(Side::getOutlineColor());
            Graphics::rectangle(xPos, yPos, Side::getWindowSize()*FACADE_WIN_ASPECT_WIDTH, Side::getWindowSize());

            xPos += Side::getWindowSize()*FACADE_WIN_ASPECT_WIDTH;
        }
        xPos = x;
        yPos += Side::getWindowSize();
    }
}

void Facade::setClearColor(uint32_t color)
{
    _clearColor = color;
    printf("background now 0x%x ", _clearColor);
}
/*
void Facade::setClearColor(unsigned int color)
{
    _clearColor.set(color);
}
*/
void Facade::print()    {_building.print();}

//unsigned int Facade::getWidth()  {return _width;}
//unsigned int Facade::getHeight() {return _height;}

void Facade::setWindowSize(unsigned int size)   {Side::setWindowSize(size);}
void Facade::drawOutlines(bool yesno)           {Side::drawOutlines(yesno);}
void Facade::drawOutlines()                     {Side::drawOutlines();}
void Facade::setOutlineColor(uint32_t color)    {Side::setOutlineColor(color);}
//void Facade::setOutlineColor(unsigned int color) {Side::setOutlineColor(color);}

unsigned int Facade::getSideWidth(FacadeSide side) {return _building.getSides().at((int) side)->getNrCols();}
unsigned int Facade::getSideHeight(FacadeSide side) {return _building.getSides().at((int) side)->getNrRows();}

unsigned int Facade::getSidePosX(FacadeSide side) {return _building.getSides().at((int) side)->getStartCol();}
unsigned int Facade::getSidePosY(FacadeSide side) {return _building.getSides().at((int) side)->getStartRow();}
