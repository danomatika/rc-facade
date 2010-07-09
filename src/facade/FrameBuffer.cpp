/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#include "FrameBuffer.h"

// http://www.nathanm.com/photoshop-blending-math/

// alpha blend from http://www.codeguru.com/cpp/cpp/algorithms/general/article.php/c15989
// src, det, alpha
#define AlphaBlend(S,D,A) ((S*A)+(D*(255-A)))/255

FrameBuffer::FrameBuffer() : _bBlend(true)//_sender()
{
    allocate();
    // init to black
    for(int address = 0; address < FACADE_NUM_ADDR; address++)
    {
        _facadeFB[address*FACADE_PKG_SIZE + 0] = (uint8_t) (address % 256);
        _facadeFB[address*FACADE_PKG_SIZE + 1] = (uint8_t) (address / 256);
        _facadeFB[address*FACADE_PKG_SIZE + FACADE_OFFSET_RED]    = 0;
        _facadeFB[address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN]  = 0;
        _facadeFB[address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE]   = 0;
    }
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

void FrameBuffer::clear(uint32_t color)
{
    bool blend = _bBlend;
    _bBlend = true;
    setColor(color);
    _bBlend = blend;
}

void FrameBuffer::setColor(uint32_t color)
{
    for(int address = 0; address < FACADE_NUM_ADDR; ++address)
    	setColor(address, color);
}

void FrameBuffer::setColor(int address, uint32_t color)
{
    if(address >= 0 && address < FACADE_NUM_ADDR)
    {
    	// don't let pure black through or the LEDs will turn off and have to be power cycled!
        if((color & 0x00FFFFFF) == 0)
            color = ((color >> 24) << 24) | 0x111111;
        
        uint8_t alpha = color >> 24;
        if(_bBlend && alpha < 255)
        {
            uint8_t r = (color >> 16) & 0xFF;
            uint8_t g = (color >> 8) & 0xFF;
            uint8_t b = (color) & 0xFF;
            _facadeFB[address*FACADE_PKG_SIZE + FACADE_OFFSET_RED] =
            	AlphaBlend(r, _facadeFB[address*FACADE_PKG_SIZE + FACADE_OFFSET_RED], alpha);
            _facadeFB[address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN] =
            	AlphaBlend(g, _facadeFB[address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN],  alpha);
            _facadeFB[address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE] =
            	AlphaBlend(b, _facadeFB[address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE],  alpha);
        }
        else
        {
            _facadeFB[address*FACADE_PKG_SIZE + FACADE_OFFSET_RED]    = (color >> 16) & 0xFF;
            _facadeFB[address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN]  = (color >> 8) & 0xFF;
            _facadeFB[address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE]   = color & 0xFF;
        }
    }
}

uint32_t FrameBuffer::getColor(int address)
{
    uint32_t color = 0xFF000000;

    if(address >= 0 && address < FACADE_NUM_ADDR)
    {
    	color = 0xFF << 24 |	// alpha
        		(_facadeFB[address*FACADE_PKG_SIZE + FACADE_OFFSET_RED]) << 16 |
        		(_facadeFB[address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN]) << 8 |
        		(_facadeFB[address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE]);
    }
	
    return color;
}


void FrameBuffer::flush()
{
    try
    {
        memcpy(_packet->data, _facadeFB, FACADE_PKG_SIZE*FACADE_NUM_ADDR);
        _sender.send(_packet);
    }
    catch(std::exception& e)
    {
        std::cerr << "_facadeFB: Could not send packet: " << e.what() << std::endl;
    }
}

void FrameBuffer::allocate()
{
    _packet = SDLNet_AllocPacket(FACADE_PKG_SIZE*FACADE_NUM_ADDR);
    _packet->len = FACADE_PKG_SIZE*FACADE_NUM_ADDR;

	// init to black
    for(int _address = 0; _address < FACADE_NUM_ADDR; _address++)
    {
        _facadeFB[_address*FACADE_PKG_SIZE + 0] = (uint8_t) (_address % 256);
        _facadeFB[_address*FACADE_PKG_SIZE + 1] = (uint8_t) (_address / 256);
        _facadeFB[_address*FACADE_PKG_SIZE + FACADE_OFFSET_RED]    = 0;
        _facadeFB[_address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN]  = 0;
        _facadeFB[_address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE]   = 0;
    }
}
