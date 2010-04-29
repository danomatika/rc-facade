/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
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

        /// calls setAddr automatically
        UdpSender(std::string addr, unsigned int port=8000);

        /// setup the udp socket using the given port
        void setup(std::string addr="127.0.0.1", unsigned int port=8000);

        /// send the message
        bool send(char* buffer, unsigned int length);

        /// send a packet
        bool send(UDPpacket* packet);

        /// get the ip addr and port
        std::string getAddr()   {return _sAddr;}
        unsigned int getPort() {return _uiPort;}

    private:

        bool _bSetup;

        unsigned int _uiPort;
        std::string _sAddr;

        IPaddress   _destination;
        UDPsocket   _socket;
        UDPpacket*  _packet;
};

} // namespace

#endif // VISUAL_UDP_SENDER_H
