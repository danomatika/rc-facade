/*==============================================================================

	Facade.cpp

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
#include "Facade.h"

#include "Config.h"

#define FACADE_WIN_ASPECT_WIDTH 3

using namespace visual;

Facade::Facade() : _packet(NULL),
	_bDrawOutlines(false), _bShowSides(false), _windowSize(5)
{
    // allocate packet
    _packet = SDLNet_AllocPacket(getPacketLen());
    _packet->len = getPacketLen();
}

Facade::~Facade()
{
	SDLNet_FreePacket(_packet); // cleanup
}

void Facade::draw(int x, int y)
{
    int xPos = x, yPos = y, xStart = xPos;
    
    if(!_bDrawOutlines)
        Graphics::noStroke();
    
    for(unsigned int y = 0; y < getHeight(); ++y)
    {
        for(unsigned int x = 0; x < getWidth(); ++x)
        {
        	// draw framebufer
            Graphics::fill(Color(getFrameBuffer()[y*getWidth()+x]));
            if(_bDrawOutlines)
            	visual::Graphics::stroke(0x666666);
            Graphics::rectangle(xPos, yPos, _windowSize*FACADE_WIN_ASPECT_WIDTH, _windowSize);
            
            // draw mask overlay
            if(_bShowSides)
            {
            	Color color;
                color.setWithAlpha(getMask()[y*getWidth()+x]);
                if(color.argb != 0)
                {
                	//color.A = 200;
            		Graphics::fill(color);
            		Graphics::rectangle(xPos, yPos, _windowSize*FACADE_WIN_ASPECT_WIDTH, _windowSize);
				}
            }
            
            xPos += _windowSize*FACADE_WIN_ASPECT_WIDTH;
        }
        xPos = xStart;
        yPos += _windowSize;
    }

}
        
void Facade::send()
{
	// send the facade frame packet
    try
    {
        memcpy(_packet->data, getPacket(), getPacketLen());
        _sender.send(_packet);
    }
    catch(std::exception& e)
    {
        LOG_ERROR << "Facade: Could not send packet: " << e.what() << endl;
    }
}

unsigned int Facade::getDrawWidth()
{
	return _windowSize*FACADE_WIN_ASPECT_WIDTH*getWidth();
}

unsigned int Facade::getDrawHeight()
{
	return _windowSize*getHeight();
}
