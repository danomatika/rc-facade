/*==============================================================================

	UdpSender.h

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
#ifndef VISUAL_UDP_SENDER_H
#define VISUAL_UDP_SENDER_H

#include "Net.h"
#include "../Thread.h"

#include <SDL/SDL_net.h>

namespace visual {

class UdpSender
{
    public:

        UdpSender();
        virtual ~UdpSender();

        /// calls setup automatically
        UdpSender(std::string addr, unsigned int port);

        /// setup the udp socket using the given port
        /// optionally set the max packet len
        bool setup(std::string addr, unsigned int port, unsigned int len=1024);

        /// send the message
        bool send(const uint8_t* data, unsigned int len);

        /// send a packet
        bool send(UDPpacket* packet);

        /// get the ip addr and port
        std::string getAddr()   {return _sAddr;}
        unsigned int getPort()	{return _uiPort;}

    private:

        unsigned int _uiPort;
        std::string _sAddr;

        IPaddress   _destination;
        UDPsocket   _socket;
        UDPpacket*  _packet;
};

} // namespace

#endif // VISUAL_UDP_SENDER_H
