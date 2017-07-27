/*==============================================================================

App.h

rc-facade: a simple 2d graphics engine for the AEC facade

Copyright (C) 2009, 2010  Dan Wilcox <danomatika@gmail.com>

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

#include "SceneManager.h"

using namespace std;

class App : public visual::Application, public OscObject
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

    protected:

        /// osc callback
        bool processOscMessage(const osc::ReceivedMessage& message,
								  const osc::MessageSource& source);

    private:

        bool bRunning;  // running or paused?

		Config& config;
		
        Facade& facade;
        OscReceiver& receiver;
        SceneManager sceneManager;
        
        visual::Image facadeImage;
        visual::Image facadeMask;

        unsigned int reloadTimestamp;
};

#endif // APP_H
