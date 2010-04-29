/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
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

void Font::drawSolid(const char c, const int x, const int y, const Color& color)
{
	if(!_font)
    	return;

	SDL_Surface* surface = TTF_RenderGlyph_Solid(_font, c, color.color);
	if(!surface)
    	return;
        
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = surface->w;
    dest.h = surface->h;

	SDL_BlitSurface(surface, NULL, Graphics::getScreen(), &dest);
    SDL_FreeSurface(surface);
}

void Font::drawBlended(const char c, const int x, const int y, const Color& color)
{
	if(!_font)
    	return;

	SDL_Surface* surface = TTF_RenderGlyph_Blended(_font, c, color.color);
	if(!surface)
    	return;
        
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = surface->w;
    dest.h = surface->h;

	SDL_BlitSurface(surface, NULL, Graphics::getScreen(), &dest);
    SDL_FreeSurface(surface);
}

void Font::drawShaded(const char c, const int x, const int y, const Color& foreground, const Color& background)
{
	if(!_font)
    	return;

	SDL_Surface* surface = TTF_RenderGlyph_Shaded(_font, c, foreground.color, background.color);
	if(!surface)
    	return;
        
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = surface->w;
    dest.h = surface->h;

	SDL_BlitSurface(surface, NULL, Graphics::getScreen(), &dest);
    SDL_FreeSurface(surface);
}

void Font::drawSolid(const std::string& text, const int x, const int y, const Color& color)
{
	if(!_font)
    	return;

	SDL_Surface* surface = TTF_RenderUTF8_Solid(_font, text.c_str(), color.color);
	if(!surface)
    	return;
        
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = surface->w;
    dest.h = surface->h;

	SDL_BlitSurface(surface, NULL, Graphics::getScreen(), &dest);
    SDL_FreeSurface(surface);
}

void Font::drawBlended(const std::string& text, const int x, const int y, const Color& color)
{
	if(!_font)
    	return;

	SDL_Surface* surface = TTF_RenderUTF8_Blended(_font, text.c_str(), color.color);
	if(!surface)
    	return;
        
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = surface->w;
    dest.h = surface->h;

	SDL_BlitSurface(surface, NULL, Graphics::getScreen(), &dest);
    SDL_FreeSurface(surface);
}

void Font::drawShaded(const std::string& text, const int x, const int y, const Color& foreground, const Color& background)
{
	if(!_font)
    	return;

	SDL_Surface* surface = TTF_RenderUTF8_Shaded(_font, text.c_str(), foreground.color, background.color);
	if(!surface)
    	return;
        
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = surface->w;
    dest.h = surface->h;

	SDL_BlitSurface(surface, NULL, Graphics::getScreen(), &dest);
    SDL_FreeSurface(surface);
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
