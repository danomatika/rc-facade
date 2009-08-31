/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#ifndef FRAMEUFFER_APP_H
#define FRAMEBUFFER_APP_H

#include <visualframework.h>

#define FACADE_PKG_SIZE     5
#define FACADE_NUM_ADDR     1085
#define FACADE_OFFSET_RED   2
#define FACADE_OFFSET_GREEN 3
#define FACADE_OFFSET_BLUE  4

/// implements the interface to the facade simulator
class FrameBuffer
{
    public:

        FrameBuffer() : _sender()
        {
            allocate();
        }

        FrameBuffer(std::string ip, unsigned int port) : _sender()
        {
            _sender.setup(ip, port);
            allocate();
        }

        ~FrameBuffer()
        {
            SDLNet_FreePacket(_packet); // cleanup
        }

        /// set the ip and port
        void setup(std::string ip, unsigned int port)
        {
            _sender.setup(ip, port);
        }

        /// set all packages to the same color
        void setColor(visual::Color color)
        {
            for (int _address = 0; _address < FACADE_NUM_ADDR; _address++)
            {
                _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_RED]    = (char) color.R;
                _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN]  = (char) color.G;
                _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE]   = (char) color.B;
            }
        }

        /// set package at address to color
        void setColor(int _address, visual::Color color)
        {
            if (_address >= 0 && _address < FACADE_NUM_ADDR)
            {
                _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_RED]    = (char) color.R;
                _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN]  = (char) color.G;
                _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE]   = (char) color.B;
            }
        }

        /// get the color from a specific address package
        visual::Color getColor(int _address)
        {
            visual::Color color;

            if (_address >= 0 && _address < FACADE_NUM_ADDR)
            {
                color.R = _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_RED];
                color.G = _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN];
                color.B = _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE];
            }

            return color;
        }

        /// send the complete UDP packet
        void flush()
        {
            try
            {
                memcpy(_packet->data, _frameBuffer, FACADE_PKG_SIZE*FACADE_NUM_ADDR);
                _sender.send(_packet);
            }
            catch(std::exception& e)
            {
                LOG_ERROR << "_frameBuffer: Could not send packet: " << e.what() << std::endl;
            }
        }

	private:

        void allocate()
        {
            _packet = SDLNet_AllocPacket(FACADE_PKG_SIZE*FACADE_NUM_ADDR);
            _packet->len = FACADE_PKG_SIZE*FACADE_NUM_ADDR;

            for(int _address = 0; _address < FACADE_NUM_ADDR; _address++)
            {
                _frameBuffer[_address*FACADE_PKG_SIZE + 0] = (char) (_address % 256);
                _frameBuffer[_address*FACADE_PKG_SIZE + 1] = (char) (_address / 256);
                _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_RED]    = 0;
                _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN]  = 0;
                _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE]   = 0;
            }
        }

        char _frameBuffer[FACADE_PKG_SIZE*FACADE_NUM_ADDR];
        visual::UdpSender _sender;
        UdpPacket* _packet;
};

#endif // FRAMEBUFFER_APP_H
