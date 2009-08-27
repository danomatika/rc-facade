#ifndef FRAMEUFFER_APP_H
#define FRAMEBUFFER_APP_H

#include "../Common.h"

#define FACADE_PKG_SIZE     5
#define FACADE_NUM_ADDR     1085
#define FACADE_OFFSET_RED   2
#define FACADE_OFFSET_GREEN 3
#define FACADE_OFFSET_BLUE  4

/**
 * implements the interface to the facade simulator
 */
class FrameBuffer
{
    public:

        FrameBuffer(std::string ip, unsigned int port) : sender()
        {
            sender.setup(ip, port);
            packet = SDLNet_AllocPacket(FACADE_PKG_SIZE*FACADE_NUM_ADDR);
            packet->len = FACADE_PKG_SIZE*FACADE_NUM_ADDR;

            for(int address = 0; address < FACADE_NUM_ADDR; address++)
            {
                frameBuffer[address*FACADE_PKG_SIZE + 0] = (char) (address % 256);
                frameBuffer[address*FACADE_PKG_SIZE + 1] = (char) (address / 256);
                frameBuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_RED]    = 0;
                frameBuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN]  = 0;
                frameBuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE]   = 0;
            }
        }

        /**
         * set all packages to the same color
         */
        void setColor(Color color)
        {
            for (int address = 0; address < FACADE_NUM_ADDR; address++)
            {
                frameBuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_RED]    = (char) color.R;
                frameBuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN]  = (char) color.G;
                frameBuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE]   = (char) color.B;
            }
        }

        /**
         * set package at address to color
         */
        void setColor(int address, Color color)
        {
            if (address >= 0 && address < FACADE_NUM_ADDR)
            {
                frameBuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_RED]    = (char) color.R;
                frameBuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN]  = (char) color.G;
                frameBuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE]   = (char) color.B;
            }
        }

        Color getColor(int address)
        {
            Color color;

            if (address >= 0 && address < FACADE_NUM_ADDR)
            {
                color.R = frameBuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_RED];
                color.G = frameBuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN];
                color.B = frameBuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE];
            }

            return color;
        }

        /**
         * send the complete UDP packet to localhost:8080 (might be necessary to change)
         */
        void flush()
        {
            try
            {
                memcpy(packet->data, frameBuffer, FACADE_PKG_SIZE*FACADE_NUM_ADDR);
                sender.send(packet);
            }
            catch(std::exception& e)
            {
                LOG_ERROR << "FrameBuffer: Could not send packet: " << e.what() << std::endl;
            }
        }

	private:

        char frameBuffer[FACADE_PKG_SIZE*FACADE_NUM_ADDR];
        UdpSender sender;
        UdpPacket* packet;
};

#endif // FRAMEBUFFER_APP_H
