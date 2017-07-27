/*==============================================================================

main.cpp

facade-simulator: a simple 2d simulator for the AEC facade

Copyright (C) 2010  Dan Wilcox <danomatika@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/
#include <iostream>
#include <unistd.h>
#include <string>

#include "Common.h"

#include "Config.h"
#include "App.h"

using namespace visual;

int main(int argc, char *argv[])
{
	Config& config = Config::instance();
	
	// parse the commandline
	if(!config.parseCommandLine(argc, argv))
		return EXIT_FAILURE;
	
	// initialize SDL context
	// set window size based on facade grid size
	Graphics::init(config.getFacade().getDrawWidth(),
	              config.getFacade().getDrawHeight(),
	              32, HARDWARE);

	// initialize app
	App app;
	if(!app.init())
		return EXIT_FAILURE;

	// set icon and open window
	//Graphics::setWindowIcon("../data/icon.bmp");
	Graphics::createWindow("facade-simulator");

	// setup sdl resources
	app.setup();

	// main app loop
	app.mainLoop();

	// cleanup after exit from loop
	app.cleanup();

	return EXIT_SUCCESS;
}
