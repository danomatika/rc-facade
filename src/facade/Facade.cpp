#include "Facade.h"

Facade::Facade(std::string ip, unsigned int port) :
    _frame(ip, port), _currentRow(0), _currentCol(0)
{}

Facade::~Facade()
{
    //dtor
}

void Facade::clear()
{
    _frame.setColor(_background);

    _building.main_W.setColor(_frame, Color(0x000000));
    _building.main_S.setColor(_frame, Color(0x666666));
    _building.main_E.setColor(_frame, Color(0x222222));
    _building.main_N.setColor(_frame, Color(0x888888));
    _building.lab_S.setColor(_frame, Color(0x444444));
    _building.main_S_street.setColor(_frame, Color(0xAAAAAA));
}

void Facade::send()
{
    _frame.flush();
}

void Facade::pixel(unsigned int x, unsigned int y, Color color)
{
    std::vector<Side*>& sides = _building.getSides();
    for(unsigned int i = 0; i < sides.size(); ++i)
    {
        sides[i]->setWindowColor(_frame, y, x, color, true);
    }
}

void Facade::pixel(unsigned int x, unsigned int y, unsigned int color)
{
    pixel(x, y, Color(color));
}

void Facade::walkRow(Color color)
{
    std::vector<Side*>& sides = _building.getSides();
    for(unsigned int i = 0; i < sides.size(); ++i)
    {
        sides[i]->setRowColor(_frame, _currentRow, color, true);
    }

    _currentRow++;
    if(_currentRow > _building.getNrRows())
    {
        _currentRow = 0;
    }
}

void Facade::walkCol(Color color)
{
    std::vector<Side*>& sides = _building.getSides();
    for(unsigned int i = 0; i < sides.size(); ++i)
    {
        sides[i]->setColumnColor(_frame, _currentCol, color);
    }

    _currentCol++;
    if(_currentCol > _building.getNrCols())
    {
        _currentCol = 0;
    }
}

void Facade::walkWindows(Color color)
{
    std::vector<Side*>& sides = _building.getSides();
    for(unsigned int i = 0; i < sides.size(); ++i)
    {
        sides[i]->setWindowColor(_frame,  _currentRow, _currentCol, color, true);
    }

    _currentCol++;
    if(_currentCol > _building.getNrCols())
    {
        _currentCol = 0;

        _currentRow++;
        if(_currentRow > _building.getNrRows())
        {
            _currentRow = 0;
        }
    }
}

void Facade::draw(int x, int y)
{
    /*
    _building.main_W.draw(_frame, x, y);
    _building.main_S.draw(_frame, x+150, y+5);
    _building.main_E.draw(_frame, x+150*2, y+5);
    _building.main_N.draw(_frame, x+150*3, y);
    _building.lab_S.draw(_frame, x+150, y+80+5);
    _building.main_S_street.draw(_frame, x+150, y+110+5);
*/
    std::vector<Side*>& sides = _building.getSides();
    for(unsigned int i = 0; i < sides.size(); ++i)
    {
        sides[i]->draw(_frame, x, y, true);
    }

    //_building.main_S.draw(_frame, x+150, y+5+200);
    //_building.main_S_street.draw(_frame, x+150, y+110+5+200);
    //_building.lab_S.draw(_frame, x+150*2, y+80+5+200);
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
            Graphics::rectangle(xPos, yPos, Side::getWindowSize()*3, Side::getWindowSize(), Graphics::CORNER);

            xPos += Side::getWindowSize()*3;
        }
        xPos = x;
        yPos += Side::getWindowSize();
    }
}

void Facade::setBackground(unsigned int color)
{
    _background.set(color);
}
