/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#include <iostream>
#include <unistd.h>
#include <string>

#include "Common.h"

#include "FacadeApp.h"

int main(int argc, char *argv[])
{
    // initialize SDL context
    Graphics::init(946, 196, 16, Graphics::HARDWARE);

    // initialize app
    FacadeApp facade;
    facade.init();

    // set icon and open window
    Graphics::setWindowIcon("../data/icon.bmp");
    Graphics::createWindow("rc-facade");

    // setup sdl resources
    facade.setup();

    // main app loop
    facade.mainLoop();

    // cleanup after exit from loop
    facade.cleanup();

    return 0;
}
