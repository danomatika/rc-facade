/*==============================================================================

	Graphics.cpp

	visualframework: a simple 2d graphics framework
  
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
#include "Graphics.h"

#include <algorithm>
#include <sstream>

#include "../Log.h"
#include <SDL/SDL_gfxPrimitives.h>
#include "sprig/sprig.h"

// references
// sprig:
// 	- http://www.sdltutorials.com/a-guide-to-graphics-with-sprig/
// 	- http://code.bluedinosaurs.com/tutorials/SprigGuide.html

#define VISUAL_MAX_TRANSFORMS	5

namespace visual {

// ***** STATIC VARIABLES *****
SDL_Surface* Graphics::_screen  = NULL;
SDL_Surface* Graphics::_drawSurface  = NULL;

unsigned int Graphics::_iWidth           = 0;
unsigned int Graphics::_iHeight          = 0;
unsigned int Graphics::_iDepth           = 0;

uint32_t Graphics::_ui32VideoFlags  = 0;
GraphicsType Graphics::_type      = UNKNOWN;
GraphicsMode Graphics::_mode      = WINDOW;
std::string Graphics::_sTitle     = "";

Color Graphics::_strokeColor;
Color Graphics::_fillColor;
bool Graphics::_bStroke = true;
bool Graphics::_bFill   = true;

DrawMode Graphics::_rectMode = CORNER;
DrawMode Graphics::_textureMode = CORNER;
FontMode Graphics::_fontMode = SOLID;

uint8_t Graphics::_bezierDetail = 20;
Shape Graphics::_currentShape = POLYGON;
bool Graphics::_bShapeStarted = false;

std::vector<Graphics::Transform> Graphics::_transforms;
std::vector<Point> Graphics::_points;
std::vector<Point> Graphics::_shapePoints;

bool Graphics::init(unsigned int w, unsigned int h, unsigned int depth, GraphicsType type)
{
	_iWidth = w;
	_iHeight = h;
	_iDepth = depth;
	_ui32VideoFlags = 0;
	_type = type;

	// initialize SDL video
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG_ERROR << "Graphics: " << getLastError() << std::endl;
		return false;
	}

	// set proper flags for mode
	_ui32VideoFlags = _type|SDL_DOUBLEBUF|_mode;

	// make sure SDL cleans up before exit
	atexit(SDL_Quit);
	
	// push the default _transforms
	push();

	return true;
}

// sort resolutions by area in descending order
bool cmpRes(SDL_Rect* a, SDL_Rect* b )
{
	int areaA = a->w*a->h;
	int areaB = b->w*b->h;
	return areaA < areaB;
}

std::vector<SDL_Rect*> Graphics::getResolutions()
{
	// get available fullscreen modes
	SDL_Rect** modes;
	std::vector<SDL_Rect*> resolutions;
	modes = SDL_ListModes(NULL, SDL_FULLSCREEN|_type);

	// check if there are any modes available
	if(modes == (SDL_Rect**)0)
	{
		LOG_WARN << "No resolutions available!" << std::endl;
	}

	// check if our resolution is restricted
	if(modes == (SDL_Rect**)-1)
	{
		LOG << "All resolutions available" << std::endl;
	}

	else
	{
		for(int i=0; modes[i] != NULL; ++i)
		{
			resolutions.push_back(modes[i]);
		}
	}

	// sort into descending order
	std::sort(resolutions.begin(), resolutions.end(), cmpRes);

	return resolutions;
}

void Graphics::setWindowTitle(const std::string& title)
{
	_sTitle = title;
	SDL_WM_SetCaption(_sTitle.c_str(), NULL);
}

bool Graphics::setWindowIcon(const std::string& bitmapFile)
{
	SDL_Surface *icon = SDL_LoadBMP(bitmapFile.c_str());
	if(icon == NULL)
	{
		LOG_ERROR << "Graphics: " << getLastError() << std::endl;
		return false;
	}

	SDL_WM_SetIcon(icon, NULL);

	return true;
}

bool Graphics::createWindow(const std::string title)
{
	unsigned int bpp = SDL_VideoModeOK(_iWidth, _iHeight, _iDepth, _ui32VideoFlags);
	if(!bpp)
	{
		LOG_ERROR << "Graphics: " << getLastError() << std::endl;
		return false;
	}

	// clear?
	if(_screen)
		SDL_FreeSurface(_screen);

	// create a new window
	_screen = SDL_SetVideoMode(_iWidth, _iHeight, _iDepth, _ui32VideoFlags);
	if(!_screen)
	{
		LOG_ERROR << "Graphics: " << getLastError() << std::endl;
		return false;
	}
	_drawSurface = _screen;

	LOG << "Setting: " << getModeString() << std::endl;

	if(title != "")
	{
		_sTitle = title;
		SDL_WM_SetCaption(_sTitle.c_str(), NULL);
	}

	return true;
}

bool Graphics::toggleFullscreen()
{
	if(_screen == NULL)
		throw WindowException();

	switch(_mode)
	{
		case WINDOW:
			_mode = FULLSCREEN;
			break;

		case FULLSCREEN:
			_mode = WINDOW;
			break;
	}

	// set proper flags for mode
	_ui32VideoFlags = _type|SDL_DOUBLEBUF|_mode;

	return createWindow(_sTitle);
}

bool Graphics::getShowMouseCursor()
{
	int state = SDL_ShowCursor(SDL_QUERY);
	if(state == SDL_ENABLE)
		return true;
	return false;
}

void Graphics::showMouseCursor(bool show)
{
	if(show)
		SDL_ShowCursor(SDL_ENABLE);
	else
		SDL_ShowCursor(SDL_DISABLE);
}

void Graphics::toggleShowMouseCursor()
{
	int state = SDL_ShowCursor(SDL_QUERY);
	if(state == SDL_ENABLE)
		SDL_ShowCursor(SDL_DISABLE);
	else
		SDL_ShowCursor(SDL_ENABLE);
}

bool Graphics::changeResolution(const unsigned int w, const unsigned int h)
{
	if(_screen == NULL)
		throw WindowException();

	// set new resolution
	_iWidth = w;
	_iHeight = h;

	return createWindow(_sTitle);
}

std::string Graphics::getModeString()
{
	std::ostringstream stream;

	switch(_type)
	{
		case SOFTWARE:
			stream << "SDL_SWSURFACE";
			break;
		case HARDWARE:
			stream << "SDL_HWSURFACE";
			break;
	}
	stream << " " << _iWidth << "x" << _iHeight << "@" << _iDepth << "bit ";
	switch(_mode)
	{
		case WINDOW:
			stream << "window";
			break;
		case FULLSCREEN:
			stream << "fullscreen";
			break;
	}

	return stream.str();
}

void Graphics::clear(unsigned int color)
{
	clear(Color(color));
}

void Graphics::clear(Color& color)
{
	SDL_FillRect(_screen, NULL, color.get(_screen));
}

void Graphics::swap()
{	
	SDL_Flip(_screen);
}

// ***** global color *****
void Graphics::stroke(const unsigned int color)
{
	_strokeColor.set(color);
	_bStroke = true;
}

void Graphics::stroke(const Color& color)
{
	_strokeColor = color;
	_bStroke = true;
}

void Graphics::fill(const unsigned int color)
{
	_fillColor.set(color);
	_bFill = true;
}

void Graphics::fill(const Color& color)
{
	_fillColor = color;
	_bFill = true;
}

void Graphics::noStroke()
{
	_bStroke = false;
}

void Graphics::noFill()
{
	_bFill = false;
}

void Graphics::strokeWeight(unsigned int weight)
{
	if(weight == 0)
		weight = 1.0;
	SPG_PopThickness();
	SPG_PushThickness(weight);
}

void Graphics::smooth()
{
	SPG_PopAA();
	SPG_PushAA(true);
}

void Graphics::noSmooth()
{
	SPG_PopAA();
	SPG_PushAA(false);
}

void Graphics::blend()
{
	SPG_PopBlend();
	SPG_PushBlend(SPG_COMBINE_ALPHA);
}

void Graphics::noBlend()
{
	SPG_PopBlend();
	SPG_PushBlend(SPG_COPY_NO_ALPHA);
}

void Graphics::bezierDetail(const uint8_t detail)
{
	_bezierDetail = detail;
}

// ***** global primitives *****
void Graphics::point(const int x, const int y)
{
	if(_screen == NULL)
		throw WindowException();

	_points.push_back(Point(x, y));
	applyTransform();

	if(_bStroke)
	{
		SPG_PixelBlend(_drawSurface, _points[0].x, _points[0].y,
			_strokeColor.get(_drawSurface), _strokeColor.A);
	}
	
	_points.clear();
}

void Graphics::line(const int x1, const int y1, const int x2, const int y2)
{
	if(_screen == NULL)
		throw WindowException();

	_points.push_back(Point(x1, y1));
	_points.push_back(Point(x2, y2));
	applyTransform();

	if(_bStroke)
	{
		SPG_LineBlend(_drawSurface, _points[0].x, _points[0].y, _points[1].x, _points[1].y,
			_strokeColor.get(_drawSurface), _strokeColor.A);
	}
	
	_points.clear();
}

void Graphics::rectangle(const int x, const int y, const int w, const int h)
{
	if(_screen == NULL)
		throw WindowException();
	
	_points.push_back(Point());
	_points.push_back(Point());	
	
	switch(_rectMode)
	{
		case CENTER:
			_points[0].set(x-w/2, y-h/2);
			_points[1].set(x+w/2, y+h/2);
			break;
			
		case CORNER:
			_points[0].set(x, y);
			_points[1].set(x+w, y+h);
			break;
			
		case CORNERS:
			_points[0].set(x, y);
			_points[1].set(w, h);
			break;
	}
	applyTransform();
	
	if(_bFill)
	{
		SPG_RectFilledBlend(_drawSurface, _points[0].x, _points[0].y, _points[1].x, _points[1].y,
			_fillColor.get(_drawSurface), _fillColor.A);
	}

	if(_bStroke)
	{
		SPG_RectBlend(_drawSurface, _points[0].x, _points[0].y, _points[1].x, _points[1].y,
			_strokeColor.get(_drawSurface), _strokeColor.A);
	}
		
	_points.clear();
}

void Graphics::circle(const int x, const int y, const int r)
{
	if(_screen == NULL)
		throw WindowException();

	_points.push_back(Point(x, y));
	applyTransform();
	Transform& t = _transforms.back();

	if(_bFill)
	{
		SPG_CircleFilledBlend(_drawSurface, _points[0].x, _points[0].y, r*t.getScaleAvg(),
			_fillColor.get(_drawSurface), _fillColor.A);
	}

	if(_bStroke)
	{
		SPG_CircleBlend(_drawSurface, _points[0].x, _points[0].y, r*t.getScaleAvg(),
			_strokeColor.get(_drawSurface), _strokeColor.A);
	}
	
	_points.clear();
}

void Graphics::ellipse(const int x, const int y, const int rx, const int ry)
{
	if(_screen == NULL)
		throw WindowException();

	_points.push_back(Point(x, y));
	applyTransform();
	Transform& t = _transforms.back();

	if(_bFill)
	{
		SPG_EllipseFilledBlend(_drawSurface, _points[0].x, _points[0].y, rx*t.getScaleX(), ry*t.getScaleY(),
			_fillColor.get(_drawSurface), _fillColor.A);
	}

	if(_bStroke)
	{
		SPG_EllipseBlend(_drawSurface, _points[0].x, _points[0].y, rx*t.getScaleX(), ry*t.getScaleY(),
			_strokeColor.get(_drawSurface), _strokeColor.A);
	}
	
	_points.clear();
}

void Graphics::triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3)
{
	if(_screen == NULL)
		throw WindowException();

	_points.push_back(Point(x1, y1));
	_points.push_back(Point(x2, y2));
	_points.push_back(Point(x3, y3));
	applyTransform();

	if(_bFill)
	{
		SPG_TrigonFilledBlend(_drawSurface, _points[0].x, _points[0].y, _points[1].x, _points[1].y, _points[2].x, _points[2].y, 
			_fillColor.get(_drawSurface), _fillColor.A);
	}

	if(_bStroke)
	{
		SPG_TrigonBlend(_drawSurface, _points[0].x, _points[0].y, _points[1].x, _points[1].y, _points[2].x, _points[2].y,
			_strokeColor.get(_drawSurface), _strokeColor.A);
	}
	
	_points.clear();
}

void Graphics::polygon(const PointList& points)
{
	if(_screen == NULL)
		throw WindowException();

	Graphics::_points = points;
	applyTransform();

	if(_bFill)
	{
		SPG_PolygonFilledBlend(_drawSurface, Graphics::_points.size(), (SPG_Point*) &Graphics::_points[0],
			_fillColor.get(_drawSurface), _fillColor.A);
	}

	if(_bStroke)
	{
		SPG_PolygonBlend(_drawSurface, Graphics::_points.size(), (SPG_Point*) &Graphics::_points[0],
			_strokeColor.get(_drawSurface), _strokeColor.A);
	}
}

void Graphics::arc(const int x, const int y, const float r, const float startAngle, const float endAngle)
{
	if(_screen == NULL)
		throw WindowException();
		
	_points.push_back(Point(x, y));
	applyTransform();
	Transform& t = _transforms.back();
		
	if(_bFill)
	{
		SPG_ArcFilledBlend(_drawSurface, _points[0].x, _points[0].y, r*t.getScaleAvg(), startAngle, endAngle,
			_fillColor.get(_drawSurface), _fillColor.A);
	}
	
	if(_bStroke)
	{
		SPG_ArcBlend(_drawSurface, _points[0].x, _points[0].y, r*t.getScaleAvg(), startAngle, endAngle,
			_strokeColor.get(_drawSurface), _strokeColor.A);
	}
	
	_points.clear();
}

void Graphics::bezier(const int x, const int y, const int cx1, const int cx2, const int cy1, const int cy2, const int endX, const int endY)
{
	if(_screen == NULL)
		throw WindowException();
		
	_points.push_back(Point(x, y));
	_points.push_back(Point(cx1, cy1));
	_points.push_back(Point(cx2, cy2));
	_points.push_back(Point(endX, endY));
	applyTransform();
		
	if(_bStroke)
	{
		SPG_BezierBlend(_drawSurface, _points[0].x, _points[0].y, _points[1].x, _points[2].x,
			_points[1].y, _points[2].y, _points[3].x, _points[3].y, _bezierDetail, _strokeColor.get(_drawSurface), _strokeColor.A);
		SDL_UnlockSurface(_drawSurface);
	}
}

void Graphics::character(const int x, const int y, const char c)
{
	if(_screen == NULL)
		throw WindowException();

	if(_bStroke)
	{
		characterRGBA(_drawSurface, x, y, c,
			_strokeColor.R, _strokeColor.G, _strokeColor.B, _strokeColor.A);
	}
}

void Graphics::string(const int x, const int y, const std::string& line)
{
	if(_screen == NULL)
		throw WindowException();

	if(_bStroke)
	{
		stringRGBA(_drawSurface, x, y, line.c_str(),
			_strokeColor.R, _strokeColor.G, _strokeColor.B, _strokeColor.A);
	}
}

void Graphics::surface(const int x, const int y, const SDL_Surface* surface)
{
	if(_screen == NULL)
		throw WindowException();
		
	assert(surface);	// surface should not be NULL

	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = surface->w;
	dest.h = surface->h;
	
	SDL_BlitSurface((SDL_Surface*) surface, NULL, _drawSurface, &dest);
	//SPG_Blit((SDL_Surface*) surface, NULL, _screen, &dest);	
}

void Graphics::quadtex(const SDL_Surface* surface, float sx, float sy, float sw, float sh,
												   float dx, float dy, float dw, float dh)
{
	for(int i = 0; i < 4; ++i)
		_points.push_back(Point());
	
	if(_textureMode == CENTER)
	{
		_points[0].set(dx-dw/2, dy-dh/2);		// UL
		_points[1].set(_points[0].x, dy+dh/2);	// DL
		_points[2].set(dx+dw/2, dy+dy/2);		// DR
		_points[3].set(_points[2].x, _points[0].y);// UR
	}
	else
	{
		_points[0].set(dx, dy);		// UL
		_points[1].set(dx, dy+dh);	// DL
		_points[2].set(dx+dw, dy+dh);// DR
		_points[3].set(dx+dw, dy);	// UR
	}
	
	// setup tex coords
	_points[4].set(sx, sy);			// UL
	_points[5].set(sx, sy+sh);		// DL
	_points[6].set(sx+sw, sy+sh);	// DR
	_points[7].set(sx+sw, sy);		// UR
	
	applyTransform();

	SPG_QuadTexPoints(_drawSurface, (SPG_Point*) &Graphics::_points[0],
					  (SDL_Surface*) surface,
					  (SPG_Point*) &Graphics::_points[4]);
					  
	_points.clear();
}

void Graphics::beginShape(Shape shape)
{
	if(_bShapeStarted)
		throw ShapeException();

	_currentShape = shape;
	_bShapeStarted = true;
}

void Graphics::vertex(int x, int y)
{
	if(!_bShapeStarted)
		throw ShapeException();
		
	_shapePoints.push_back(Point(x, y));
}

void Graphics::vertex(Point& p)
{
	if(!_bShapeStarted)
		throw ShapeException();
		
	_shapePoints.push_back(p);
}

void Graphics::vertices(PointList& _points)
{
	if(!_bShapeStarted)
		throw ShapeException();
		
	for(unsigned int i = 0; i < _points.size(); ++i)
		_shapePoints.push_back(_points[i]);
}

void Graphics::endShape()
{
	if(_shapePoints.size() == 0)
		throw ShapeException();

	switch(_currentShape)
	{
		case POINTS:
			for(unsigned int i = 0; i < _shapePoints.size(); ++i)
				point(_shapePoints[i].x, _shapePoints[i].y);
			break;
			
		case LINES:
			for(unsigned int i = 1; i < _shapePoints.size(); i+=2)
				line(_shapePoints[i-1].x, _shapePoints[i-1].y, _shapePoints[i].x, _shapePoints[i].y);
			break;
			
		case LINE_STRIP:
			for(unsigned int i = 1; i < _shapePoints.size(); ++i)
				line(_shapePoints[i-1].x, _shapePoints[i-1].y, _shapePoints[i].x, _shapePoints[i].y);
			break;
			
		case LINE_LOOP:
			for(unsigned int i = 1; i < _shapePoints.size(); ++i)
				line(_shapePoints[i-1].x, _shapePoints[i-1].y, _shapePoints[i].x, _shapePoints[i].y);
			line(_shapePoints.front().x, _shapePoints.front().y, _shapePoints.back().x, _shapePoints.back().y);
			break;
			
		case TRIANGLES:
			for(unsigned int i = 2; i < _shapePoints.size(); i+=3)
				triangle(_shapePoints[i-2].x, _shapePoints[i-2].y, _shapePoints[i-1].x, _shapePoints[i-1].y,
					_shapePoints[i].x, _shapePoints[i].y);
			break;
			
		case TRIANGLE_STRIP:
			for(unsigned int i = 2; i < _shapePoints.size(); ++i)
				triangle(_shapePoints[i-2].x, _shapePoints[i-2].y, _shapePoints[i-1].x, _shapePoints[i-1].y,
					_shapePoints[i].x, _shapePoints[i].y);
			break;
			
		case TRIANGLE_FAN:
		{
			Point& p = _shapePoints.front();
			for(unsigned int i = 2; i < _shapePoints.size(); i+=2)
				triangle(p.x, p.y, _shapePoints[i-1].x, _shapePoints[i-1].y,
					_shapePoints[i].x, _shapePoints[i].y);
			break;
		}
			
		case QUADS:
		{
			std::vector<Point> p;
			for(unsigned int i = 3; i < _shapePoints.size(); i+=4)
			{
				p.push_back(_shapePoints[i-3]);
				p.push_back(_shapePoints[i-2]);
				p.push_back(_shapePoints[i-1]);
				p.push_back(_shapePoints[i]);
				polygon(p);
				p.clear();
			}
			break;
		}
		
		case QUAD_STRIP:
		{
			std::vector<Point> p;
			for(unsigned int i = 3; i < _shapePoints.size(); ++i)
			{
				p.push_back(_shapePoints[i-3]);
				p.push_back(_shapePoints[i-2]);
				p.push_back(_shapePoints[i-1]);
				p.push_back(_shapePoints[i]);
				polygon(p);
				p.clear();
			}
			break;
		}
			
		case POLYGON:
				polygon(_shapePoints);
			break;
	}
	_bShapeStarted = false;
	_shapePoints.clear();
}

// ***** draw __transforms *****
void Graphics::push()
{
	if(_transforms.size() >= VISUAL_MAX_TRANSFORMS)
	{
		LOG_WARN << "Too many pushes" << std::endl;
		return;
	}
		
	Transform t;
	_transforms.push_back(t);
}

void Graphics::pop()
{
	if(_transforms.size() == 1)
	{
		_transforms[0].clear();
		return;
	}
	
	_transforms.erase(_transforms.end());
}

void Graphics::popAll()
{
	_transforms.clear();
	push();
}

void Graphics::scale(float x, float y)
{
	_transforms.back().scale(x, y);
}

void Graphics::rotate(float angle)
{
	_transforms.back().rotate(angle);
}

void Graphics::skew(float x, float y)
{
	_transforms.back().skew(x, y);
}

void Graphics::translate(float x, float y)
{
	_transforms.back().translate(x, y);
}

/* ***** draw texture **** */

void Graphics::setDrawTexture(Texture& texture)
{
	_drawSurface = texture;
}

void Graphics::clearDrawTexture()
{
	_drawSurface = _screen;
}

/* ***** global util ***** */

std::string Graphics::getLastError()
{
	return SDL_GetError();
}

unsigned int Graphics::getMillis()
{
	return SDL_GetTicks();
}

/* ***** PRIVATE ***** */

void Graphics::applyTransform()
{
	for(unsigned int i = 0; i < _transforms.size(); ++i)
	{
		Transform& t = _transforms[i];
		if(t.bScale)
			SPG_ScalePoints(_points.size(), (SPG_Point*) &_points[0], t.scaleX, t.scaleY);
		if(t.bRotate)
			SPG_RotatePoints(_points.size(), (SPG_Point*) &_points[0], t.rotateAngle);
		if(t.bSkew)
			SPG_SkewPoints(_points.size(), (SPG_Point*) &_points[0], t.skewX, t.skewY);
		if(t.bTranslate)
			SPG_TranslatePoints(_points.size(), (SPG_Point*) &_points[0], t.translateX, t.translateY);
	}
}

} // namespace
