/*==============================================================================

	UdpSender.cpp

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

	SDL_net tutorial: http://gpwiki.org/index.php/SDL:Tutorial:Using_SDL_net
	
==============================================================================*/
#include "UdpSender.h"

#include <exception>

namespace visual {

UdpSender::UdpSender() : _packet(NULL)
{
	Net::init();
	_socket = NULL;
}

UdpSender::UdpSender(std::string addr, unsigned int port) : _packet(NULL)
{
	Net::init();
	_socket = NULL;
	setup(addr, port);
}

UdpSender::~UdpSender()
{
	if(_packet)
		SDLNet_FreePacket(_packet);
	if(_socket)
		SDLNet_UDP_Close(_socket);
}

bool UdpSender::setup(std::string addr, unsigned int port, unsigned int len)
{
	if(addr == _sAddr && port == _uiPort)
		return false;

	if(_packet)
		SDLNet_FreePacket(_packet);

	// allocate packet memory
	if(!(_packet = SDLNet_AllocPacket(len)))
	{
		LOG_ERROR << "UdpSender: Could not allocate packet:" << SDLNet_GetError() << std::endl;
		return false;
	}

	if(_socket)
		SDLNet_UDP_Close(_socket);

	// try to open the socket
	if(!(_socket = SDLNet_UDP_Open(0)))
	{
		LOG_ERROR << "UdpSender: Could not open socket on port " << port << ": "
				  <<  SDLNet_GetError() << std::endl;
		return false;
	}

	// Resolve server name
	if(SDLNet_ResolveHost(&_destination, addr.c_str(), port) == -1)
	{
		LOG_ERROR << "UdpSender: Could not resolve hostname " << addr
				  << " on port " <<  port<< ": " << SDLNet_GetError() << std::endl;
		return false;
	}
	
	_sAddr = addr;
	_uiPort = port;
	
	return true;
}

bool UdpSender::send(const uint8_t* data, unsigned int len)
{
	assert(data);	// data should not be NULL

	// allocate packet memory (if not allocated)
	if(!_packet || _packet->maxlen < (int) len)
	{
		if(_packet)
			SDLNet_FreePacket(_packet);
		if(!(_packet = SDLNet_AllocPacket(len)))
		{
			LOG_ERROR << "UdpSender: Could not allocate packet:" << SDLNet_GetError() << std::endl;
			return false;
		}
	}

	// load packet
	try
	{
		_packet->len = len;
		memcpy(_packet->data, data, len);
	}
	catch(std::exception& e)
	{
		LOG_ERROR << "UdpSender: Failed to load packet: " << e.what() << std::endl;
		return false;
	}

	// send
	if(!send(_packet))
	{
		return false;
	}

	return true;
}

bool UdpSender::send(UDPpacket* packet)
{
	assert(packet);	// packet should not be NULL
	
	if(!_socket)
	{
		LOG_WARN << "UdpSender: Cannot send, socket not setup" << std::endl;
		return false;
	}

	// load packet destination
	packet->address.host = _destination.host;
	packet->address.port = _destination.port;

	// send
	if(SDLNet_UDP_Send(_socket, -1, packet) == 0)
	{
		std::string err = SDLNet_GetError();
		if(err != "")
		{
			LOG_WARN << "UdpSender: Send error: " <<  err << std::endl;
			return false;
		}
	}

	return true;
}

} // namespace
