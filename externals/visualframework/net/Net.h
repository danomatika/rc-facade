/*==============================================================================

	Net.h

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
#ifndef VISUAL_NET_H
#define VISUAL_NET_H

#include "../Common.h"

#define VISUAL_MAX_PACKET_LEN   1024

// udp
#include "UdpSender.h"
#include "UdpListener.h"

typedef UDPpacket UdpPacket;

namespace visual {

class Net
{
    public:

        /// init SDL_net
        static bool init();

        /// quit SDL_net
        static void quit();

        /// has SDL_net been setup?
        static bool isSetup()   {return _bSetup;}
/*
        /// allocates a udp packet, clears if existing
        static bool allocatePacket(UDPpacket* packet, unsigned int length=VISUAL_MAX_PACKET_LEN);

        /// free's a udp packet
        static void freePacket(UDPpacket* packet);
*/
        /// get the SDL_net error as a string
        static std::string getError();

    private:

        Net() {}
        virtual ~Net() {}

        static bool _bSetup;
        static std::string _error;
};

} // namespace

#endif // VISUAL_NET_H
