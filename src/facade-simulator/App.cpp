/*==============================================================================

	App.cpp

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
#include "App.h"

#include <sstream>

#include "Config.h"
#include <facade/Facade.h>

#define FACADE_RECV_PORT	8080

using namespace visual;
using namespace facade;

App::App() : facade(Config::instance().getFacade())
{}

App::~App()
{}

bool App::init()
{
	if(!receiver.setup(FACADE_RECV_PORT, facade.getPacketLen()))
		return false;
        
    // setup the facade
    LOG << endl;
    //facade.setSidePos(SIDE_MAIN_WEST, 35, 0);
    //facade.moveSides(-9, 0);
    //facade.recomputeSize();
    facadeMask.load(facade.getMask(), facade.getWidth(), facade.getHeight());
    facade.print();

	return true;
}

void App::setup()
{
    setBackground(0x505050);
    setFrameRate(25);
}

void App::update()
{    
    // handle new packet?
    if(receiver.receivePacket())
    {
    	if(receiver.getDataLen() == facade.getPacketLen())
    		facade.setPacket(receiver.getData());
        else
        {
        	LOG_WARN << "Bad Packet: Received length " << receiver.getDataLen()
                     << " is not Facade packet len of " << facade.getPacketLen() << endl;
        }
    }
    
	// laod icon preview
    facadeImage.load(facade.getFrameBuffer(), facade.getWidth(), facade.getHeight());
}

void App::draw()
{
    facade.draw(0, 0);

	if(bDebug)
    {
		// draw preview icons
    	facadeImage.draw(Graphics::getWidth()-facadeImage.width(), 0);
    	facadeMask.draw(Graphics::getWidth()-facadeMask.width(), facadeImage.height());
	}
    
    // fps display
    stringstream stream;
    stream << getFrameRate();
    Graphics::stroke(0xFFFFFF);
    Graphics::string(12, 12, stream.str());
}

void App::cleanup()
{}

void App::keyPressed(SDLKey key, SDLMod mod)
{
    switch(key)
    {
        case 'd':
            bDebug = !bDebug;
            facade.showSides(bDebug);
            facade.drawOutlines(bDebug);
            break;
			
		case 'r':
			if(facade.getXmlFilename() != "")
			{
				facade.loadXmlFile();
				if(facade.getDrawWidth() != Graphics::getWidth() ||
				   facade.getDrawHeight() != Graphics::getHeight())
				{
				   Graphics::changeResolution(facade.getDrawWidth(), facade.getDrawHeight());
				}
			}
			else
			{
				LOG_WARN << "No file to reload" << endl;
			}

			break;
			
        default:
            break;
    }
}
