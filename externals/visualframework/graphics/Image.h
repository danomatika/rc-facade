/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
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
