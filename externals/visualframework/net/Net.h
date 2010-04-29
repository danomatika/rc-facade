/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
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
