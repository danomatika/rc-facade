/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#include "FacadeApp.h"

#include "facade/Facade.h"

#define OSC_BASE_ADDR   "/visual/facade"

FacadeApp::FacadeApp() : OscObject(""), bRunning(true),
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

FacadeApp::~FacadeApp()
{}

void FacadeApp::init()
{
    // setup the osc listener
    receiver.setup(7000);
    receiver.start();

    // setup the facade
    LOG << endl;
    //facade.setup("192.168.7.121", 8080);
    facade.setup("192.168.5.73", 8080);
    //facade.setClearColor(0xFFFF00);//Color(40, 40, 40));
    facade.setWindowSize(7);
    facade.drawOutlines(false);

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
    facade.moveSide(Facade::SIDE_MAIN_SOUTH_STREET, -9, 0);
    facade.moveSide(Facade::SIDE_LAB_SOUTH, -10, 0);
	*/
    //facade.recomputeSize();
    
    facade.print();

    // load the xml file
    if(Config::instance().file != "")
    {
    	sceneManager.loadXmlFile(Config::instance().file);
    }
}

void FacadeApp::setup()
{
    setBackground(0x505050);
    setFrameRate(25);
    
    sceneManager.setup();
}

void FacadeApp::update()
{
    if(bRunning)
    {
        facade.clear();

        sceneManager.draw();
    }
}

void FacadeApp::draw()
{
    facade.draw(0, 0, bDebug);

//    if(bDebug
//        facade.drawGrid(100, 100, bDebug);

    if(bRunning)
        facade.send();
}

void FacadeApp::cleanup()
{
    receiver.stop();
}

void FacadeApp::keyPressed(SDLKey key, SDLMod mod)
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
            break;

        //case 's':
        //    sceneManager.saveXmlFile("../data/testout.xml");
        //    break;

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

bool FacadeApp::processOscMessage(const osc::ReceivedMessage& message,
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
