/*==============================================================================

	Thread.h

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
#ifndef VISUAL_THREAD_H
#define VISUAL_THREAD_H

#include "Common.h"

#include "SDL/SDL_thread.h"
#include "SDL/SDL_mutex.h"

namespace visual {

class Thread
{
	public:

		/// create the thread, name and type
		Thread(std::string name);
		virtual ~Thread();

		/// start the thread
		virtual void start();

		/// stop the thread, wait for it to finish
		virtual void stop();

		/// kill this thread
		virtual void kill();
		
		/// lock the mutex
		void lock();
		
		/// unlock the mutex
		void unlock();

		/// is the thread currently running?
		inline bool threadIsRunning() {return _bRun;}

		/// get this thread's ID
		int getThreadID();

		/// get the thread's name
		inline std::string getThreadName() {return _name;}

	protected:

		/// thread callback function
		virtual void run() = 0;

	private:

		/// thread runner
		static int threadFunc(void* data);

		SDL_Thread* _thread;
		SDL_mutex*	_lock;
		bool _bRun;
		std::string _name;
};

} // namespace

#endif // VISUAL_THREAD_H
