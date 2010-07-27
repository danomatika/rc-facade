/*==============================================================================

	UdpReceiver.h

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
#ifndef VISUAL_UDP_RECEIVER_H
#define VISUAL_UDP_RECEIVER_H

#include "Net.h"
#include "../Thread.h"

#include <SDL/SDL_net.h>

namespace visual {

typedef UDPpacket UdpPacket;

/**
    \class  UdpReceiver
    \brief  a threaded UDP listener

    set the processing function to process incoming bytes
**/
class UdpReceiver : protected Thread
{
    public:

        UdpReceiver();
        virtual ~UdpReceiver();

        /// calls setup automatically
        UdpReceiver(unsigned int port);

        /// setup the udp socket using the given port, returns true on success
        bool setup(unsigned int port, unsigned int len=1024);

		/// get the packet data, make sure to lock first if using the thread!
        const uint8_t* getData();
        
        /// get the data length
        unsigned int getDataLen();

		/* ***** THREADED POLLING ***** */

        /// start the listening thread, opens connection
        void start();

        /// stop the listening thread, closes connection
        void stop();
        
        /// lock/unlock the packet data
        void lock();
        void unlock();

		/* ***** MANUAL POLLING ***** */
        
        /**
        	\brief	manually check for incoming packets, nonblocking
            \return	true if a packet was received
            
            note: the address must be set using setup(), this cannot be called
            while the thread is running
        */
        bool receivePacket();
        
        /* ***** UTIL ***** */

        /// is the thread running?
        inline bool isListening() {return threadIsRunning();}

        /// get port num
        inline unsigned int getPort() {return _uiPort;}

    protected:

        /// received packet callback, automaitcally locks the packet
        virtual void process(const uint8_t* data, unsigned int len) {}

    private:

        // thread function
        void run();

        bool _bSetup;

        unsigned int _uiPort;

        UDPsocket   _socket;
        UDPpacket*  _packet;
};

} // namespace

#endif // VISUAL_UDP_RECEIVER_H
