/*==============================================================================

Side.cpp

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
#include "Side.h"

#include <iostream>

#include "Building.h"

namespace facade {

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

void Side::move(int rowAmount, int colAmount)
{
	setPos(startRow+rowAmount, startCol+colAmount);
}

void Side::reset()
{
	bEnabled = true;
	bFlipX = false;
	bFlipY = false;
	setPos(c_startRow, c_startCol);
}

int Side::getAddress(int row, int col, bool global)
{
	if(global) // grab address in relation to building's overall grid
	{
		if((row >= startRow && row <= endRow) &&
		   (col >= startCol && col <= endCol))
		{
			int r = row-startRow, c = col-startCol;
			if(bFlipY)
				r = endRow-row;
			if(bFlipX)
				c = endCol-col;
			return windowAddrs[(r*nrCols) + c];
		}
	}
	else // grab address relative to this window's grid
	{
		if((row >= 0 && row <= nrRows) && (col >= 0 && col <= nrCols))
		{
			int r = row, c = col;
			if(bFlipY)
				r = nrRows-row-1;
			if(bFlipX)
				c = nrCols-col-1;
			return windowAddrs[(r*nrCols) + c];
		}
	}

	return -1;
}

/* ***** FRAME BUFFER DRAWING ***** */

void Side::set(FrameBuffer& frame, uint32_t color)
{
	if(!bEnabled)
		return;

	for(int address = getStartAddress(); address <= getEndAddress(); ++address)
	{
		frame.setColor(address, color);
	}
}

void Side::setRow(FrameBuffer& frame, int row, uint32_t color, bool global)
{
	if(!bEnabled)
		return;

	if(row >= startRow && row <= endRow)
	{
		for(int col = 0; col <= endCol; ++col)
		{
			frame.setColor(getAddress(row, col), color);
		}
	}
}

void Side::setCol(FrameBuffer& frame, int col, uint32_t color, bool global)
{
	if(!bEnabled)
		return;

	if(col >= startCol && col <= endCol)
	{
		for(int row = startRow; row <= endRow; ++row)
		{
			frame.setColor(getAddress(row, col), color);
		}
	}
}

void Side::setWindow(FrameBuffer& frame, int row, int col, uint32_t color, bool global)
{
	if(!bEnabled)
		return;
		frame.setColor(getAddress(row, col, global), color);
}

/* ***** PIXEL BUFFER DRAWING ***** */

void Side::draw(uint32_t* pixels, Building& building, FrameBuffer& frame)
{
	if(!bEnabled)
		return;

	int xPos = startCol;
	int yPos = startRow;
	int xStart = xPos;

	for(int r = 0; r < nrRows; ++r)
	{
		for(int c = 0; c < nrCols; ++c)
		{            
			if(getAddress(r, c) != -1)
			{
				pixels[yPos*building.getNrCols()+xPos] = frame.getColor(getAddress(r, c));
			}
			++xPos;
		}
		xPos = xStart;
		++yPos;
	}
}

void Side::draw(uint32_t* pixels, Building& building, uint32_t color, bool drawEmpty)
{
	if(!bEnabled)
		return;

	int xPos = startCol;
	int yPos = startRow;
	int xStart = xPos;

	for(int r = 0; r < nrRows; ++r)
	{
		for(int c = 0; c < nrCols; ++c)
		{
			if(xPos >= 0 && yPos >= 0)
			{
				if(getAddress(r, c) != -1)
					pixels[yPos*building.getNrCols()+xPos] = color;
					
				else if(drawEmpty)	// set the empty color?
					pixels[yPos*building.getNrCols()+xPos] = 0x00000000;
			}
			
			++xPos;
		}
		xPos = xStart;
		++yPos;
	}
}

void Side::drawRow(uint32_t* pixels, Building& building, unsigned int row, uint32_t color)
{
	if(!bEnabled)
		return;
		
	if(row >= 0 && row < (unsigned int) nrRows)
	{
		for(int col = 0; col < nrCols; ++col)
		{
			if(getAddress(row, col) != -1)
				pixels[(row+startRow)*building.getNrCols()+(col+startCol)] = color;
		}
	}
}

void Side::drawCol(uint32_t* pixels, Building& building, unsigned int col, uint32_t color)
{
	if(!bEnabled)
		return;
		
	if(col >= 0 && col < (unsigned int) nrCols)
	{
		for(int row = 0; row < nrRows; ++row)
		{
			if(getAddress(row, col) != -1)
				pixels[(row+startRow)*building.getNrCols()+(col+startCol)] = color;
		}
	}
}

void Side::drawWindow(uint32_t* pixels, Building& building, unsigned int row, unsigned int col, uint32_t color)
{
	if(!bEnabled)
		return;
	
	if(getAddress(row, col) != -1)
		pixels[(row+startRow)*building.getNrCols()+(col+startCol)] = color;   
}

/* ***** UTIL ***** */
		
void Side::print()
{
	for(int r = 0; r < nrRows; ++r)
	{
		std::cout << "    ";

		for(int c = 0; c < nrCols; ++c)
		{
			int addr = getAddress(r, c);
			if(addr < 0)
				std::cout << "  -1 ";
			else if(addr < 10)
				std::cout << "   " << addr << " ";
			else if(addr < 100)
				std::cout << "  " << addr << " ";
			else if(addr < 1000)
				std::cout << " " << addr << " ";
			else
				std::cout << addr << " ";
		}
		std::cout << std::endl;
	}
}

} // namespace