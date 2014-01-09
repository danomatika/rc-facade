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

namespace visual {

Image::Image() : Texture(), _filename("")
{}

Image::Image(std::string filename) : Texture(), _filename("")
{
	load(filename);
}

bool Image::load(std::string filename)
{
	clear();

	_surface = IMG_Load(filename.c_str());
	if(!_surface)
	{
		LOG_ERROR << "Image: " << IMG_GetError() << std::endl; 
		return false;
	}

	_filename = filename;
	return true;
}

bool Image::load(const uint32_t* pixels, unsigned int w, unsigned int h)
{
	return Texture::load(pixels, w, h);
}

void Image::clear()
{
	Texture::clear();
	_filename = "";
}

} // namespace
