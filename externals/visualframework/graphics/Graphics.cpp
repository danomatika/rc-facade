/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
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

// ***** global primitives *****
void Graphics::point(const int x, const int y)
{
    if(_screen == NULL)
        throw WindowException();

    if(_bStroke)
    {
        SPG_Pixel(_screen, x, y, _strokeColor.get(_screen));
    }
}

void Graphics::line(const int x1, const int y1, const int x2, const int y2)
{
    if(_screen == NULL)
        throw WindowException();

    if(_bStroke)
    {
        SPG_Line(_screen, x1, y1, x2, y2, _strokeColor.get(_screen));
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
        SPG_RectFilled(_screen, _x1, _y1, _x2, _y2, _fillColor.get(_screen));
    }

    if(_bStroke)
    {
        SPG_Rect(_screen, _x1, _y1, _x2, _y2, _strokeColor.get(_screen));
    }
}

void Graphics::circle(const int x, const int y, const int r)
{
    if(_screen == NULL)
        throw WindowException();

    if(_bFill)
    {
        SPG_CircleFilled(_screen, x, y, r, _fillColor.get(_screen));
    }

    if(_bStroke)
    {
        SPG_Circle(_screen, x, y, r, _strokeColor.get(_screen));
    }
}

void Graphics::ellipse(const int x, const int y, const int rx, const int ry)
{
    if(_screen == NULL)
        throw WindowException();

    if(_bFill)
    {
        SPG_EllipseFilled(_screen, x, y, rx, ry, _fillColor.get(_screen));
    }

    if(_bStroke)
    {
        SPG_Ellipse(_screen, x, y, rx, ry, _strokeColor.get(_screen));
    }
}

void Graphics::triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3)
{
    if(_screen == NULL)
        throw WindowException();

    if(_bFill)
    {
        SPG_TrigonFilled(_screen, x1, y1, x2, y2, x3, y3, _fillColor.rgba);
    }

    if(_bStroke)
    {
        SPG_Trigon(_screen, x1, y1, x2, y2, x3, y3, _strokeColor.rgba);
    }
}

void Graphics::polygon(const PointList& points)
{
    if(_screen == NULL)
        throw WindowException();

    if(_bFill)
    {
        SPG_PolygonFilled(_screen, points.size(), (SPG_Point*) &points[0], _fillColor.rgba);
    }

    if(_bStroke)
    {
        SPG_Polygon(_screen, points.size(), (SPG_Point*) &points[0], _strokeColor.rgba);
    }
}

void Graphics::character(const int x, const int y, const char c)
{
    if(_screen == NULL)
        throw WindowException();

    if(_bStroke)
    {
        characterColor(_screen, x, y, c, _strokeColor.rgba);
    }
}

void Graphics::string(const int x, const int y, const std::string line)
{
    if(_screen == NULL)
        throw WindowException();

    if(_bStroke)
    {
        stringColor(_screen, x, y, line.c_str(), _strokeColor.rgba);
    }
}

std::string Graphics::getLastError()
{
    return SDL_GetError();
}

unsigned int Graphics::getMillis()
{
    return SDL_GetTicks();
}

} // namespace
