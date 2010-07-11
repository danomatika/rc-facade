/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#include <iostream>
#include <unistd.h>
#include <string>

#include "Common.h"

#include "App.h"

using namespace visual;

int main(int argc, char *argv[])
{
	Config& config = Config::instance();
    
	// parse the commandline
    if(!config.parseCommandLine(argc, argv))
    	return EXIT_FAILURE;
	
    // initialize SDL context
    // ste window size based on facade grid size
    Graphics::init(config.getFacade().getDrawWidth(),
                   config.getFacade().getDrawHeight(),
                   32, HARDWARE);

    // initialize app
    App facadeApp;
    facadeApp.init();

    // set icon and open window
    //Graphics::setWindowIcon("../data/icon.bmp");
    Graphics::createWindow("rc-facade");

    // setup sdl resources
    facadeApp.setup();

    // main app loop
    facadeApp.mainLoop();

    // cleanup after exit from loop
    facadeApp.cleanup();

    return EXIT_SUCCESS;
}
