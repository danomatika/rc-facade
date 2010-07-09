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

namespace visual {

class Image
{
	public:
	
    	Image();
        Image(std::string filename);
    	virtual ~Image();
        
        bool load(std::string filename);
        
        void clear();
        
        bool isLoaded();
        
        void draw(int x, int y);
        
        void resize(int w, int h);
        void scale(float scaleX, float scaleY);
        
        const int width();
        const int height();
        
        Color getPixel(unsigned int x, unsigned int y);
        void setPixel(unsigned int x, unsigned int y, Color& color);
        void pixelate(unsigned int pixelWidth, unsigned int pixelHeight);
        
        /// get the raw surface structure of the image (contains pixels)
        SDL_Surface* getSurface() {return _image;}
        
        inline std::string getFilename() {return _filename;}

    protected:
    	
        SDL_Surface* _image;
    	std::string	_filename;
};

} // namespace

#endif // VISUAL_IMAGE_H
