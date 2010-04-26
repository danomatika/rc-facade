/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#include "Side.h"

using namespace visual;

unsigned int Side::_windowSize = 5;
bool Side::_bDrawOutlines = true;
Color Side::_outlineColor(0x666666);

Side::~Side()
{
    if(windowAddrs != NULL)
        delete windowAddrs;
}

void Side::setPos(int row, int column)
{
    startRow = row;
    endRow = row+nrRows-1;

    startCol = column;
    endCol = column+nrCols-1;
}

int Side::getAddress(int row, int col, bool global)
{
    if(!bEnabled)
        return -1;

    if(global)  // grab address in relation to building's overall grid
    {
        if(row >= startRow && row <= endRow)
        {
            if(col >= startCol && col <= endCol)
            {
                int r = row-startRow, c = col-startCol;
                if(bFlipY)
                    r = endRow-row;
                if(bFlipX)
                    c = endCol-col;
                return windowAddrs[(r*nrCols) + c];
            }
        }
    }
    else    // grab address relative to this window's grid
    {
        if(row >= 0 && row < nrRows)
        {
            if(col >= 0 && col < nrCols)
            {
                int r = row, c = col;
                if(bFlipY)
                    r = nrRows-row-1;
                if(bFlipX)
                    c = nrCols-col-1;
                return windowAddrs[(r*nrCols) + c];
            }
        }
    }

    return -1;
}

void Side::setColor(FrameBuffer& frame, Color color)
{
    if(!bEnabled)
        return;

    for(int address = getStartAddress(); address <= getEndAddress(); ++address)
    {
        frame.setColor(address, color);
    }
}

void Side::setRowColor(FrameBuffer& frame, int row, Color color, bool global)
{
    if(!bEnabled)
        return;

    if(row >= getStartRow() && row <= getEndRow())
    {
        for(int column = 0; column <= getEndCol(); ++column)
        {
            frame.setColor(getAddress(row, column, global), color);
        }
    }
}

void Side::setColColor(FrameBuffer& frame, int column, Color color, bool global)
{
    if(!bEnabled)
        return;

    if(column >= 0 && column < getNrCols())
    {
        for(int row = getStartRow(); row <= getEndRow(); ++row)
        {
            frame.setColor(getAddress(row, column, global), color);
        }
    }
}

void Side::setWindowColor(FrameBuffer& frame, int row, int column, Color color, bool global)
{
    if(!bEnabled)
        return;

    frame.setColor(getAddress(row, column, global), color);
}

void Side::print()
{
    for(int r = 0; r < nrRows; ++r)
    {
        LOG << "    ";

        for(int c = 0; c < nrCols; ++c)
        {
            int addr = getAddress(r, c);
            if(addr < 0)
                LOG << "  -1 ";
            else if(addr < 10)
                LOG << "   " << addr << " ";
            else if(addr < 100)
                LOG << "  " << addr << " ";
            else if(addr < 1000)
                LOG << " " << addr << " ";
            else
                LOG << addr << " ";
        }
        LOG << std::endl;
    }
}

void Side::draw(FrameBuffer& frame, int x, int y, bool global)
{
    if(!bEnabled)
        return;

    int xStart, xPos = x, yPos = y;

    if(global)
    {
        xPos = x + (startCol*_windowSize*FACADE_WIN_ASPECT_WIDTH);
        yPos = y + (startRow*_windowSize);
    }
    xStart = xPos;

    if(!_bDrawOutlines)
        Graphics::noStroke();

    for(int r = 0; r < nrRows; ++r)
    {
        for(int c = 0; c < nrCols; ++c)
        {
            int addr = getAddress(r, c);
            if(addr != -1)
            {
                Color color = frame.getColor(addr);

                Graphics::fill(color);
                if(_bDrawOutlines)
                {
                    visual::Graphics::stroke(_outlineColor);
                }
                visual::Graphics::rectangle(xPos, yPos, _windowSize*FACADE_WIN_ASPECT_WIDTH-1, _windowSize-1);
            }

            xPos += _windowSize*FACADE_WIN_ASPECT_WIDTH;
        }
        xPos = xStart;
        yPos += _windowSize;
    }
}

