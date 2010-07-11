/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#ifndef FACADE_FACADE_H
#define FACADE_FACADE_H

#include <string>

namespace facade {

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

        /// clears the framebuffer by setting the background
        void clear();

        /// set the framebuffer clear color
        void setClearColor(uint32_t color);
        
        /// swap the pixel framebuffer into the facade framebuffer packet
        /// automatically discards pixels not on a side
        void swap();
        
        /* ***** RAW PACKET ACCESS ***** */
        
        /// get the raw facade frame packet
        const uint8_t* getPacket() const;

		/// get the length of the packet
		unsigned int getPacketLen();
        
        /// set the raw packet from memory, assumes correct length
        void setPacket(const uint8_t* packet);

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

        /// call this after changing any if the side attributes to recompute the overall all building grid size,
        /// (possibley) changes the width and height; reallocates the pixel framebuffer, not the facade packet
        void recomputeSize();
    
    	/* ***** PIXEL FRAME BUFFER ***** */
        
        /// get the current framebuffer, length is getFramebufferLen()
        /// pixels are 0xAARRGGBB with A always 0xFF
        const uint32_t* getFrameBuffer() const;
        
        /// set the current framebuffer, assumes length is getFramebufferLen()
        /// pixels should be 0xAARRGGBB with A always 0xFF
        void setFrameBuffer(const uint32_t* pixels);
        
        /// get the length of either the framebuffer or the mask
        inline unsigned int getFrameBufferLen()	{return _pixelLen;}
        
        /// get the pixel mask image, the sides are colored and empty pixels = 0
        const uint32_t* getMask() const;
        
        /// get a pixel in the building grid
    	uint32_t getPixel(unsigned int x, unsigned int y);
        
        /// get a pixel in a specific side, returns 0 on empty pixel
        uint32_t getSidePixel(FacadeSide side, unsigned int x, unsigned int y);

        /* ***** GRAPHICS SETTINGS ***** */

        /// set the ARGB draw color, white by default
        /// pure black (0xFFFFFFFF) may turn off the leds, so it is
        /// automatically converted to 0xFF111111
        inline void stroke(uint32_t color) 	{_drawColor = color;}
        
        /// blend colors when drawing? off by default
        /// alpha is ignored when off
        inline void blend()	{_bBlend = true;}
        inline void noBlend()	{_bBlend = false;}
        
        /// fill rectangles? off by default
        inline void fill()		{_bRectFill = true;}
        inline void noFill()	{_bRectFill = false;}
        
        /// draw rectangles from the center or corner? corner by default
        inline void rectModeCenter() {_bRectCenter = true;}
        inline void rectModeCorner() {_bRectCenter = false;}
        
        /// should the graphics primitives wrap around the grid? (on by default)
        inline void wrap()				{_bWrapX = true; _bWrapY = true;}
        inline void noWrap()			{_bWrapX = false; _bWrapY = false;}
        inline void wrapX(bool yesno)	{_bWrapX = yesno;}
        inline void wrapY(bool yesno)	{_bWrapY = yesno;}

		/* ***** GRAPHICS PRIMITIVES ***** */

        /// draw a pixel in the building grid
        void pixel(int x, int y);

        /// draw a line in the building grid
        void line(int x1, int y1, int x2, int y2);

        /// draw a rectangle in the building grid
        void rect(int x, int y, int w, int h);

        /// draw a circle in the building grid
        void circle(int x, int y, int r);
        
        /* ***** SIDE GRAPHICS ***** */
        
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

        /* ***** UTIL ***** */

        /// print the facade addresses "graphically" to stdout
        void print();

        /// get the overall width and height of the building grid
        unsigned int getWidth();
        unsigned int getHeight();

        /// get the width/height of a specific window
        unsigned int getSideWidth(FacadeSide side);
        unsigned int getSideHeight(FacadeSide side);

        /// get the pos of a specific window in the building grid (upper left corner)
        unsigned int getSidePosX(FacadeSide side);
        unsigned int getSidePosY(FacadeSide side);

    private:
    
    	/// (re)allocate and build the mask
    	void setup();
        
        /// set a pixel in the framebuffer
        void setPixel(unsigned int x, unsigned int y, uint32_t color);

        uint32_t* _pixels;	///< pixel framebuffer
        uint32_t* _mask;	///< side location mask

        uint32_t _clearColor;      ///< current clear color
        uint32_t _drawColor;       ///< current draw color

        bool _bWrapX, _bWrapY;  ///< does drawing wrap around the grid edges?
        
        bool _bBlend;		///< blend colors when drawing?
        
        bool _bRectCenter;	///< draw rects from the center point or corner?
        bool _bRectFill;	///< fill rectangles?
        
        unsigned int _pixelLen;	///< length of the pxiel framebuffer
};

} // namespace

#endif // FACADE_FACADE_H
