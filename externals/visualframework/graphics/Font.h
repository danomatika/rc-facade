/*==============================================================================

	Font.h

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
#ifndef VISUAL_FONT_H
#define VISUAL_FONT_H

#include "Common.h"

#include <SDL/SDL_ttf.h>

#include <string>

namespace visual {

class Font
{
	public:
	
    	Font();
        Font(std::string filename, unsigned int size);
    	virtual ~Font();
        
        bool load(std::string filename, unsigned int size);
        
        void clear();
        
        bool isLoaded();
        
        /// draw characters
        void draw(const char c, const int x, const int y);
        
        /// draw strings
        void draw(const std::string& text, const int x, const int y);
        
        //const int width();
        //const int height();
        
        /// get the raw surface structure of the Font (contains pixels)
        //SDL_Surface* getSurface() {return _Font;}
        
        inline std::string getFilename() {return _filename;}
        
        static void initTTF();
        static void cleanupTTF();

    protected:
    	
        TTF_Font*	_font;
    	std::string	_filename;
};

} // namespace

#endif // VISUAL_FONT_H
