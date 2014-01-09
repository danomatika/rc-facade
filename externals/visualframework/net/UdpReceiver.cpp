/*==============================================================================

	UdpReceiver.cpp

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
#include "UdpReceiver.h"

namespace visual {

UdpReceiver::UdpReceiver() : Thread("UdpReceiver"),
	_uiPort(0), _packet(NULL)
{
	Net::init();
	_socket = NULL;
}

UdpReceiver::UdpReceiver(unsigned int port) : Thread("UdpReceiver"),
	 _packet(NULL)
{
	Net::init();
	_socket = NULL;
	setup(port);
}

UdpReceiver::~UdpReceiver()
{
	if(!_packet)
		SDLNet_FreePacket(_packet);
}

bool UdpReceiver::setup(unsigned int port, unsigned int len)
{
	if(threadIsRunning())
	{
		LOG_WARN << "UdpReceiver: Cannot set port while thread is running" << std::endl;
		return false;
	}

	// allocate packet memory (if not allocated)
	if(!_packet)
	{
		if(!(_packet = SDLNet_AllocPacket(len)))
		{
			LOG_ERROR << "UdpReceiver: Could not allocate packet:" << SDLNet_GetError() << std::endl;
			return false;
		}
	}
	
	// clear socket
	if(_socket)
		SDLNet_UDP_Close(_socket);

	// try to open the socket
	if(!(_socket = SDLNet_UDP_Open(port)))
	{
		LOG_ERROR << "UdpReceiver: Could not open socket on port " << port << ": "
				  <<  SDLNet_GetError() << std::endl;
		return false;
	}

	_uiPort = port;
	return true;
}

const uint8_t* UdpReceiver::getData()
{
	return _packet->data;
}

unsigned int UdpReceiver::getDataLen()
{
	return _packet->len;
}

/* ***** THREADED POLLING ***** */

void UdpReceiver::start()
{
	Thread::start();
}

void UdpReceiver::stop()
{
	Thread::stop();
}

void UdpReceiver::lock()	{Thread::lock();}
void UdpReceiver::unlock()	{Thread::unlock();}

/* ***** MANUAL POLLING ***** */

bool UdpReceiver::receivePacket()
{
	if(threadIsRunning())
	{
		LOG_WARN << "UdpReceiver: Cannot receive Packet while thread is running" << std::endl;
		return 0;
	}
	
	int ret = SDLNet_UDP_Recv(_socket, _packet);
	if(ret < 0)
	{
		LOG_ERROR << "UdpReceiver: Cannot receive: " << SDLNet_GetError() << std::endl;
	}
	return (bool) ret;
}

/* ***** PROTECTED ***** */

void UdpReceiver::run()
{
	while(threadIsRunning())
	{
		int ret = SDLNet_UDP_Recv(_socket, _packet);
		if(ret < 0)
		{
			LOG_ERROR << "UdpReceiver: receive error: " << SDLNet_GetError() << std::endl;
			break;
		}
		else if(ret)
		{
			lock();
			process(_packet->data, _packet->len);
			unlock();
		}
		SDL_Delay(20);   // dont eat the cpu
	}
}

} // namespace
