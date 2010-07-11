/*==============================================================================

	Facade.cpp
    
    libfacade: a 2d framebuffer for the Ars Electronica Facade

    Copyright (c) 2009, 2010 Dan Wilcox <danomatika@gmail.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
    
==============================================================================*/
#include "Facade.h"

#include <cassert>

#include "Building.h"

// alpha blend from http://www.codeguru.com/cpp/cpp/algorithms/general/article.php/c15989
// src, det, alpha
#define AlphaBlend(S,D,A) ((S*A)+(D*(255-A)))/255

namespace facade {

// local class variables
FrameBuffer _frame;     /// facade framebuffer
Building _building;     /// building address mapping

Facade::Facade() :
	_pixels(NULL), _mask(NULL),
	_clearColor(0xFF000000),
    _bWrapX(true), _bWrapY(true), _bBlend(false),
    _bRectCenter(false), _bRectFill(false),
    _pixelLen(0)
{
	setup();
}

Facade::~Facade()
{
    if(_pixels)
    	delete [] _pixels;
    if(_mask)
    	delete [] _mask;
}

void Facade::setClearColor(uint32_t color)
{
    _clearColor = color;
}

void Facade::clear()
{        
    bool blend = _bBlend;
    _bBlend = true;
    
    // clear the pixel framebuffer
    for(unsigned int x = 0; x < _building.getNrCols(); ++x)
    {
    	for(unsigned int y = 0; y < _building.getNrRows(); ++y)
    	{
            setPixel(x, y, _clearColor);  
        }
    }
    
    _bBlend = blend;
}

void Facade::swap()
{
	std::vector<Side*>& sides = _building.getSides();
    for(unsigned int x = 0; x < _building.getNrCols(); ++x)
    {
    	for(unsigned int y = 0; y < _building.getNrRows(); ++y)
        {
        	// don't bother if the pixel is not within the mask
        	if(_mask[y*_building.getNrCols()+x] != 0)
            {
                for(unsigned int i = 0; i < sides.size(); ++i)
                {
                    sides[i]->setWindow(_frame, y, x, _pixels[y*_building.getNrCols()+x], true);
                }
            }
        }
    }
}

/* ***** RAW PACKET ACCESS ***** */

const uint8_t* Facade::getPacket() const
{
	return _frame.getFramebuffer();
}

unsigned int Facade::getPacketLen()
{
	return _frame.getFramebufferLen();
}

void Facade::setPacket(const uint8_t* packet)
{
	assert(packet);	// shouldn't be null
    
	_frame.setFramebuffer(packet);

	// draw the facade framebuffer onto the pixel framebuffer
    std::vector<Side*>& sides = _building.getSides();
    for(unsigned int i = 0; i < sides.size(); ++i)
    {
        sides[i]->draw(_pixels, _building, _frame);
    }
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
	setup();
}

/* ***** PIXEL FRAME BUFFER ***** */
        
const uint32_t* Facade::getFrameBuffer() const
{
	return _pixels;
}

const uint32_t* Facade::getMask() const
{
	return _mask;
}
        
void Facade::setFrameBuffer(const uint32_t* pixels)
{
	assert(pixels);	// shouldn't be null
    
	try
    {
    	memcpy(_pixels, pixels, _pixelLen);
    }
    catch(std::exception& e)
    {
        std::cerr << "Facade::setFrameBuffer: error: " << e.what() << std::endl;
    }
}

uint32_t Facade::getPixel(unsigned int x, unsigned int y)
{
	if(x >= _building.getNrCols() || y >= _building.getNrRows())
    {
    	std::cerr << "Facade::getPixel: warning, point (" << x << "," << y << ") out of bounds" << std::endl;
    	return 0;
    }
    
    return _pixels[y*_building.getNrCols()+x];
}


uint32_t Facade::getSidePixel(FacadeSide side, unsigned int x, unsigned int y)
{
	Side* s = _building.getSides().at((int) side);
    if(!s->isEnabled() || s->getAddress(x, y) == -1)
    	return 0;
        
    x += s->getStartCol();
    y += s->getStartRow();
    return getPixel(x, y);
}

/* ***** GRAPHICS PRIMITIVES ***** */

void Facade::pixel(int x, int y)
{
    int xPos = x, yPos = y;

    if(_bWrapX)
    {
        if(x >= (int) _building.getNrCols())
            x = x - _building.getNrCols();
        else if(x < 0)
            xPos = _building.getNrCols() - x;
    }
    if(_bWrapY)
    {
        if(y >= (int) _building.getNrRows())
            y = y - _building.getNrRows();
        else if(y < 0)
            yPos = _building.getNrRows() - y;
    }
	
    setPixel(xPos, yPos, _drawColor);    
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

void Facade::rect(int x, int y, int w, int h)
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

void Facade::circle(int x, int y, int r)
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

/* ***** SIDE GRAPHICS ***** */

void Facade::sideColor(FacadeSide side)
{
    _building.getSides().at((int) side)->draw(_pixels, _building, _drawColor);
}

void Facade::sideRow(FacadeSide side, int row)
{
    _building.getSides().at((int) side)->drawRow(_pixels, _building, row, _drawColor);
}

void Facade::sideCol(FacadeSide side, int col)
{
    _building.getSides().at((int) side)->drawCol(_pixels, _building, col, _drawColor);
}

void Facade::sidePixel(FacadeSide side, int x, int y)
{
    _building.getSides().at((int) side)->drawWindow(_pixels, _building, y, x, _drawColor);
}

/* **** UTIL ***** */

void Facade::print()	{_building.print();}

unsigned int Facade::getWidth() 	{return _building.getNrCols();}
unsigned int Facade::getHeight()	{return _building.getNrRows();}

unsigned int Facade::getSideWidth(FacadeSide side)
	{return _building.getSides().at((int) side)->getNrCols();}
    
unsigned int Facade::getSideHeight(FacadeSide side)
	{return _building.getSides().at((int) side)->getNrRows();}

unsigned int Facade::getSidePosX(FacadeSide side)
	{return _building.getSides().at((int) side)->getStartCol();}
    
unsigned int Facade::getSidePosY(FacadeSide side)
	{return _building.getSides().at((int) side)->getStartRow();}

/* ***** PRIVATE ***** */

void Facade::setup()
{
	// new length
    _pixelLen = _building.getNrCols()*_building.getNrRows();
    
    // reallocate pixels
    if(_pixels)
    	delete [] _pixels;
    _pixels = new uint32_t[_pixelLen];
    clear();
    
    // reallocate maks
    if(_mask)
    	delete [] _mask;
    _mask = new uint32_t[_pixelLen];
    
    // rebuild mask
    for(unsigned int p = 0; p < _pixelLen; ++p)
        	_mask[p] = 0;	// clear pixels with black
    _building.main_N.draw(_mask, _building, 0xFFFF0000);
    _building.main_E.draw(_mask, _building, 0xFFFF00FF);
    _building.main_S.draw(_mask, _building, 0xFF00FF00);
    _building.main_S_street.draw(_mask, _building, 0xFF00FFFF);
    _building.main_W.draw(_mask, _building, 0xFFFFFF00);

    _building.lab_N.draw(_mask, _building, 0xFF666666);
    _building.lab_E.draw(_mask, _building, 0xFF999999);
    _building.lab_S.draw(_mask, _building, 0xFF0000FF);
}

void Facade::setPixel(unsigned int x, unsigned int y, uint32_t color)
{
	uint8_t alpha = (color >> 24) & 0xFF;
    if(_bBlend && alpha < 255)
    {
    	uint32_t pixel = _pixels[y*getWidth() + x];
    	uint8_t r = (color >> 16) & 0xFF;
        uint8_t g = (color >> 8) & 0xFF;
        uint8_t b = (color) & 0xFF;
        
        uint8_t r2 = (pixel >> 16) & 0xFF;
        uint8_t g2 = (pixel >> 8) & 0xFF;
        uint8_t b2 = (pixel) & 0xFF;
        
        _pixels[y*getWidth() + x] = 0xFF << 24 |
        	AlphaBlend(r, r2, alpha) << 16 |
        	AlphaBlend(g, g2, alpha) << 8 |
        	AlphaBlend(b, b2, alpha);
    }
    else
    {
    	_pixels[y*getWidth() + x] = color;    
    }
}

} // facade
