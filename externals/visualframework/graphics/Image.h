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
#ifndef VISUAL_IMAGE_H
#define VISUAL_IMAGE_H

#include "Common.h"

#include <string>

#include "Texture.h"

namespace visual {

/// a texture that can load from an image file
class Image : public Texture
{
	public:
	
		Image();
		Image(std::string filename);
		
		/// load an image
		bool load(std::string filename);
		
		/// load from ARGB pixels
		bool load(const uint32_t* pixels, unsigned int w, unsigned int h);
		
		void clear();
		
		inline std::string getFilename() {return _filename;}
		
		/// print this images's info via ostream
		friend std::ostream& operator<<(std::ostream& os, const Image& from)
		{
			os << "loaded: " << from.isLoaded()
			   << " w: " << (int) from.width() << " h: " << (int) from.height()
			   << " filename: " << from._filename;
			return os;
		}

	protected:

		std::string	_filename;
};

} // namespace

#endif // VISUAL_IMAGE_H
