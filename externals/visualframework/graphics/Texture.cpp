/*==============================================================================

	Texture.cpp

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
#include "Texture.h"

#include "Common.h"
#include "sprig/sprig.h"

namespace visual {

Texture::Texture() : _surface(NULL)
{}

Texture::Texture(unsigned int w, unsigned int h) : _surface(NULL)
{
	allocate(w, h);
}

Texture::~Texture()
{
	clear();
}

bool Texture::allocate(unsigned int w, unsigned int h)
{
	clear();
	
	_surface = SPG_CreateSurface32(SDL_SWSURFACE, w, h);
	if(!_surface)
	{
		LOG_ERROR << "Texture: " << SDL_GetError() << std::endl; 
		return false;
	}

	return true;
}

bool Texture::load(const uint32_t* pixels, unsigned int w, unsigned int h)
{
	// do we need to allocate?
	if((w != width() && h != height()) || !_surface)
	{
		if(allocate(w, h))
			return false;
	}
	
	// load from pixels
	for(unsigned int x = 0; x < w; ++x)
	{
		for(unsigned int y = 0; y < h; ++y)
		{
			Color color;
			color.setWithAlpha(pixels[y*w + x]);
			SPG_PixelBlend(_surface, x, y, color.get(Graphics::getScreen()), color.A);
		}
	}
	
	return true;
}

void Texture::clear()
{
	if(_surface)
		SDL_FreeSurface(_surface);
}

bool Texture::isLoaded() const
{
	return (bool) _surface; 
}

void Texture::draw(int x, int y)
{
	if(!_surface) throw TextureException();
	
	if(Graphics::getTextureMode() == CENTER)
	{
		x = x-(_surface->w/2);
		y = y-(_surface->h/2);
	}

	Graphics::surface(x, y, _surface);
//	Graphics::quadtex(_surface, 0, 0, _surface->w-1, _surface->h-1,
//							  x, y, _surface->w-1, _surface->h-1);
}

void Texture::fill(unsigned int color)
{
	Color c(color);
	fill(c);
}

void Texture::fill(Color& color)
{
	if(!_surface) throw TextureException();
	
	SDL_FillRect(_surface, NULL, color.get(_surface));
	//SPG_FloodFill(_surface, width(), height(), color.get(_surface));
}

void Texture::resize(int w, int h)
{
	scale((float)w/(float)width(), (float)h/(float)height());
}

void Texture::scale(float scaleX, float scaleY)
{
	if(!_surface) throw TextureException();
	
	SDL_Surface* newSurface = NULL;
	if(!hasAlpha())
		newSurface= SPG_Scale(_surface, scaleX, scaleY);
	else
		newSurface = SPG_ScaleAA(_surface, scaleX, scaleY);

	if(!newSurface)
	{
		LOG_ERROR << "Texture: scaling failed" << std::endl;
		return;
	}
	SDL_FreeSurface(_surface);
	_surface = newSurface;
}

void Texture::rotate(float angle)
{
	if(!_surface) throw TextureException();
	
	SDL_Surface* newSurface = NULL;
	if(!hasAlpha())
		newSurface= SPG_Rotate(_surface, angle);
	else
		newSurface = SPG_RotateAA(_surface, angle);

	if(!newSurface)
	{
		LOG_ERROR << "Texture: rotating failed" << std::endl;
		return;
	}
	SDL_FreeSurface(_surface);
	_surface = newSurface;
}

void Texture::pixelate(unsigned int pixelWidth, unsigned int pixelHeight)
{
	if(!_surface) throw TextureException();

	if(pixelWidth == 0)	pixelWidth = 1;
	if(pixelHeight == 0) pixelHeight = 1;
	
	// algorithm from http://www.tuxradar.com/practicalphp/11/2/24
		  
	// go from pixel block to block
	for(int x = 0; x < _surface->w; x += pixelWidth)
	{
		for(int y = 0; y < _surface->h; y += pixelHeight)
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
					// if we are outside the valid bounds of the Texture, use a safe color
					if (k < 0) { colors.push_back(thisColor); continue; }
					if (k >= (unsigned int) _surface->w) { colors.push_back(thisColor); continue; }
					if (l < 0) { colors.push_back(thisColor); continue; }
					if (l >= (unsigned int) _surface->h) { colors.push_back(thisColor); continue; }

					// if not outside the Texture bounds, get the colour at this pixel
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
			SPG_RectFilledBlend(_surface, x, y, x+pixelWidth, y+pixelHeight,
				SDL_MapRGB(_surface->format, newR, newG, newB), newA);
		}
	}
}

unsigned int Texture::width() const
{
	return _surface ? _surface->w : -1;
}

unsigned int Texture::height() const
{
	return _surface ? _surface->h : -1;
}

Color Texture::getPixel(unsigned int x, unsigned int y)
{
	if(!_surface) throw TextureException();
	
	Color color;
	color.set(SPG_GetPixel(_surface, x, y), _surface);
	return color;
}

void Texture::setPixel(unsigned int x, unsigned int y, Color& color)
{
	if(!_surface) throw TextureException();

	SPG_PixelBlend(_surface, x, y, color.get(_surface), color.A);
}

bool Texture::hasAlpha() const
{
	if(!_surface) throw TextureException();
	
	if((_surface->flags & SDL_SRCALPHA) || (_surface->format->Amask != 0))
		return true;
	return false;
}

} // namespace
