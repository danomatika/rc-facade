/*==============================================================================

App.h

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
#ifndef APP_H
#define APP_H

#include "Common.h"

#include "../common/Facade.h"

using namespace std;

class App : public visual::Application, public visual::UdpReceiver
{
	public:

		App();

		virtual ~App();

		bool init();

		void setup();

		void update();

		void draw();

		void cleanup();

		void keyPressed(SDLKey key, SDLMod mod);

	private:

		Facade& facade;

		visual::Image facadeImage;
		visual::Image facadeMask;
		
		visual::UdpReceiver receiver;

		unsigned int reloadTimestamp;
};

#endif // APP_H
