/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
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
	if(!_image)
    	return;

	SDL_Rect dest;// = {(Sint16) posX, (Sint16) posY, 0, 0};
    
	if(Graphics::getImageMode() == CENTER)
    {
    	dest.x = x-(_image->w/2);
        dest.y = y-(_image->h/2);
    }
	else
    {
        dest.x = x;
        dest.y = y;
    }

	SDL_BlitSurface(_image, NULL, Graphics::getScreen(), &dest);
}

void Image::resize(int w, int h)
{
	if(!_image)
    	return;
	
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
	if(!_image)
    	return;
	
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
	Color c;
	if(!_image)
    	return c;	/// empty
        
	c.set(SPG_GetPixel(_image, x, y));
    return c;
}

void Image::setPixel(unsigned int x, unsigned int y, Color& color)
{
	if(!_image)
    	return;

	SPG_Pixel(_image, x, y, color.rgba);
}

void Image::pixelate(unsigned int pixelWidth, unsigned int pixelHeight)
{
    if(!_image)
    	return;

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
            unsigned int newR = 0, newG = 0, newB = 0;
            
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
            }
            
            // now divide the master numbers by the number of valid samples to get an average
            newR /= colors.size();
    		newG /= colors.size();
            newB /= colors.size();
            
            // and use the new numbers as our color
            SPG_RectFilled(_image, x, y, x+pixelWidth, y+pixelHeight,
            	SDL_MapRGB(_image->format, newR, newG, newB));
        }
    }
}

} // namespace
