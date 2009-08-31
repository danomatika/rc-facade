/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#ifndef SIDE_APP_H
#define SIDE_APP_H

#include <string>

#include "FrameBuffer.h"

#define FACADE_WIN_ASPECT_WIDTH 3

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
        inline void enable(bool enabled)    {bEnabled = enabled;}

        static unsigned int getWindowSize() {return _windowSize;}
        static void setWindowSize(unsigned int size)    {_windowSize = size;}
        static void drawOutlines(bool yesno)         {_bDrawOutlines = yesno;}
        static void drawOutlines()                   {_bDrawOutlines = !_bDrawOutlines;}
        static visual::Color& getOutlineColor() {return _outlineColor;}
        static void setOutlineColor(visual::Color color)    {_outlineColor = color;}
        static void setOutlineColor(unsigned int color) {_outlineColor.set(color);}

        /// set this windows position realitve the overall building grid
        /// row, column are the upper left corner
        void setPos(int row, int column);

        /**
            \brief retrieve the address of the window at a certain position
            \param  row		index of row
            \param  column	index of column
            \param  global  true to get global address, false for address rel to window
            \return			window address of row/column, -1 if no window at this position
        **/
        int getAddress(int row, int col, bool global=false);

        /// set side to a particular color
        void setColor(FrameBuffer& frame, visual::Color color);

        /// set row of side to a particular color
        void setRowColor(FrameBuffer& frame, int row, visual::Color color, bool global=false);

        /// set column of side to a particular color
        void setColColor(FrameBuffer& frame, int column, visual::Color color, bool global=false);

        /// set window at row/column to particular color.
        /// do nothing, if there is no window at that position.
        void setWindowColor(FrameBuffer& frame, int row, int column, visual::Color color, bool global=false);

        /// draw the side, x,y is upper left corner
        /// if global is true, x and y will be offset by where the sides start row nad cols are
        void draw(FrameBuffer& frame, int x, int y, bool global=false);

        /// print the side addresses graphically to LOG
        void print();

    protected:

		std::string name;

        int startAddr;		/// first window address
        int endAddr;		/// last window address

        int startRow;		/// index of top row in an overall numbering
        int endRow;			/// index of last row in an overall numbering

        int startCol;       /// index of leftmost col in overall numbering
        int endCol;         /// index of rightmost col in overall numbering

        int nrRows;         /// number of rows
        int nrCols;		    /// number of columns

        int* windowAddrs;	/// window addresses of this side

        bool bFlipX, bFlipY;  /// flip the side?
        bool bEnabled;        /// is this side enabled?

    private:

        static unsigned int _windowSize;/// how big should the window pixel be
        static bool _bDrawOutlines;     /// draw an outline around each window?
        static visual::Color _outlineColor;     /// the color of the window outlines
};

#endif // SIDE_APP_H
