/*==============================================================================

	Graphics.h

	visualframework: a simple 2d graphics framework
	
	Uses the SPriG - SDL Primitive Generator by Jonathan Dearborn (GPL2)
  
	Copyright (C) 2009, 2010  Dan Wilcox <danomatika@gmail.com>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/
#ifndef VISUAL_GRAPHICS_H
#define VISUAL_GRAPHICS_H

#include <string>
#include <vector>

#include <SDL/SDL.h>

#include "Color.h"
#include "Texture.h"

#include "../Point.h"
#include "../Exception.h"

namespace visual {

enum GraphicsMode {
	WINDOW = 0,
	FULLSCREEN = SDL_FULLSCREEN
};

enum GraphicsType {
	UNKNOWN		= 0,
	SOFTWARE	= SDL_SWSURFACE,
	HARDWARE	= SDL_HWSURFACE
};

 // global primitive draw options
enum DrawMode
{
	CENTER,	// pos is upper right corner
	CORNER,	// pos is center of rect/texture
	CORNERS	// pos is upper right corner, w/h is lower left corner
};

// global font modes
enum FontMode
{
	SOLID,		// fast
	BLENDED,	// antialiased
	SHADED		// background
};

// shapes (following OpenGL)
enum Shape
{
	POINTS,
	LINES,
	LINE_STRIP,
	LINE_LOOP,
	TRIANGLES,
	TRIANGLE_STRIP,
	TRIANGLE_FAN,
	QUADS,
	QUAD_STRIP,
	POLYGON
};

/// Window exception
class WindowException : public Exception
{
	public:
		WindowException(
			const char* w="call to graphics command when SDL window is not yet setup")
			: Exception(w) {}
};

/// Shape exception
class ShapeException : public Exception
{
	public:
		ShapeException(
			const char* w="cannot start a new shape or shape has not begun")
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
		static void setWindowTitle(const std::string& title);

		/// set the window's icon
		static bool setWindowIcon(const std::string& bitmapFile);

		/// create the actual sdl draw surface
		static bool createWindow(std::string title="");

		/// toggles between fullscreen and window,
		/// automatically destroys and recreates draw surface
		static bool toggleFullscreen();
		
		/// show/hide the mouse cursor (shown by default)
		static bool getShowMouseCursor();
		static void showMouseCursor(bool show);
		static void toggleShowMouseCursor();

		/// get available fullscreen video resolutions (descending order)
		/// note: do not free any of the SDL_Rect pointers
		static std::vector<SDL_Rect*> getResolutions();

		/// change the window/screen resolution
		/// automatically destroys and recreates draw surface
		static bool changeResolution(const unsigned int w, const unsigned int h);

		/// get the current vode mode as a string
		static std::string getModeString();
		
		/// clear the screen with a given color
		static void clear(unsigned int color);	///< ARGB
		static void clear(Color& color);
		
		/// swap the draw surface to the screen
		static void swap();

		// global gets
		static const GraphicsType getType()     {return _type;}
		static const GraphicsMode getMode()     {return _mode;}
		static const SDL_Surface* getScreen() 	{return _screen;}
		static const unsigned int getWidth()   	{return _iWidth;}
		static const unsigned int getHeight()  	{return _iHeight;}
		static const unsigned int getDepth()   	{return _iDepth;}

		// global color
		static void stroke(const unsigned int color);	///< ARGB
		static void stroke(const Color& color);
		static void fill(const unsigned int color);		///< ARGB
		static void fill(const Color& color);

		static void noStroke();
		static void noFill();
		
		static const Color& getStroke()	{return _strokeColor;}
		static const Color& getFill()	{return _fillColor;}
		
		// affects rectangles
		static void rectMode(const DrawMode mode) {_rectMode = mode;}
		static const DrawMode getRectMode() {return _rectMode;} 
		
		// affects textures
		static void textureMode(const DrawMode mode) {_textureMode = mode;}
		static const DrawMode getTextureMode() {return _textureMode;}
		
		// affects fonts
		static void fontMode(const FontMode mode) {_fontMode = mode;}
		static const FontMode getFontMode() {return _fontMode;}
		
		// affects lines and object edges
		static void strokeWeight(unsigned int weight=1);
		
		// antialiasing on lines and objects
		static void smooth();
		static void noSmooth();
		
		// alpha blending on lines and objects
		static void blend();
		static void noBlend();
		
		// bezier curve detail (default is 20)
		static void bezierDetail(const uint8_t detail);

		// global primitives
		static void point(const int x, const int y);
		static void line(const int x1, const int y1, const int x2, const int y2);
		static void rectangle(const int x, const int y, const int w, const int h);
		static void circle(const int x, const int y, const int r);
		static void ellipse(const int x, const int y, const int rx, const int ry);
		static void triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3);
		static void polygon(const PointList& points);
		
		static void arc(const int x, const int y, const float r, const float startAngle, const float endAngle);
		static void bezier(const int x, const int y, const int cx1, const int cx2, const int cy1, const int cy2, const int endX, const int endY);
		
		static void character(const int x, const int y, const char c);
		static void string(const int x, const int y, const std::string& line);
		
		static void surface(const int x, const int y, const SDL_Surface* surface);
		static void quadtex(const SDL_Surface* surface, float sx, float sy, float sw, float sh,
														float dx, float dy, float dw, float dh);
		// bitmap string stream helper
		class BitmapString
		{
			public:

				BitmapString(const int x, const int y) : _pos(x, y) {}
				BitmapString(const Point& p) : _pos(p) {}

				/// does the actual printing on exit
				~BitmapString()
				{
					Graphics::string(_pos.x, _pos.y, _line.str());
				}

				/// catch << with a template class to read any type of data
				template <class T> BitmapString& operator<<(const T& value)
				{
					_line << value;
					return *this;
				}

				/// catch << ostream function pointers such as std::endl and std::hex
				BitmapString& operator<<(std::ostream& (*func)(std::ostream&))
				{
					func(_line);
					return *this;
				}

			private:

				BitmapString(BitmapString const&);                // not defined, not copyable
				BitmapString& operator = (BitmapString const&);   // not defined, not assignable
				
				Point _pos;
				std::ostringstream _line;   ///< temp buffer
		};

		// draw with shapes
		static void beginShape(Shape shape);
		static void vertex(int x, int y);
		static void vertex(Point& p);
		static void vertices(PointList& points);
		static void endShape();
		
		// draw transforms
		static void push();
		static void pop();	// popping at the bottom level clears the default transform
		static void popAll();

		// primitive transforms
		// rotate and skew are non orthographic and work best for points, lines,
		// triangles, beziers, polygons and shapes. Does not work as expected
		// with orthographic primitives ie rects, circles, ellipses, and arcs.
		static void scale(float x, float y);
		static void rotate(float angle);	// degrees
		static void skew(float x, float y);
		static void translate(float x, float y);
		
		// set a texture to draw into for all subsequenct drawing calls
		static void setDrawTexture(Texture& texture);
		static void clearDrawTexture();

		// global utils
		static std::string getLastError();
		static unsigned int getMillis();

	private:

		// apply the current transform to the point vector
		static void applyTransform();

		Graphics() {}                       // cannot create
		Graphics(const Graphics& from) {}   // not copyable
		virtual ~Graphics() {}              // cannot destroy
		void operator =(Color& from) {}     // not copyable

		static SDL_Surface* _screen;		/// SDL screen
		static SDL_Surface* _drawSurface;	/// the render surface pointer

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

		// global draw modes
		static DrawMode _rectMode;
		static DrawMode _textureMode;
		static FontMode _fontMode;
		
		// global primitive settings
		static uint8_t _bezierDetail;
		static Shape _currentShape;
		static bool _bShapeStarted;
		
		// current transform
		struct Transform
		{
			bool bScale, bRotate, bSkew, bTranslate;
			float scaleX, scaleY, scaleAvg;
			float rotateAngle;
			float skewX, skewY;
			float translateX, translateY;
			
			Transform() {clear();}
			
			void clear()
			{
				bScale = false; bRotate = false;
				bSkew = false; bTranslate = false;
				scaleX = 0.0f; scaleY = 0.0f;
				rotateAngle = 0.0f;
				skewX = 0.0f; skewY = 0.0f;
				translateX = 0.0f; translateY = 0.0f;
			}
			
			void scale(float x, float y)
			{
				if(x == 0 && y == 0)
					bScale = false;
				else
					bScale = true;
				scaleX = x;
				scaleY = y;
				scaleAvg = (x+y)/2;
			}
			
			void rotate(float angle)
			{
				if(angle == 0)
					bRotate = false;
				else
					bRotate = true;
				rotateAngle = angle;
			}
			
			void skew(float x, float y)
			{
				if(x == 0 && y == 0)
					bSkew = false;
				else
					bSkew = true;
				skewX = x;
				skewY = y;
			}
			
			void translate(float x, float y)
			{
				if(x == 0 && y == 0)
					bTranslate = false;
				else
					bTranslate = true;
				translateX = x;
				translateY = y;
			}
			
			// safe scale getters
			float getScaleX()	{return bScale && scaleX != 0 ? scaleX : 1;}
			float getScaleY()	{return bScale && scaleY != 0 ? scaleY : 1;}
			float getScaleAvg()	{return bScale && scaleAvg != 0 ? scaleAvg : 1;}
		};
		static std::vector<Transform> _transforms;	// transform stack
		static std::vector<Point> _points; 		// temp for transforms
		static std::vector<Point> _shapePoints;	// temp for shapes
};

} // namespace

#endif // VISUAL_GRAPHICS_H
