/*==============================================================================

	Side.h
    
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
#ifndef FACADE_SIDE_H
#define FACADE_SIDE_H

#include <string>

#include "FrameBuffer.h"

#define FACADE_WIN_ASPECT_WIDTH 3

namespace facade {

class Building;

/**
    abstract base class for building sides, initialized in derived
    classes to represent a certain side.
**/
class Side
{
    public:

        Side() : bFlipX(false), bFlipY(false), bEnabled(true) {}
        virtual ~Side();

        inline std::string getName()    {return name;}
        inline int getStartAddress()    {return startAddr;}
        inline int getEndAddress()      {return endAddr;}
        inline int getNrRows()          {return nrRows;}
        inline int getNrCols()          {return nrCols;}
        inline int getStartRow()        {return startRow;}
        inline int getEndRow()          {return endRow;}
        inline int getStartCol()        {return startCol;}
        inline int getEndCol()          {return endCol;}

        inline void flipX(bool yesno)   {bFlipX = yesno;}
        inline void flipY(bool yesno)   {bFlipY = yesno;}
        inline void enable(bool enabled){bEnabled = enabled;}
        inline bool isEnabled()			{return bEnabled;}

        /// set the position relative the overall building grid
        /// row, column are the upper left corner
        void setPos(int row, int column);
        
        /// set the position relative to the current position
        void move(int rowAmount, int colAmount);
		
		/// reset the position and orientation
		void reset();

        /**
            \brief retrieve the address of the window at a certain position
            \param  row		index of row
            \param  col 	index of column
            \param  global  true to get global address, false for address rel to window
            \return			window address of row/column, -1 if no window at this position
        **/
        int getAddress(int row, int col, bool global=false);

		/* ***** FRAME BUFFER DRAWING ***** */

        /// set side to a particular color
        void set(FrameBuffer& frame, uint32_t color);

        /// set row of side to a particular color
        void setRow(FrameBuffer& frame, int row, uint32_t color, bool global=false);

        /// set column of side to a particular color
        void setCol(FrameBuffer& frame, int col, uint32_t color, bool global=false);

        /// set window at row/column to particular color.
        /// do nothing, if there is no window at that position.
        void setWindow(FrameBuffer& frame, int row, int col, uint32_t color, bool global=false);
        
        /* ***** PIXEL BUFFER DRAWING ***** */
        
        /// draw the side into a pixel buffer
        void draw(uint32_t* pixels, Building& building, FrameBuffer& frame);
        
        /// draw the side into a pixel buffer with a color
        void draw(uint32_t* pixels, Building& building, uint32_t color, bool drawEmpty=false);
		
        /// draw a row of the side into a pixel buffer with a color
        void drawRow(uint32_t* pixels, Building& building, unsigned int row, uint32_t color);
        
        /// draw a col of the side into a pixel buffer with a color
        void drawCol(uint32_t* pixels, Building& building, unsigned int col, uint32_t color);
        
        /// draw a window of the side into a pixel buffer with a color
        void drawWindow(uint32_t* pixels, Building& building, unsigned int row, unsigned int col, uint32_t color);

		/* ***** UTIL ***** */

        /// print the side addresses graphically to LOG
        void print();

    protected:

		std::string name;

        int startAddr;		///< first window address
        int endAddr;		///< last window address

        int startRow;		///< index of top row in an overall numbering
        int endRow;			///< index of last row in an overall numbering

        int startCol;       ///< index of leftmost col in overall numbering
        int endCol;         ///< index of rightmost col in overall numbering

        int nrRows;         ///< number of rows
        int nrCols;		    ///< number of columns

        int* windowAddrs;	///< window addresses of this side

        bool bFlipX, bFlipY;  ///< flip the side?
        bool bEnabled;        ///< is this side enabled?
		
		int c_startRow;		///< the default start row
		int c_startCol;		///< the default start col
};

} // namespace

#endif // FACADE_SIDE_H
