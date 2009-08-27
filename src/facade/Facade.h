#ifndef FACADE_H
#define FACADE_H

#include "Building.h"

class Facade
{
    public:

        Facade(std::string ip, unsigned int port=8080);
        virtual ~Facade();

        void clear();

        void send();

        void pixel(unsigned int x, unsigned int y, Color color);
        void pixel(unsigned int x, unsigned int y, unsigned int color);
        void walkRow(Color color);
        void walkCol(Color color);
        void walkWindows(Color color);

        void draw(int x, int y);
        void drawGrid(int x, int y);

        void setBackground(unsigned int color);

        void print()    {_building.print();}

        void setWindowSize(unsigned int size)    {Side::setWindowSize(size);}
        void drawOutlines(bool yesno)        {Side::drawOutlines(yesno);}
        void drawOutlines()                  {Side::drawOutlines();}
        void setOutlineColor(Color color)   {Side::setOutlineColor(color);}
        void setOutlineColor(unsigned int color) {Side::setOutlineColor(color);}

    private:

        Color _background;
        FrameBuffer _frame;
        Building _building;

        int _currentRow, _currentCol;
};

#endif // FACADE_H
