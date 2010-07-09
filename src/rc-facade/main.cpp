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
	// parse the commandline
    if(!Config::instance().parseCommandLine(argc, argv))
    	return EXIT_FAILURE;
	
    // initialize SDL context
    //Graphics::init(1200, 400, 16, HARDWARE);
    //Graphics::init(946, 196, 16, HARDWARE);
    Graphics::init(1280, 196, 16, HARDWARE);


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

    return EXIT_SUCCESS;
}
