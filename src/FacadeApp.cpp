#include "FacadeApp.h"

FacadeApp::FacadeApp() : facade("192.168.5.59", 8080)
{}

FacadeApp::~FacadeApp()
{
    //dtor
}

void FacadeApp::init()
{

}

void FacadeApp::setup()
{
    _background.set(80, 80, 80);
    setFrameRate(25);

    LOG << std::endl;
    facade.print();
    facade.setBackground(0x000000);

    Side::drawOutlines(false);
}

void FacadeApp::update()
{
    facade.clear();
    facade.walkWindows(Color(255, 0, 0));
    facade.send();
}

void FacadeApp::draw()
{
    facade.pixel(15, 5, 0xFF00FF);

    facade.draw(0, 0);
    facade.drawGrid(0, 0);
}

void FacadeApp::cleanup()
{
}

void FacadeApp::keyPressed(SDLKey key, SDLMod mod)
{
    switch(key)
    {

        default:
            break;
    }
}
