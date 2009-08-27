#ifndef SIDE_APP_H
#define SIDE_APP_H

#include <string>

#include "FrameBuffer.h"

/**
 * abstract base class for building sides, initialized in derived
 * classes to represent a certain side.
 */
class Side
{
    public:

        Side() {}
        virtual ~Side() {}

        inline std::string getName()    {return name;}
        inline int getStartAddress()    {return startAddr;}
        inline int getEndAddress()      {return endAddr;}
        inline int getNrRows()          {return nrRows;}
        inline int getNrCols()          {return nrCols;}
        inline int getStartRow()        {return startRow;}
        inline int getEndRow()          {return endRow;}
        inline int getStartCol()        {return startCol;}
        inline int getEndCol()          {return endCol;}

        static unsigned int getWindowSize() {return _windowSize;}
        static void setWindowSize(unsigned int size)    {_windowSize = size;}
        static void drawOutlines(bool yesno)         {_bDrawOutlines = yesno;}
        static void drawOutlines()                   {_bDrawOutlines = !_bDrawOutlines;}
        static Color& getOutlineColor() {return _outlineColor;}
        static void setOutlineColor(Color color)    {_outlineColor = color;}
        static void setOutlineColor(unsigned int color) {_outlineColor.set(color);}

        /**
            \brief retrieve the address of the window at a certain position
            \param  row		index of row
            \param  column	index of column
            \param  global  true to get global address, false for address rel to window
            \return			window address of row/column, -1 if no window at this position
        **/
        int getAddress(int row, int col, bool global=false);

        /**
         * set side to a particular color
         */
        void setColor(FrameBuffer& frame, Color color);

        /**
         * set row of side to a particular color
         */
        void setRowColor(FrameBuffer& frame, int row, Color color, bool global=false);

        /**
         * set column of side to a particular color
         */
        void setColumnColor(FrameBuffer& frame, int column, Color color, bool global=false);

        /**
         * set window at row/column to particular color.
         * do nothing, if there is no window at that position.
         */
        void setWindowColor(FrameBuffer& frame, int row, int column, Color color, bool global=false);

        /// draw the side, x,y is upper left corner
        /// if global is true, x and y will be offset by where the sides start row nad cols are
        void draw(FrameBuffer& frame, int x, int y, bool global=false);

        /// print the side addresses graphically to LOG
        void print();

    protected:

		std::string name;

        int startAddr;		///< first window address
        int endAddr;		///< last window address

        int startRow;		///< index of top row in an overall numbering
        int endRow;			///< index of last row in an overall numbering

        int startCol;       /// index of leftmost col in overall numbering
        int endCol;         /// index of rightmost col in overall numbering

        int nrRows;         /// number of rows
        int nrCols;		    ///< number of columns

        int* windowAddrs;	///< window addresses of this side

    private:

        static unsigned int _windowSize;    /// how big should the window pixel be
        static bool _bDrawOutlines;     /// draw an outline around each window?
        static Color _outlineColor;     /// the color of the window outlines
};

#endif // SIDE_APP_H
