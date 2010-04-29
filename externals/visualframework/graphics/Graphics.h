/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#ifndef VISUAL_GRAPHICS_H
#define VISUAL_GRAPHICS_H

#include <string>

#include <SDL/SDL.h>

#include "Color.h"

#include "../Point.h"
#include "../Exception.h"

namespace visual {

enum GraphicsMode {
	WINDOW = 0,
	FULLSCREEN = SDL_FULLSCREEN
};

enum GraphicsType {
    UNKNOWN     = 0,
    SOFTWARE    = SDL_SWSURFACE,
    HARDWARE    = SDL_HWSURFACE
};

 // global primitive draw options
enum DrawMode
{
    CENTER,
    CORNER
};

/// Window exception
class WindowException : public Exception
{
	public:
    	WindowException(
            const char* w="call to graphics command when SDL window is not yet setup")
        	: Exception(w) {}
};

class Graphics
{
    public:

        /// init sdl graphics
        static bool init(unsigned int w, unsigned int h, unsigned int depth, GraphicsType type=HARDWARE);

        /// set screen mode before creating window
        static void inline setWindow()     {_mode = WINDOW;}
        static void inline setFullscreen() {_mode = FULLSCREEN;}

        /// set the window's title text
        static void setWindowTitle(const std::string title);

        /// set the window's icon
        static bool setWindowIcon(const std::string bitmapFile);

        /// create the actual sdl draw surface
        static bool createWindow(std::string title="");

        /// toggles between fullscreen and window,
        /// automatically destroys and recreates draw surface
        static bool toggleFullscreen();

        /// get available fullscreen video resolutions (descending order)
        /// note: do not free any of the SDL_Rect pointers
        static std::vector<SDL_Rect*> getResolutions();

        /// change the window/screen resolution
        /// automatically destroys and recreates draw surface
        static bool changeResolution(const unsigned int w, const unsigned int h);

        /// get the current vode mode as a string
        static std::string getModeString();
        

        // global gets
        static const GraphicsType getType()     {return _type;}
        static const GraphicsMode getMode()     {return _mode;}
        static SDL_Surface* getScreen() 		{return _screen;}
        static const unsigned int getWidth()   	{return _iWidth;}
        static const unsigned int getHeight()  	{return _iHeight;}
        static const unsigned int getDepth()   	{return _iDepth;}

        // global color
        static void stroke(const unsigned int color);
        static void stroke(const Color& color);
        static void fill(const unsigned int color);
        static void fill(const Color& color);

        static void noStroke();
        static void noFill();
        
        // affects rectangles
        static void rectMode(const DrawMode mode) {_rectMode = mode;}
        static const DrawMode getRectMode() {return _rectMode;} 
        
        // affects images
        static void imageMode(const DrawMode mode) {_imageMode = mode;}
        static const DrawMode getImageMode() {return _imageMode;} 

        // global primitives
        static void point(const int x, const int y);
        static void line(const int x1, const int y1, const int x2, const int y2);
        static void rectangle(const int x, const int y, const int w, const int h);
        static void circle(const int x, const int y, const int r);
        static void ellipse(const int x, const int y, const int rx, const int ry);
        static void triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3);
        static void polygon(const PointList& points);
        static void character(const int x, const int y, const char c);
        static void string(const int x, const int y, const std::string line);

        // global utils
        static std::string getLastError();
        static unsigned int getMillis();

    private:

        Graphics() {}                       // cannot create
        Graphics(const Graphics& from) {}   // not copyable
        virtual ~Graphics() {}              // cannot destroy
        void operator =(Color& from) {}     // not copyable

        static SDL_Surface* _screen;	/// SDL draw surface

        static unsigned int _iWidth;    /// window width
        static unsigned int _iHeight;   /// window height
        static unsigned int _iDepth;    /// bit depth

        static uint32_t _ui32VideoFlags;/// sdl video mode flags
        static GraphicsMode _mode;      /// context mode, WINDOW or FULLSCREEN
        static GraphicsType _type;      /// context type
        static std::string _sTitle;     /// window title

        // global color settings
        static Color _strokeColor;
        static Color _fillColor;
        static bool _bStroke;
        static bool _bFill;

        static DrawMode _rectMode;
        static DrawMode _imageMode;
};

} // namespace

#endif // VISUAL_GRAPHICS_H
