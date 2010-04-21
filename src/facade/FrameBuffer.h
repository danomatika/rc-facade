/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#ifndef FRAMEUFFER_APP_H
#define FRAMEBUFFER_APP_H

#include <visualframework/visualframework.h>

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
        void clear(visual::Color color);

        /// set all packages to the same color, uses alpha as blend amount if belnd is on
        void setColor(visual::Color color);

        /// set package at address to color, uses alpha as blend amount if belnd is on
        void setColor(int _address, visual::Color color);

        /// get the color from a specific address package
        visual::Color getColor(int _address);

        /// send the complete UDP packet
        void flush();

        static void blend(bool yesno) {_bBlend = yesno;}

	private:

        void allocate();

        char _frameBuffer[FACADE_PKG_SIZE*FACADE_NUM_ADDR];
        visual::UdpSender _sender;
        UdpPacket* _packet;

        static bool _bBlend;
};

#endif // FRAMEBUFFER_APP_H
