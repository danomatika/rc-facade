/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#ifndef FACADE_H
#define FACADE_H

#include <visualframework.h>

class Facade
{
    public:

        enum FacadeSide
        {
            SIDE_MAIN_NORTH,
            SIDE_MAIN_EAST,
            SIDE_MAIN_SOUTH,
            SIDE_MAIN_SOUTH_STREET,
            SIDE_MAIN_WEST,
            SIDE_LAB_NORTH,
            SIDE_LAB_EAST,
            SIDE_LAB_SOUTH
        };

        Facade();
        virtual ~Facade();

        /// calls setup automatically
        Facade(std::string ip, unsigned int port=8080);

        /// set the ip and port to send the facade packets to
        void setup(std::string ip, unsigned int port=8080);

        /// clears the framebuffer by setting the background
        void clear();

        /// send the facade framebuffer
        void send();

        /// draw the facade sides, (x,y) is the upper left corner
        /// note: only draws windows that exist at a specific position
        void draw(int x, int y);

        /// draw the overall building grid, (x,y) is the upper left corner
        void drawGrid(int x, int y);

        /// set the framebuffer clear color
        void setClearColor(visual::Color color);
        void setClearColor(unsigned int color);

        /* ***** SETTINGS ***** */

        /// set the draw size of a window in pixels
        /// note: aspect ration is 3:1
        void setWindowSize(unsigned int size);

        /// should the sides draw outlines around the windows?
        void drawOutlines(bool yesno);
        void drawOutlines();    /// toggle

        /// set the color of the window outlines
        void setOutlineColor(visual::Color color);
        void setOutlineColor(unsigned int color);

        /// should the graphics primitives wrap around the grid? (on by default)
        inline void wrapX(bool yesno)  {_bWrapX = yesno;}
        inline void wrapY(bool yesno) {_bWrapY = yesno;}

        /* ***** SIDE SETTINGS ***** */

        /// place the side in the overall building grid, (x,y) are the upper left corner
        void setSidePos(FacadeSide side, int x, int y);

        /// enable/disable a building side
        void enableSide(FacadeSide side, bool enabled);

        /// flip the side horizontally or vertically
        void flipSide(FacadeSide side, bool flipX, bool flipY);

        /// call this after changing any if the side attributes to recompute the overall all building grid size
        void recomputeSize();

        /// draw the individual sides with different colors for debugging placement, ignores background
        /// (off by default)
        void showSides(bool yesno) {_bShowSides = yesno;}

        /* ***** GRAPHICS ***** */

        /// set the draw color
        void stroke(visual::Color color)    {_drawColor = color;}
        void stroke(unsigned int color) {_drawColor.set(color);}

        /// set the color of a specific side
        void sideColor(FacadeSide side);

        /// set the color of a row on a specific side
        void sideRow(FacadeSide side, int row);

        /// set the color of a column on a specific side
        void sideCol(FacadeSide side, int col);

        /// draw a pixel on a specific side
        /// x, y are coordinates relative the WINDOWS's size, not the building grid
        /// aka (0, 0) isthe upper left corder of the side no matter where it is
        void sidePixel(FacadeSide side, int x, int y);

        /// draw a pixel in the building grid (finds the right side)
        void pixel(int x, int y);

        /// draw a line in the building grid
        void line(int x1, int y1, int x2, int y2);

        /// draw a rectangle in the building grid
        void rect(int x, int y, int w, int h, bool drawFromCenter=false);

        /// draw a filled rectangle in the building grid
        void box(int x, int y, int w, int h, bool drawFromCenter=false);

        //void circle(int x, int y, int r);

        /// enable/disable color blending when drawing
        void enableBlending();
        void disableBlending();

        /* ***** UTIL ***** */

        /// print the facade "graphically" to LOG
        void print();

        /// get the overall width and height of the building grid
        int getWidth();
        int getHeight();

        /// get the width/height of a specific window
        int getSideWidth(FacadeSide side);
        int getSideHeight(FacadeSide side);

        /// get the pos of a specific window in the building grid (upper left corner)
        int getSidePosX(FacadeSide side);
        int getSidePosY(FacadeSide side);

    private:

        visual::Color _clearColor;      /// framebuffer clear color
        visual::Color _drawColor;       /// current draw color

        bool _bWrapX, _bWrapY;  /// does drawing wrap around the grid edges?
        bool _bShowSides;       /// draw the individual sides in diff colors?
};

#endif // FACADE_H
