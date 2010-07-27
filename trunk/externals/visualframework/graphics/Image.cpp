/*==============================================================================

	Image.cpp

	visualframework: a simple 2d graphics framework
  
	Copyright (C) 2010  Dan Wilcox <danomatika@gmail.com>

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
#include "Image.h"

#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "resize/resize++.h"
#include "sprig/sprig.h"

namespace visual {

Image::Image() : _image(NULL), _filename("")
{}

Image::Image(std::string filename) : _image(NULL), _filename("")
{
	load(filename);
}

Image::~Image()
{
	clear();
}

bool Image::load(std::string filename)
{
	// clear if image already loaded
    clear();

	_image = IMG_Load(filename.c_str());
    if(!_image)
    {
    	LOG_ERROR << "Image: "  << IMG_GetError() << std::endl; 
        return false;
    }
    
    _filename = filename;
    return true;
}

bool Image::load(const uint32_t* pixels, unsigned int w, unsigned int h)
{
	clear();
    
    _image = SPG_CreateSurface32(SDL_SWSURFACE, w, h);
    if(!_image)
    {
    	LOG_ERROR << "Image: "  << SDL_GetError() << std::endl; 
        return false;
    }
    
    // load image
    for(unsigned int x = 0; x < w; ++x)
    {
    	for(unsigned int y = 0; y < h; ++y)
        {
        	Color color;
            color.setWithAlpha(pixels[y*w + x]);
        	SPG_Pixel(_image, x, y, color.get(_image));
        }
    }
    
    return true;
}

void Image::clear()
{
	if(_image)
    	SDL_FreeSurface(_image);
}

bool Image::isLoaded()
{
	return (bool) _image; 
}

void Image::draw(int x, int y)
{
	assert(_image);	// image not created!
    
	if(Graphics::getImageMode() == CENTER)
    {
    	x = x-(_image->w/2);
        y = y-(_image->h/2);
    }

	Graphics::surface(x, y, _image);
}

void Image::resize(int w, int h)
{
	assert(_image);	// image not created!
	
    // resize automatically frees old image
    _image = SDL_Resize(_image, w, h);
    if(!_image)
    {
    	LOG_ERROR << "Image: resizing failed" << std::endl;
    	return;
    }
}

void Image::scale(float scaleX, float scaleY)
{
	assert(_image);	// image not created!
	
    // resize automatically frees old image
    _image = SDL_Resize(_image, scaleX, scaleY);
    if(!_image)
    {
    	LOG_ERROR << "Image: resizing failed" << std::endl;
    	return;
    }
}

const int Image::width()
{
    return _image ? _image->w : -1;
}

const int Image::height()
{
	return _image ? _image->h : -1;
}

Color Image::getPixel(unsigned int x, unsigned int y)
{
	assert(_image);	// image not created!
    
    Color color;
    color.set(SPG_GetPixel(_image, x, y), _image);
    return color;
}

void Image::setPixel(unsigned int x, unsigned int y, Color& color)
{
	assert(_image);	// image not created!

	SPG_PixelBlend(_image, x, y, color.get(_image), color.A);
}

void Image::pixelate(unsigned int pixelWidth, unsigned int pixelHeight)
{
    assert(_image);	// image not created!

	if(pixelWidth == 0)	pixelWidth = 1;
    if(pixelHeight == 0) pixelHeight = 1;
    
	// algorithm from http://www.tuxradar.com/practicalphp/11/2/24
          
	// go from pixel block to block
    for(int x = 0; x < _image->w; x += pixelWidth)
    {
    	for(int y = 0; y < _image->h; y += pixelHeight)
        {
        	// get the top-left pixel
            Color thisColor = getPixel(x, y);
            
            // new color (must be large enough, Color too small)
            unsigned int newR = 0, newG = 0, newB = 0, newA = 0;
            
            // our color values
            std::vector<Color> colors;
            
            // grab each pixel in the block
            for(unsigned int k = x; k < x + pixelWidth; ++k)
            {
            	for(unsigned int l = y; l < y + pixelHeight; ++l)
                {
                	// if we are outside the valid bounds of the image, use a safe color
                    if (k < 0) { colors.push_back(thisColor); continue; }
                    if (k >= (unsigned int) _image->w) { colors.push_back(thisColor); continue; }
                    if (l < 0) { colors.push_back(thisColor); continue; }
                    if (l >= (unsigned int) _image->h) { colors.push_back(thisColor); continue; }

                    // if not outside the image bounds, get the colour at this pixel
                    colors.push_back(getPixel(k, l));
                }
            }
            
            // cycle through all the colours we can use for sampling
            for(unsigned int i = 0; i < colors.size(); ++i)
            {
            	// add their red, green, and blue values to our master numbers
            	newR += colors[i].R & 0xFF;
                newG += colors[i].G & 0xFF;
                newB += colors[i].B & 0xFF;
                newA += colors[i].A & 0xFF;
            }
            
            // now divide the master numbers by the number of valid samples to get an average
            newR /= colors.size();
    		newG /= colors.size();
            newB /= colors.size();
            newA /= colors.size();
            
            // and use the new numbers as our color
            SPG_RectFilled(_image, x, y, x+pixelWidth, y+pixelHeight,
            	SDL_MapRGBA(_image->format, newR, newG, newB, newA));
        }
    }
}

} // namespace
