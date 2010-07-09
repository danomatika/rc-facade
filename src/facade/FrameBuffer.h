/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#ifndef FRAMEUFFER_APP_H
#define FRAMEBUFFER_APP_H

#include <visualframework/visualframework.h>
#include <stdint.h>

#define FACADE_PKG_SIZE     5
#define FACADE_NUM_ADDR     1085
#define FACADE_OFFSET_RED   2
#define FACADE_OFFSET_GREEN 3
#define FACADE_OFFSET_BLUE  4

/// implements the interface to the facade simulator
class FrameBuffer
{
    public:

        FrameBuffer();

        FrameBuffer(std::string ip, unsigned int port);

        ~FrameBuffer();

        /// set the ip and port
        void setup(std::string ip, unsigned int port);

        /// clear the framebuffer with a certain color, does alpha
        void clear(uint32_t color);

        /// set all packages to the same color, uses alpha as blend amount if belnd is on
        void setColor(uint32_t color);

        /// set package at address to color, uses alpha as blend amount if belnd is on
        void setColor(int address, uint32_t color);

        /// get the color from a specific address package
        uint32_t getColor(int address);

        /// interface to send the complete UDP packet
        virtual void flush();// = 0;

        // enable blending?
        inline void blend(bool yesno) {_bBlend = yesno;}

	private:

        void allocate();

		// facade framebuffer
        uint8_t _facadeFB[FACADE_PKG_SIZE*FACADE_NUM_ADDR];
        
        visual::UdpSender _sender;
        UdpPacket* _packet;

        bool _bBlend;
};

#endif // FRAMEBUFFER_APP_H
