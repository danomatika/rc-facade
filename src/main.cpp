#include <iostream>
#include <unistd.h>
#include <string>

#include "Common.h"

#include "FacadeApp.h"
#include "facade/FacadeSample.h"

using namespace std;
using namespace visual;

int main(int argc, char *argv[])
{
    // initialize SDL context
    Graphics::init(1024, 200, 16, Graphics::HARDWARE);

    // initialize app
    FacadeApp facade;
    facade.init();

    // open sdl window
    Graphics::createWindow("rc-facade");

    // setup sdl resources
    facade.setup();

    // main app loop
    facade.mainLoop();

    // cleanup after exit from loop
    facade.cleanup();

    return 0;
}
