#include "Side.h"

unsigned int Side::_windowSize = 5;
bool Side::_bDrawOutlines = true;
Color Side::_outlineColor(0x999999);

int Side::getAddress(int row, int col, bool global)
{
    if(global)  // grab address in relation to buildings overall grid
    {
        if(row >= startRow && row <= endRow)
        {
            if(col >= startCol && col <= endCol)
            {
                return windowAddrs[((row-startRow)*nrCols) + (col-startCol)];
            }
        }
    }
    else    // grab address relative to this window's grid
    {
        if(row >= 0 && row < nrRows)
        {
            if(col >= 0 && col < nrCols)
            {
                return windowAddrs[((row)*nrCols) + col];
            }
        }
    }

    return -1;
}

/**
 * set side to a particular color
 */
void Side::setColor(FrameBuffer& frame, Color color)
{
    for(int address = getStartAddress(); address <= getEndAddress(); ++address)
    {
        frame.setColor(address, color);
    }
}

/**
 * set row of side to a particular color
 */
void Side::setRowColor(FrameBuffer& frame, int row, Color color, bool global)
{
    if(row >= getStartRow() && row <= getEndRow())
    {
        for(int column = 0; column <= getEndCol(); ++column)
        {
            frame.setColor(getAddress(row, column, global), color);
        }
    }
}

/**
 * set column of side to a particular color
 */
void Side::setColumnColor(FrameBuffer& frame, int column, Color color, bool global)
{
    if(column >= 0 && column < getNrCols())
    {
        for(int row = getStartRow(); row <= getEndRow(); ++row)
        {
            frame.setColor(getAddress(row, column, global), color);
        }
    }
}

/**
 * set window at row/column to particular color.
 * do nothing, if there is no window at that position.
 */
void Side::setWindowColor(FrameBuffer& frame, int row, int column, Color color, bool global)
{
    frame.setColor(getAddress(row, column, global), color);
}

/// print the side addresses graphically to LOG
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
    int xStart, xPos = x, yPos = y;

    if(global)
    {
        xPos = x + (startCol*_windowSize*3);
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
                    Graphics::stroke(_outlineColor);
                }
                Graphics::rectangle(xPos, yPos, _windowSize*3, _windowSize, Graphics::CORNER);
            }

            xPos += _windowSize*3;
        }
        xPos = xStart;
        yPos += _windowSize;
    }
}

