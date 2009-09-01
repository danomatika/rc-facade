/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#include "FacadeApp.h"

#include "facade/Facade.h"

FacadeApp::FacadeApp() : bRunning(true),
    facade(Config::getFacade()), listener(Config::getListener()),
    reloadTimestamp(0)
{
    // set osc addresses
    listener.setOscRootAddress("/visual/facade");
    sceneManager.setOscRootAddress("/visual/facade");

    listener.addObject(&sceneManager);

    reloadTimestamp = Graphics::getMillis();
}

FacadeApp::~FacadeApp()
{
    //dtor
}

void FacadeApp::init()
{
    // setup the osc listener
    listener.setup(7000);
    listener.startListening();

    // setup the facade
    LOG << endl;
    facade.setup("192.168.5.59", 8080);
    facade.setClearColor(Color(40, 40, 40, 127));
    facade.setWindowSize(7);
    facade.drawOutlines(false);

    // move some sides
    facade.setSidePos(Facade::SIDE_LAB_EAST, 0, 18);
    facade.setSidePos(Facade::SIDE_LAB_NORTH, 5, 17);
    facade.recomputeSize();

    facade.print();

    // load the xml file
    sceneManager.loadXmlFile("../data/testScene.xml");
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
    listener.stopListening();
}

void FacadeApp::keyPressed(SDLKey key, SDLMod mod)
{
    switch(key)
    {
        case 'p':
            bRunning = !bRunning;
            listener.ignoreMessages(!bRunning);
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
                sceneManager.loadXmlFile("../data/testScene.xml");
            }
            break;

        default:
            break;
    }
}
