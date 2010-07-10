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

namespace visual {

// ***** STATIC VARIABLES *****
SDL_Surface* Graphics::_screen  = NULL;

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
DrawMode Graphics::_imageMode = CORNER;
FontMode Graphics::_fontMode = SOLID;

// ***** LOCAL GLOBAL VARIABLES *****
int _x1, _y1, _x2, _y2; // computed rectangle points

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

void Graphics::setWindowTitle(const std::string title)
{
    _sTitle = title;
    SDL_WM_SetCaption(_sTitle.c_str(), NULL);
}

bool Graphics::setWindowIcon(const std::string bitmapFile)
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

    SDL_FreeSurface(_screen);

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

void Graphics::clear(Color color)
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
    	return;
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

// ***** global primitives *****
void Graphics::point(const int x, const int y)
{
    if(_screen == NULL)
        throw WindowException();

    if(_bStroke)
    {
        SPG_PixelBlend(_screen, x, y, _strokeColor.get(_screen), _strokeColor.A);
    }
}

void Graphics::line(const int x1, const int y1, const int x2, const int y2)
{
    if(_screen == NULL)
        throw WindowException();

    if(_bStroke)
    {
        SPG_LineBlend(_screen, x1, y1, x2, y2, _strokeColor.get(_screen), _strokeColor.A);
    }
}

void Graphics::rectangle(const int x, const int y, const int w, const int h)
{
    if(_screen == NULL)
        throw WindowException();

    if(_rectMode == CENTER)
    {
        _x1 = x-w/2;
        _x2 = x+w/2;
        _y1 = y-h/2;
        _y2 = y+h/2;
    }
    else
    {
        _x1 = x;
        _x2 = x+w;
        _y1 = y;
        _y2 = y+h;
    }
    
    if(_bFill)
    {
        SPG_RectFilledBlend(_screen, _x1, _y1, _x2, _y2, _fillColor.get(_screen), _fillColor.A);
    }

    if(_bStroke)
    {
        SPG_RectBlend(_screen, _x1, _y1, _x2, _y2, _strokeColor.get(_screen), _strokeColor.A);
    }
}

void Graphics::circle(const int x, const int y, const int r)
{
    if(_screen == NULL)
        throw WindowException();

    if(_bFill)
    {
        SPG_CircleFilledBlend(_screen, x, y, r, _fillColor.get(_screen), _fillColor.A);
    }

    if(_bStroke)
    {
        SPG_CircleBlend(_screen, x, y, r, _strokeColor.get(_screen), _strokeColor.A);
    }
}

void Graphics::ellipse(const int x, const int y, const int rx, const int ry)
{
    if(_screen == NULL)
        throw WindowException();

    if(_bFill)
    {
        SPG_EllipseFilledBlend(_screen, x, y, rx, ry, _fillColor.get(_screen), _fillColor.A);
    }

    if(_bStroke)
    {
        SPG_EllipseBlend(_screen, x, y, rx, ry, _strokeColor.get(_screen), _strokeColor.A);
    }
}

void Graphics::triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3)
{
    if(_screen == NULL)
        throw WindowException();

    if(_bFill)
    {
        SPG_TrigonFilledBlend(_screen, x1, y1, x2, y2, x3, y3, _fillColor, _fillColor.A);
    }

    if(_bStroke)
    {
        SPG_TrigonBlend(_screen, x1, y1, x2, y2, x3, y3, _strokeColor, _strokeColor.A);
    }
}

void Graphics::polygon(const PointList& points)
{
    if(_screen == NULL)
        throw WindowException();

    if(_bFill)
    {
        SPG_PolygonFilledBlend(_screen, points.size(), (SPG_Point*) &points[0], _fillColor, _fillColor.A);
    }

    if(_bStroke)
    {
        SPG_PolygonBlend(_screen, points.size(), (SPG_Point*) &points[0], _strokeColor, _strokeColor.A);
    }
}

void Graphics::character(const int x, const int y, const char c)
{
    if(_screen == NULL)
        throw WindowException();

    if(_bStroke)
    {
        characterRGBA(_screen, x, y, c,
        	_strokeColor.R, _strokeColor.G, _strokeColor.B, _strokeColor.A);
    }
}

void Graphics::string(const int x, const int y, const std::string line)
{
    if(_screen == NULL)
        throw WindowException();

    if(_bStroke)
    {
        stringRGBA(_screen, x, y, line.c_str(),
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
    
	SDL_BlitSurface((SDL_Surface*) surface, NULL, _screen, &dest);
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

} // namespace
