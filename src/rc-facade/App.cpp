/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#include "App.h"

#include "Config.h"
#include "facade/Facade.h"

#define OSC_BASE_ADDR   "/visual/facade"

using namespace visual;
using namespace facade;

App::App() : OscObject(""), bRunning(true),
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
    
    // allocate packet
    packet = SDLNet_AllocPacket(facade.getPacketLen());
    packet->len = facade.getPacketLen();
}

App::~App()
{
	SDLNet_FreePacket(packet); // cleanup
}

void App::init()
{
    // setup the osc listener
    receiver.setup(7000);
    receiver.start();

	// set destibation
    sender.setup("192.168.5.73", 8080);

    // setup the facade
    LOG << endl;
    facade.blend();
    //facade.setup("192.168.7.121", 8080);
    //facade.setClearColor(0xFFFF00);//Color(40, 40, 40));
    //facade.setWindowSize(7);

    // move some sides
    //facade.moveSides(-10, 0);
    // close encounters setup
    //facade.setSidePos(Facade::SIDE_LAB_EAST, 0, 18);
    //facade.setSidePos(Facade::SIDE_LAB_NORTH, 5, 17);

	// facade opera pic setup
    /*
	facade.enableSide(Facade::SIDE_LAB_EAST, false);
    facade.enableSide(Facade::SIDE_LAB_NORTH, false);
    facade.enableSide(Facade::SIDE_MAIN_WEST, false);
    facade.setSidePos(Facade::SIDE_MAIN_EAST, 0, 3);
    
    facade.enableSide(Facade::SIDE_MAIN_NORTH, false);
    facade.moveSide(Facade::SIDE_MAIN_SOUTH, -10, 0);
    */
    //facade.enableSide(SIDE_MAIN_SOUTH, false);
    //facade.enableSide(SIDE_LAB_SOUTH, false);
    //facade.moveSide(SIDE_MAIN_SOUTH_STREET, 0, 1);
    //facade.moveSide(Facade::SIDE_LAB_SOUTH, -10, 0);
	
    //facade.recomputeSize();
    facadeMask.load(facade.getMask(), facade.getWidth(), facade.getHeight());
    
    facade.print();

    // load the xml file
    if(Config::instance().file != "")
    {
    	sceneManager.loadXmlFile(Config::instance().file);
    }
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

        sceneManager.draw();
    }
    
    facadeImage.load(facade.getFramebuffer(), facade.getWidth(), facade.getHeight());
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
        facade.send();
    }
}

void App::cleanup()
{
    receiver.stop();
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

        case 'r':
            if(Graphics::getMillis() - reloadTimestamp > 5000)
            {
                LOG << "Reloading xml file" << endl;
                sceneManager.closeXmlFile();
                sceneManager.clear(true);
                sceneManager.loadXmlFile();
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
