/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009

    SDL_net tutorial: http://gpwiki.org/index.php/SDL:Tutorial:Using_SDL_net
==============================================================================*/
#include "UdpSender.h"

#include <exception>

namespace visual {

UdpSender::UdpSender() : _bSetup(false), _packet(NULL)
{
    Net::init();
}

UdpSender::UdpSender(std::string addr, unsigned int port) :
    _bSetup(false), _packet(NULL)
{
    Net::init();

    setup(addr, port);
}

UdpSender::~UdpSender()
{
    if(_bSetup)
    {
        if(_packet != NULL)
            SDLNet_FreePacket(_packet);

        SDLNet_UDP_Close(_socket);
    }
}

void UdpSender::setup(std::string addr, unsigned int port)
{
    if(addr == _sAddr && port == _uiPort)
        return;

    _sAddr = addr;
    _uiPort = port;

    // free the existing socket
    if(_bSetup)
    {
        SDLNet_UDP_Close(_socket);
    }

    // try to open the socket
	if(!(_socket = SDLNet_UDP_Open(0)))
	{
		LOG_ERROR << "UdpSender: Could not open socket on port " << _uiPort << ": "
                  <<  SDLNet_GetError() << std::endl;
		return;
	}

	// Resolve server name
	if(SDLNet_ResolveHost(&_destination, _sAddr.c_str(), _uiPort) == -1)
	{
	    LOG_ERROR << "UdpSender: Could not resolve hostname " << _sAddr
                  << " on port " <<  _uiPort<< ": " << SDLNet_GetError() << std::endl;
		return;
	}
}

bool UdpSender::send(char* buffer, unsigned int length)
{
    if(buffer == NULL || _socket == NULL)
        return false;

    // allocate packet memory (if not allocated)
    if(_packet == NULL)
    {
        if(!(_packet = SDLNet_AllocPacket(VISUAL_MAX_PACKET_LEN)))
        {
            LOG_ERROR << "UdpSender: Could not allocate packet:" << SDLNet_GetError() << std::endl;
            return false;
        }
    }

    unsigned int position = 0, numSend = 0;
    while(position < length)
    {
        // how many bytes to send?
        numSend = length - position;
        if(numSend > VISUAL_MAX_PACKET_LEN)
        {
            numSend = VISUAL_MAX_PACKET_LEN;
        }

        // load packet
        try
        {
            _packet->len = numSend;
            _packet->maxlen = VISUAL_MAX_PACKET_LEN;
            memcpy(_packet->data, buffer+position, numSend);
        }
        catch(std::exception& e)
        {
            LOG_ERROR << "UdpSender: memcpy failed to load packet: " << e.what() << std::endl;
            return false;
        }

        // send
		if(!send(_packet))
		{
		    return false;
		}

		// move index position
		position += numSend;
	}

    return true;
}

bool UdpSender::send(UDPpacket* packet)
{
    if(_socket == NULL)
        return false;

    if(packet == NULL)
    {
        LOG_WARN << "UdpSender: Send error: Packet is NULL" << std::endl;
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
