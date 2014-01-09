/*==============================================================================

	Color.h

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
#ifndef VISUAL_COLOR_H
#define VISUAL_COLOR_H

#include <iostream>
#include <cassert>

namespace visual {

class Color
{
	public:

		union
		{
			struct
			{
				uint8_t	B, G, R, A;  // individual access, reversed for proper byte order
			};
			uint32_t argb;     // single variable, 0xAARRGGBB
		};

		Color() : B(255), G(255), R(255), A(255) {}

		Color(const uint8_t r, const uint8_t g, const uint8_t b) :
			B(b), G(g), R(r), A(255) {}           

		Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) :
			B(b), G(g), R(r), A(a) {}
		
		/// html style hex aka 0xFF00FF
		Color(const uint32_t color) : A(255)
		{
			set(color);
		}

		virtual ~Color() {}

		/// copy constructor
		Color(const Color& from)
		{
			R = from.R;
			G = from.G;
			B = from.B;
			A = from.A;
		}

		/// copy operator
		void operator =(const Color& from)
		{
			R = from.R;
			G = from.G;
			B = from.B;
			A = from.A;
		}

		/// attribute sets
		void set(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a=255)
		{
			R = r;
			G = g;
			B = b;
			A = a;
		}

		/// ARGB, no alpha
		void set(const uint32_t color)
		{
			R = color >> 16;
			G = color >> 8;
			B = color;
			A = 255;
		}
		
		/// ARGB with alpha
		void setWithAlpha(const uint32_t color)
		{
			A = color >> 24;
			R = color >> 16;
			G = color >> 8;
			B = color >> 0;
		}
		
		/// uint operator
		operator uint32_t() const
		{
			return argb;
		}
		
		/// set mapped to a surface's pixel format
		void set(const uint32_t color, SDL_Surface* surface)
		{
			assert(surface);	// surface should never be NULL
			SDL_GetRGBA(color, surface->format, &R, &G, &B, &A);
		}
		
		/// get this color mapped to a surface's pixel format
		uint32_t get(const SDL_Surface* surface) const
		{
			assert(surface);	// surface should never be NULL
			return SDL_MapRGBA(surface->format, R, G, B, A);
		}
		
		/// get this color as an SDL_color
		inline operator SDL_Color() const
		{
			SDL_Color c = {R, G, B, A};
			return c;
		}

		/// print this color's value via ostream
		friend std::ostream& operator<<(std::ostream& os, const Color& from)
		{
			os << "R: " << (int) from.R << " G: " << (int) from.G << " B: " << (int) from.B
			   << " A: " << (int) from.A;
			return os;
		}
};

} // namespace

#endif // VISUAL_COLOR_H
