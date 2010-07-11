/*==============================================================================

	Facade.h

	facade-simulator: a simple 2d simulator for the AEC facade
  
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
        
        // draw the framebuffer
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
        UdpPacket* _packet;
        
        bool _bDrawOutlines;
        bool _bShowSides;
        unsigned int _windowSize;
};

#endif // FACADE_H
