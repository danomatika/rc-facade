/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#ifndef FACADE_H
#define FACADE_H

#include "Common.h"
#include <facade/Facade.h>

class facade::Facade;

class Facade : public facade::Facade
{
    public:

        Facade();
        virtual ~Facade();
        
        /// setup the sending destination
        void setup(string addr, unsigned int port);
        
        /// draw the framebuffer
        void draw(int x=0, int y=0);
        
        /// send a facade frame
        void send();
        
        /// draw the individual sides with different colors for debugging placement, ignores background
        /// (off by default)
        inline void showSides(bool yesno) 		{_bShowSides = yesno;}
        
        /// should the sides draw outlines around the windows?
        inline void drawOutlines(bool yesno)	{_bDrawOutlines = yesno;}
        
        /// set the draw size of a window in pixels
        /// note: aspect ration is 3:1
        inline void setWindowSize(unsigned int size) {_windowSize = size;}
        
        /// get the draw width and height, based on windowSize
        unsigned int getDrawWidth();
        unsigned int getDrawHeight();

    private:
        
        visual::Image _facadeImage;
        visual::Image _facadeMask;
        
        visual::UdpSender _sender;
        
        bool _bDrawOutlines;
        bool _bShowSides;
        unsigned int _windowSize;
};

#endif // FACADE_H
