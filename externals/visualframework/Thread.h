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

namespace visual {

class Thread
{
    public:

        enum Type {
            NORMAL, // run run() once
            LOOP    // loop run() and wait for stopThread()
        };

        Thread(std::string name, Type type=NORMAL);

        virtual ~Thread();

        void startThread();

        void stopThread();

        void waitThread();

        void killThread();

        bool isThreadRunning() {return _bRun;}

        int getThreadID();

        std::string getThreadName() {return _name;}

    protected:

        virtual void run() = 0;

    private:

        void _run();

        static int threadFunc(void* data);

        SDL_Thread* _thread;
        bool _bRun;
        Type _type;
        std::string _name;
};

} // namespace

#endif // VISUAL_THREAD_H
