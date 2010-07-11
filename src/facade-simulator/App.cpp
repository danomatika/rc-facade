/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#include "App.h"

#include <sstream>

#include "Config.h"
#include <facade/Facade.h>

#define FACADE_RECV_PORT	8080

using namespace visual;
using namespace facade;

App::App() : bRunning(true),
    facade(Config::instance().getFacade())
{}

App::~App()
{}

bool App::init()
{
	if(!receiver.setup(FACADE_RECV_PORT, facade.getPacketLen()))
		return false;
        
    // setup the facade
    LOG << endl;
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
    if(bRunning)
    {
//        facade.clear();
    }
    
    // handle new packet?
    if(receiver.receivePacket())
    {
    	LOG_DEBUG << "received packet" << endl;
    	if(receiver.getDataLen() == facade.getPacketLen())
    		facade.setPacket(receiver.getData());
        else
        {
        	LOG_WARN << "Bad Packet: Received length " << receiver.getDataLen()
                     << " is not Facade packet len " << facade.getPacketLen() << endl;
        }
    }
    
    facadeImage.load(facade.getFrameBuffer(), facade.getWidth(), facade.getHeight());
}

void App::draw()
{
    facade.draw(0, 0);

	if(bDebug)
    {
    	facadeImage.draw(Graphics::getWidth()-facadeImage.width(), 0);
    	facadeMask.draw(Graphics::getWidth()-facadeMask.width(), facadeImage.height());
	}
    
    if(bRunning)
	{
        //facade.send();
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
        case 'p':
            bRunning = !bRunning;
            break;

        case 'd':
            bDebug = !bDebug;
            facade.showSides(bDebug);
            facade.drawOutlines(bDebug);
            break;

        default:
            break;
    }
}
