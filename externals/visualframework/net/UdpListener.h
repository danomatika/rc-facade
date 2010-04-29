/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#ifndef VISUAL_UDP_LISTENER_H
#define VISUAL_UDP_LISTENER_H

#include "Net.h"
#include "../Thread.h"

#include <SDL/SDL_net.h>

namespace visual {

/**
    \class  UdpListener
    \brief  a threaded UDP listener

    set the processing function to process incoming bytes
**/
class UdpListener : protected Thread
{
    public:

        UdpListener();
        virtual ~UdpListener();

        /// calls setup automatically
        UdpListener(unsigned int port);

        /// setup the udp socket using the given port
        void setup(unsigned int port, unsigned int packetLen=VISUAL_MAX_PACKET_LEN);

        /// start the listening thread, opens connection
        void startListening();

        /// stop the listening thread, closes connection
        void stopListening();

        /// is the thread running?
        bool isListening() {return isThreadRunning();}

        /// get port num
        unsigned int getPort() {return _uiPort;}

    protected:

        /// callback to implement
        virtual void process(UDPpacket* packet) = 0;

    private:

        // thread main loop
        void run();

        bool _bSetup;

        unsigned int _uiPort;
        std::string _sAddr;

        UDPsocket   _socket;
        UDPpacket*  _packet;
};

} // namespace

#endif // VISUAL_UDP_LISTENER_H
