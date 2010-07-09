/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#ifndef FACADE_H
#define FACADE_H

#include <visualframework/visualframework.h>
#include <string>

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

class Facade
{
    public:

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
        void draw(int x, int y, bool debug=false);

        /// draw the overall building grid, (x,y) is the upper left corner
        void drawGrid(int x, int y);

        /// set the framebuffer clear color
        void setClearColor(uint32_t color);
        //void setClearColor(unsigned int color);

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
        inline void wrapX(bool yesno)	{_bWrapX = yesno;}
        inline void wrapY(bool yesno)	{_bWrapY = yesno;}

        /* ***** SIDE SETTINGS ***** */

        /// place the side in the overall building grid, (x,y) are the upper left corner
        void setSidePos(FacadeSide side, int x, int y);
        
        /// move the side realitve to it's current position in the overall building grid
		void moveSide(FacadeSide side, int xAmount, int yAmount);
        
        /// move all sides relative to their current position in the overall building grid
        void moveSides(int xAmount, int yAmount);
        
        /// enable/disable a building side
        void enableSide(FacadeSide side, bool enabled);

        /// flip the side horizontally or vertically
        void flipSide(FacadeSide side, bool flipX, bool flipY);

        /// call this after changing any if the side attributes to recompute the overall all building grid size
        void recomputeSize();

        /// draw the individual sides with different colors for debugging placement, ignores background
        /// (off by default)
        inline void showSides(bool yesno) {_bShowSides = yesno;}

        /* ***** GRAPHICS ***** */

        /// set the ARGB draw color, white by default
        /// pure black (0xFFFFFFFF) may turn off the leds, so it is
        /// automatically converted to 0xFF111111
        inline void stroke(uint32_t color) 	{_drawColor = color;}
        
        /// blend colors when drawing? off by default
        /// alpha is ignored when off
        void blend();
        void noBlend();
        
        /// fill rectangles? off by default
        inline void fill()		{_bRectFill = true;}
        inline void noFill()	{_bRectFill = false;}
        
        /// draw rectangles from the center or corner? corner by default
        inline void rectModeCenter() {_bRectCenter = true;}
        inline void rectModeCorner() {_bRectCenter = false;}

        /// set the color of a specific side
        void sideColor(FacadeSide side);

        /// set the color of a row on a specific side
        void sideRow(FacadeSide side, int row);

        /// set the color of a column on a specific side
        void sideCol(FacadeSide side, int col);

        /// draw a pixel on a specific side
        /// x, y are coordinates relative the WINDOWS's size, not the building grid
        /// aka (0, 0) is the upper left corder of the side no matter where it is
        void sidePixel(FacadeSide side, int x, int y);
        
        /// get a pixel in the building grid, returns black (0xFFFFFFFF) on empty pixel
    	//uint32_t getPixel(int x, int y);
        
        /// get a pixel in a specific side, returns black (0xFFFFFFFF) on empty pixel
        //uint32_t getSidePixel(FacadeSide side, int x, int y);

        /// draw a pixel in the building grid
        void pixel(int x, int y);

        /// draw a line in the building grid
        void line(int x1, int y1, int x2, int y2);

        /// draw a rectangle in the building grid
        void rect(int x, int y, int w, int h);

        /// draw a circle in the building grid
        void circle(int x, int y, int r);
        
        /* ***** FRAMEBUFFER ***** */
        
        // get the pixel framebuffer
        uint32_t* getPixels();
        
        // load the pixel framebuffer, assumes width and height
        void setPixels(uint32_t* p); 

        /* ***** UTIL ***** */

        /// print the facade "graphically" to stdout
        void print();

        /// get the overall width and height of the building grid
        inline unsigned int getWidth() {return _width;}
        inline unsigned int getHeight(){return _height;}

        /// get the width/height of a specific window
        unsigned int getSideWidth(FacadeSide side);
        unsigned int getSideHeight(FacadeSide side);

        /// get the pos of a specific window in the building grid (upper left corner)
        unsigned int getSidePosX(FacadeSide side);
        unsigned int getSidePosY(FacadeSide side);

    private:

        uint8_t *_pixels;	/// pixel framebuffer
        unsigned int _width, _height;	/// framebuffer size

        uint32_t _clearColor;      /// framebuffer clear color
        uint32_t _drawColor;       /// current draw color

        bool _bWrapX, _bWrapY;  /// does drawing wrap around the grid edges?
        bool _bShowSides;       /// draw the individual sides in diff colors?
        
        bool _bBlend;		/// blend colors when drawing?
        
        bool _bRectCenter;	/// draw rects from the center point or corner?
        bool _bRectFill;	/// fill rectangles?
};

#endif // FACADE_H
