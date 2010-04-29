/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#include "UdpListener.h"

namespace visual {

UdpListener::UdpListener() : Thread("UdpListener", Thread::LOOP), _bSetup(false), _packet(NULL)
{
    Net::init();
}

UdpListener::UdpListener(unsigned int port) : Thread("UdpListener", Thread::LOOP),
     _bSetup(false), _packet(NULL)
{
    Net::init();

    setup(port);
}

UdpListener::~UdpListener()
{
    if(_packet != NULL)
        SDLNet_FreePacket(_packet);
}

void UdpListener::startListening()
{
    if(!_bSetup)
    {
        LOG_WARN << "UdpListener: Cannot start thread, port not set" << std::endl;
        return;
    }

    startThread();
}

void UdpListener::stopListening()
{
    if(!_bSetup)
        return;

    stopThread();
}

void UdpListener::setup(unsigned int port, unsigned int packetLen)
{
    if(isThreadRunning())
    {
        LOG_WARN << "UdpListener: Cannot set port while thread is running" << std::endl;
        return;
    }

    // allocate packet memory (if not allocated)
    if(_packet == NULL)
    {
        if(!(_packet = SDLNet_AllocPacket(packetLen)))
        {
            LOG_ERROR << "UdpListener: Could not allocate packet:" << SDLNet_GetError() << std::endl;
            return;
        }
    }

    _uiPort = port;

    // free the existing socket
    if(_bSetup)
    {
        SDLNet_UDP_Close(_socket);
    }

    // try to open the socket
	if(!(_socket = SDLNet_UDP_Open(_uiPort)))
	{
		LOG_ERROR << "UdpListener: Could not open socket on port " << _uiPort << ": "
                  <<  SDLNet_GetError() << std::endl;
		return;
	}

    _bSetup = true;
}

/* ***** Protected Functions ***** */

void UdpListener::run()
{
    // handle packets ...
    if(SDLNet_UDP_Recv(_socket, _packet) == true)
    {
        process(_packet);
    }

    usleep(10000);   // dont eat the cpu
}

} // namespace
