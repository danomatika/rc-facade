/*==============================================================================

	Application.h

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
#ifndef VISUAL_APPLICATION_H

#include "Common.h"

#include "Timer.h"

namespace visual {

class Application
{
	public:

		Application();
		virtual ~Application();

		/* ***** SETUP ***** */

		/// initialization, call before creating sdl window
		virtual bool init() {return true;}

		/// sdl resource setup, call after creating sdl window
		virtual void setup() = 0;

		/// start the main run loop
		void mainLoop();

		/* ***** MAIN CALLBACKS ***** */

		virtual void update() = 0;

		virtual void draw() = 0;

		virtual void cleanup() {};

		/* ***** INPUT CALLBACKS ***** */

		virtual void keyPressed(SDLKey key, SDLMod mod) {}

		virtual void keyReleased(SDLKey key, SDLMod mod) {}

		virtual void mousePressed(int button, int x, int y) {}

		virtual void mouseReleased(int button, int x, int y) {}

		virtual void mouseMotion(int x, int y, int xRel, int yRel) {}

		/* ***** UTIL ***** */

		/// set the target framerate
		void setFrameRate(float frameRate);
		
		/// get the current framerate
		inline float getFrameRate() {return _currentFps;}

		/// get/set the background clear color
		inline Color& getBackground() {return _background;}
		void setBackground(Color color) {_background = color;}
		void setBackground(unsigned int color) {_background.set(color);}

		/// get/set the debug state
		inline bool getDebug() {return bDebug;}
		inline void setDebug(bool yesno) {bDebug = yesno;}
		inline void toggleDebug() {bDebug = !bDebug;}

		/// tell mainLoop to exit
		inline void exitMainLoop() {_bRun = false;}

	protected:

		bool bDebug;    /// is debug mode on?
		
		/// input variables set in event callbacks
		int mouseButton;		/// mouse button
		bool bMousePressed;		/// is the mouse being pressed?
		int mouseX, mouseY;		/// mouse pos
		int motionX, motionY;	/// relative motion from last position

	private:

		// processes sdl events to input callbacks
		void _events();

		// main sdl loop, calls draw, update, etc
		void _draw();

		bool _bRun;          /// is the main loop running?
		float _frameRate;    /// frame rate target in FPS
		float _frameRateMs;  /// frame rate delay in ms
		Timer _frameRateTimer;	 /// frame rate timer
		Color _background;   /// back ground color
		
		float _currentFps;				/// current fps
		Timer _currentFpsTimer;			/// timer for measuring current fps
		unsigned int _currentFpsFrames;	/// number of frames since last check
};

} // namespace

#endif // VISUAL_APPLICATION_H
