/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#include "FrameBuffer.h"

#define MIN(a,b)  ((a) < (b) ? (a) : (b))
#define MAX(a,b)  ((a) > (b) ? (a) : (b))

#define ChannelBlend_Alpha(B,L,O)    ((uint8_t)(O/255 * B + (1 - O/255) * L))

bool FrameBuffer::_bBlend = true;

FrameBuffer::FrameBuffer() : _sender()
{
    allocate();
}

FrameBuffer::FrameBuffer(std::string ip, unsigned int port) : _sender()
{
    _sender.setup(ip, port);
    allocate();
}

FrameBuffer::~FrameBuffer()
{
    SDLNet_FreePacket(_packet); // cleanup
}

void FrameBuffer::setup(std::string ip, unsigned int port)
{
    _sender.setup(ip, port);
}

void FrameBuffer::clear(visual::Color color)
{
    for(int _address = 0; _address < FACADE_NUM_ADDR; _address++)
    {
        _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_RED] =
            //MIN(255, (_frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_RED] + (char) color.R/color.A) );// * color.A/255);
            ChannelBlend_Alpha(_frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_RED], color.R, color.A);
        _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN] =
            //MIN(255, (_frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN] + (char) color.G/color.A) );// * color.A/255);
            ChannelBlend_Alpha(_frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN], color.G, color.A);
        _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE] =
            //MIN(255, (_frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE] + (char) color.B/color.A) );// * color.A/255);
            ChannelBlend_Alpha(_frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE], color.B, color.A);
    }
}

void FrameBuffer::setColor(visual::Color color)
{
    for(int _address = 0; _address < FACADE_NUM_ADDR; _address++)
    {
        /*
        if(!_bBlend)
        {
            */
            _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_RED]    = (char) color.R;
            _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN]  = (char) color.G;
            _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE]   = (char) color.B;
            /*
        }
        else
        {
            _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_RED] =
                MIN(255, ((_frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_RED] + (char) color.R)*color.A/255));
            _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN] =
                MIN(255, ((_frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN] + (char) color.G)*color.A/255));
            _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE] =
                MIN(255, ((_frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE] + (char) color.B)*color.A/255));
        }
        */
    }
}

void FrameBuffer::setColor(int _address, visual::Color color)
{
    if(_address >= 0 && _address < FACADE_NUM_ADDR)
    {
        if(_bBlend)
        {
            _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_RED]    = (char) color.R;
            _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN]  = (char) color.G;
            _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE]   = (char) color.B;

        }
        else
        {
            _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_RED] =
                //MIN(255, (_frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_RED] + (char) color.R * color.A/255));
                ChannelBlend_Alpha(_frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_RED], color.R, color.A);
            _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN] =
                //MIN(255, (_frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN] + (char) color.G * color.A/255));
                ChannelBlend_Alpha(_frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN], color.G, color.A);
            _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE] =
                //MIN(255, (_frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE] + (char) color.B * color.A/255));
                ChannelBlend_Alpha(_frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE], color.B, color.A);
        }
    }
}

visual::Color FrameBuffer::getColor(int _address)
{
    visual::Color color;

    if(_address >= 0 && _address < FACADE_NUM_ADDR)
    {
        color.R = _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_RED];
        color.G = _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN];
        color.B = _frameBuffer[_address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE];
    }

    return color;
}


void FrameBuffer::flush()
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

void FrameBuffer::allocate()
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

