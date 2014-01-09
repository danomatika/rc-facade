/*==============================================================================

	Application.cpp

	visualframework: a simple 2d graphics framework
  
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
#include "Application.h"

#include "graphics/Font.h"

#define VISUAL_APP_SLEEP_MS 25	// how long to sleep while waiting to draw
#define VISUAL_APP_FRAMES	5	// number of frames calc current fps

namespace visual {

Application::Application() : bDebug(false),
	mouseButton(0), bMousePressed(false),
	mouseX(0), mouseY(0), motionX(0), motionY(0),
	_bRun(true), _frameRate(0), _background(0, 0, 0, 255),
	_currentFps(0.0), _currentFpsFrames(0)
{
	_frameRateMs = 0; 	// no timing
	
	Font::initTTF();	// start font
}

Application::~Application()
{
	Font::cleanupTTF();	// stop font
}

/* ***** SETUP ***** */

void Application::mainLoop()
{
	// start fps cal timer
	_currentFpsTimer.set();

	// program main loop
	while(_bRun)
	{
		_frameRateTimer.set();
		
		// calc current fps
		_currentFpsFrames++;
		if(_currentFpsFrames >= VISUAL_APP_FRAMES)
		{
			_currentFps = (float) _currentFpsFrames/(_currentFpsTimer.getDiff()/1000.0f);
			_currentFpsFrames = 0;
			_currentFpsTimer.set();
		}
	
		update();   // call the user update function
		_events();  // handle events and do framerate idling
		_draw();  	// render a frame
		
		// idle the frame rate
		if(_frameRateTimer.getDiff() < _frameRateMs)
		{
			SDL_Delay(_frameRateMs - _frameRateTimer.getDiff());
		}
	}
}

/* ***** UTIL ***** */

void Application::setFrameRate(float frameRate)
{
	if(frameRate < 0)
		return;

	_frameRate = frameRate;

	// no delay?
	if(frameRate == 0)
	{
		_frameRateMs = 0;
		return;
	}

	_frameRateMs = 1000/_frameRate;   // delay = 1000 ms / fps
}

/* ***** PRIVATE FUNCTIONS ***** */

void Application::_draw()
{    
	// clear background
	Graphics::clear(_background);
	
	// user render function
	draw();

	// swap buffers
	Graphics::swap();
}

void Application::_events()
{
	// do message processing while waiting for next frame
/*    while(_frameRateTimer.getDiff() <= _frameRateMs)
	{
*/      // message processing loop
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			// check for messages
			switch(event.type)
			{
				// stop the main loop on quit
				case SDL_QUIT:
					_bRun = false;
					break;

				case SDL_KEYDOWN:
				{
					switch(event.key.keysym.sym)
					{
						// exit if ESCAPE is pressed
						case SDLK_ESCAPE:
							_bRun = false;
							break;

						case SDLK_RETURN:
							// toggle fullscreen on ALT+ENTER
							if(event.key.keysym.mod & KMOD_ALT)
								Graphics::toggleFullscreen();
							// don't break so SDLK_RETURN goes to keyPressed

						default:
							keyPressed(event.key.keysym.sym, event.key.keysym.mod);
							break;
					}
					break;
				}
				
				case SDL_KEYUP:
				{
					keyReleased(event.key.keysym.sym, event.key.keysym.mod);
					break;
				}

				case SDL_MOUSEMOTION:
				{
					mouseX = event.motion.x;
					mouseY = event.motion.y;
					motionX = event.motion.xrel;
					motionY = event.motion.yrel;
					mouseMotion(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
					break;
				}

				case SDL_MOUSEBUTTONDOWN:
				{
					mouseButton = event.button.button;
					bMousePressed = true;
					mousePressed(event.button.button, event.button.x, event.button.y);
					break;
				}
				
				case SDL_MOUSEBUTTONUP:
				{
					bMousePressed = false;
					mouseReleased(event.button.button, event.button.x, event.button.y);
					break;
				}

			} // end switch
		} // end of message processing

		//SDL_Delay(VISUAL_APP_SLEEP_MS); // msec for the scheduler
//    }
}

} // namespace
