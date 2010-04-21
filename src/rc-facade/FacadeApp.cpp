/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#include "FacadeApp.h"

#include "facade/Facade.h"

#define OSC_BASE_ADDR   "/visual/facade"

FacadeApp::FacadeApp() : OscObject(""), bRunning(true),
    facade(Config::getFacade()), receiver(Config::getReceiver()),
    reloadTimestamp(0)
{
    // set osc addresses
    setOscRootAddress(OSC_BASE_ADDR);
    receiver.setOscRootAddress(OSC_BASE_ADDR);
    sceneManager.setOscRootAddress(OSC_BASE_ADDR);

    receiver.addOscObject(this);
    //receiver.addOscObject(&sceneManager);
    
    reloadTimestamp = Graphics::getMillis();
}

FacadeApp::~FacadeApp()
{
    //dtor
}

void FacadeApp::init()
{
    // setup the osc listener
    receiver.setup(7000);
    receiver.start();

    // setup the facade
    LOG << endl;
    //facade.setup("192.168.7.121", 8080);
    facade.setup("192.168.5.79", 8080);
    facade.setClearColor(Color(40, 40, 40, 127));
    facade.setWindowSize(7);
    facade.drawOutlines(false);

    // move some sides
    facade.setSidePos(Facade::SIDE_LAB_EAST, 0, 18);
    facade.setSidePos(Facade::SIDE_LAB_NORTH, 5, 17);

    facade.setSidePos(Facade::SIDE_MAIN_SOUTH, 0, 0);
    facade.setSidePos(Facade::SIDE_MAIN_EAST, 0, 0);
    facade.setSidePos(Facade::SIDE_MAIN_NORTH, 0, 0);

    facade.recomputeSize();

    facade.print();

    // load the xml file
    sceneManager.loadXmlFile("../data/CloseEncounters.xml");
}

void FacadeApp::setup()
{
    setBackground(0x505050);
    setFrameRate(25);
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
    facade.draw(0, 0);

    if(bDebug)
        facade.drawGrid(0, 0);

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

        case 's':
            sceneManager.saveXmlFile("../data/testout.xml");
            break;

        case 'r':
            if(Graphics::getMillis() - reloadTimestamp > 5000)
            {
                LOG << "Reloading xml file" << endl;
                sceneManager.closeXmlFile();
                sceneManager.clear();
                sceneManager.loadXmlFile("../data/CloseEncounters.xml");
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

bool FacadeApp::processOscMessage(const osc::ReceivedMessage& message,
								  const osc::MessageSource& source)
{
	LOG_DEBUG << "received " << message.path() << " " << message.types() << std::endl;
    
    if(message.path() == getOscRootAddress() + "/scene")
    {
        //osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();

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

    else if(message.path() == getOscRootAddress() + "/quit")
    {
        stop();
        return true;
    }

    return false;
}
