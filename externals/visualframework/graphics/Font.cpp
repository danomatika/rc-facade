/*==============================================================================

	Font.cpp

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
#include "Font.h"

// from http://www.parallelrealities.co.uk/tutorials/basic/tutorial7.php

namespace visual {

Font::Font() : _font(NULL), _filename("")
{}

Font::Font(std::string filename, unsigned int size) : _font(NULL), _filename("")
{
	load(filename, size); 
}

Font::~Font()
{
	clear();
}

bool Font::load(std::string filename, unsigned int size)
{
	// clear if Font already loaded
    clear();

	_font = TTF_OpenFont(filename.c_str(), size);
    if(!_font)
    {
    	LOG_ERROR << "Font: " << TTF_GetError() << std::endl; 
        return false;
    }
    
    _filename = filename;
    return true;
}

void Font::clear()
{
	if(_font)
    	TTF_CloseFont(_font);
}

bool Font::isLoaded()
{
	return (bool) _font;
}

void Font::draw(const char c, const int x, const int y)
{
	SDL_Surface* surface = render(c);
	if(!surface)
    	return;

    Graphics::surface(x, y, surface);
    SDL_FreeSurface(surface);
}

void Font::draw(const std::string& text, const int x, const int y)
{
    SDL_Surface* surface = render(text);
    if(!surface)
    	return;

    Graphics::surface(x, y, surface);
    SDL_FreeSurface(surface);
}

SDL_Surface* Font::render(const char c)
{
	assert(_font);	// font not loaded!

	SDL_Surface* surface = NULL;
	switch(Graphics::getFontMode())
    {
    	case SOLID:
        	surface = TTF_RenderGlyph_Solid(_font, c, Graphics::getStroke());
            break;
            
        case BLENDED:
        	surface = TTF_RenderGlyph_Blended(_font, c, Graphics::getStroke());
            break;
            
        case SHADED:
        {
        	surface = TTF_RenderGlyph_Shaded(_font, c,
    			Graphics::getStroke(),	// foreground
            	Graphics::getFill());	// background
            break;
        }
    }
    
    if(!surface)
    {
    	LOG_ERROR << "Font::render: couldn't create surface: " << TTF_GetError() << std::endl;
    }
    
    return surface;
}

SDL_Surface* Font::render(const std::string& text)
{
	assert(_font);	// font not loaded!

	SDL_Surface* surface = NULL;
	switch(Graphics::getFontMode())
    {
    	case SOLID:
        	surface = TTF_RenderUTF8_Solid(_font, text.c_str(), Graphics::getStroke());
            break;
            
        case BLENDED:
        	surface = TTF_RenderUTF8_Blended(_font, text.c_str(), Graphics::getStroke());
            break;
            
        case SHADED:
        	surface = TTF_RenderUTF8_Shaded(_font, text.c_str(),
    			Graphics::getStroke(),	// foreground
            	Graphics::getFill());		// background
            break;
    }
    
    if(!surface)
    {
    	LOG_ERROR << "Font::render: couldn't create surface: " << TTF_GetError() << std::endl;
    }
    
    return surface;
}

/*
const int Font::width()
{
    return _Font ? _Font->w : -1;
}

const int Font::height()
{
	return _Font ? _Font->h : -1;
}
*/

void Font::initTTF()
{
	TTF_Init();
}

void Font::cleanupTTF()
{
	TTF_Quit();
}
            

} // namespace
