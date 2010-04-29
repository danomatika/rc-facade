/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#include "Thread.h"

namespace visual {

Thread::Thread(std::string name, Type type) :
    _thread(NULL), _bRun(false), _type(type), _name(name)
{
    //ctor
}

Thread::~Thread()
{
    // still running?
    if(isThreadRunning())
    {
        killThread();
        LOG_ERROR << "Thread::~Thread(): Thread \"" << _name
                  << "\" id " << getThreadID()
                  << " still running, killed" << std::endl;
    }
}

void Thread::startThread()
{
    if(_bRun == true)
    {
        LOG_WARN << "Thread::start(): Thread \"" << _name
                 << "\" id " << getThreadID()
                 << " already running" << std::endl;
        return;
    }

    _bRun = true;

    // send this pointer as thread data
    SDL_CreateThread(&threadFunc, this);
}

void Thread::stopThread()
{
    if(_thread == NULL) //|| _type == NORMAL)
        return;

    _bRun = false;
}

void Thread::waitThread()
{
    if(_thread == NULL)
        return;

    _bRun = false;
    SDL_WaitThread(_thread, NULL);
}

void Thread::killThread()
{
    if(_thread == NULL)
        return;

    _bRun = false;
    SDL_KillThread(_thread);
}

int Thread::getThreadID()
{
    return SDL_GetThreadID(_thread);
}

void Thread::_run()
{
    if(_type == LOOP) // repeat
    {
        while(_bRun)
        {
            run();
        }
    }
    else    // run once
    {
        run();
    }

    _bRun = false;
}

int Thread::threadFunc(void* data)
{
    // thread pointer as data
    Thread* t = (Thread*) data;
    t->_run();

    return 0;
}

} // namespace
