/*==============================================================================

	Image.h

	visualframework: a simple 2d graphics framework
	
	Image resizing from David Olsen <jolynsbass@gmail.com> (no license given)
  
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
#ifndef VISUAL_TEXTURE_H
#define VISUAL_TEXTURE_H

#include <SDL/SDL.h>
#include "../Exception.h"
#include "Color.h"

namespace visual {

/// Texture exception
class TextureException : public Exception
{
	public:
		TextureException(
			const char* w="cannot access unallocated texture")
			: Exception(w) {}
};

/// a wrapper for an SDL surface
class Texture
{
	public:
	
		Texture();
		Texture(unsigned int w, unsigned int h);	// allocates on construction
		virtual ~Texture();
		
		/// allocate an empty texture
		bool allocate(unsigned int w, unsigned int h);
		
		/// load from ARGB pixels
		bool load(const uint32_t* pixels, unsigned int w, unsigned int h);
		
		/// clear (unallocate) the texture
		virtual void clear();
		
		/// is the texture loaded/allocated?
		bool isLoaded() const;
		
		void draw(int x, int y);
		
		/// fill the texture with a given color
		void fill(unsigned int color);	///< ARGB
		void fill(Color& color);
		
		/// transform the texture (writes over contents)
		void resize(int w, int h);
		void scale(float scaleX, float scaleY);
		void rotate(float angle);
		void pixelate(unsigned int pixelWidth, unsigned int pixelHeight);
		
		/// get the texture dimensions
		unsigned int width() const;
		unsigned int height() const;
		
		/// pixel access
		Color getPixel(unsigned int x, unsigned int y);
		void setPixel(unsigned int x, unsigned int y, Color& color);
		
		/// is this texture using alpha?
		bool hasAlpha() const;
		
		/// get the raw surface structure of the image (contains pixels)
		inline operator SDL_Surface*() {return _surface;}
		
		/// print this texture's info via ostream
		friend std::ostream& operator<<(std::ostream& os, const Texture& from)
		{
			os << "loaded: " << from.isLoaded()
			   << " w: " << (int) from.width() << " h: " << (int) from.height();
			return os;
		}

	protected:
		
		SDL_Surface* _surface;
};

} // namespace

#endif // VISUAL_TEXTURE_H
