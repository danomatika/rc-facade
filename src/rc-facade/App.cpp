/*==============================================================================

	App.cpp

	rc-facade: a simple 2d graphics engine for the AEC facade
  
	Copyright (C) 2009, 2010  Dan Wilcox <danomatika@gmail.com>

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
#include "facade/Facade.h"

#define OSC_BASE_ADDR   "/visual/facade"
#define FACADE_RECV_PORT 8080

using namespace visual;
using namespace facade;

App::App() : OscObject(""), bRunning(true),
	config(Config::instance()),
    facade(Config::instance().getFacade()),
    receiver(Config::instance().getReceiver()),
    reloadTimestamp(0)
{
    // set osc addresses
    setOscRootAddress(OSC_BASE_ADDR);
    receiver.setOscRootAddress(OSC_BASE_ADDR);
    sceneManager.setOscRootAddress(OSC_BASE_ADDR);

    receiver.addOscObject(this);
    receiver.addOscObject(&sceneManager);
    
    reloadTimestamp = Graphics::getMillis();
}

App::~App()
{}

bool App::init()
{
    // setup the osc listener
    receiver.setup(config.listeningPort);
    receiver.start();
	
	config.print();

    // setup the facade
    LOG << endl;
    facadeMask.load(facade.getMask(), facade.getWidth(), facade.getHeight());
    facade.setup(config.sendingIp, FACADE_RECV_PORT);
    facade.print();
	
	// load the xml file into the scene manager
    if(config.getXmlFilename() != "")
    {
    	//sceneManager.loadXmlFile(config.getXmlFilename());
    }
    
    return true;
}

void App::setup()
{
    setBackground(0x505050);
    setFrameRate(25);
    
    sceneManager.setup();
}

void App::update()
{
    if(bRunning)
    {
        facade.clear();
        //sceneManager.draw();
		config.updateLua();
		config.drawLua();
        facade.swap();
        
        facadeImage.load(facade.getFrameBuffer(), facade.getWidth(), facade.getHeight());
    }
}

void App::draw()
{
    facade.draw(0, 0);

	if(bDebug)
    {
    	facadeImage.draw(Graphics::getWidth()-facadeImage.width(), 0);
    	facadeMask.draw(Graphics::getWidth()-facadeMask.width(), facadeImage.height());
	}

	Graphics::stroke(0xFFFFFF);
	stringstream stream;
	int x = ((float)mouseX/(float)Graphics::getWidth())*facade.getWidth();
	int y = ((float)mouseY/(float)Graphics::getHeight())*facade.getHeight();
	stream << "pos: " << x << ", " << y;
	Graphics::string(10, 10, stream.str());

    if(bRunning)
	{
        facade.send();
    }
}

void App::cleanup()
{
    receiver.stop();
	config.closeLuaFile();
}

void App::keyPressed(SDLKey key, SDLMod mod)
{
    switch(key)
    {
        case 'p':
            bRunning = !bRunning;
            receiver.ignoreMessages(!bRunning);
            break;

        case 'd':
            bDebug = !bDebug;
            facade.showSides(bDebug);
            facade.drawOutlines(bDebug);
            break;
			
		case 'g':	// show grid?
			facade.drawOutlinesToggle();
			break;
			
		case 's':	// draw sides?
			facade.showSidesToggle();
			break;

        case 'r':	// reload xml
            if(Graphics::getMillis() - reloadTimestamp > 5000)
            {
                //sceneManager.closeXmlFile();
                //sceneManager.clear(true);
                //sceneManager.loadXmlFile();
				
				config.reloadFiles();
            }
            break;

        case SDLK_LEFT:
            sceneManager.prevScene();
            break;

        case SDLK_RIGHT:
            sceneManager.nextScene();
            break;

        default:
            break;
    }
}

/* ***** PROTECTED ***** */

bool App::processOscMessage(const osc::ReceivedMessage& message,
								  const osc::MessageSource& source)
{
	LOG_DEBUG << "received " << message.path() << " " << message.types() << std::endl;
    
    if(message.path() == getOscRootAddress() + "/scene")
    {
        if(message.types() == "s")
        {
            string scene = message.asString(0);
            sceneManager.gotoScene(scene);
            return true;
        }
        else if(message.types() == "i")
        {
            int index = message.asInt32(0);
            sceneManager.gotoScene(index);
            return true;
        }
    }
    
    else if(message.path() == getOscRootAddress() + "/scene/prev")
    {
    	sceneManager.prevScene();
    	return true;
    }
    
    else if(message.path() == getOscRootAddress() + "/scene/next")
    {
    	sceneManager.nextScene();
    	return true;
    }

    else if(message.path() == getOscRootAddress() + "/quit")
    {
        exitMainLoop();
        return true;
    }

    return false;
}
