/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#include "FrameBuffer.h"

// alpha blend from http://www.codeguru.com/cpp/cpp/algorithms/general/article.php/c15989
// src, det, alpha
//#define AlphaBlend(S,D,A) ((S*A)+(D*(255-A)))/255

namespace facade {

FrameBuffer::FrameBuffer() : _length(FACADE_PKG_SIZE*FACADE_NUM_ADDR)//, _bBlend(true)
{
    // set addresses and init to black
    for(int address = 0; address < FACADE_NUM_ADDR; address++)
    {
        _framebuffer[address*FACADE_PKG_SIZE + 0] = (uint8_t) (address % 256);
        _framebuffer[address*FACADE_PKG_SIZE + 1] = (uint8_t) (address / 256);
        _framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_RED]    = 0;
        _framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN]  = 0;
        _framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE]   = 0;
    }
}

FrameBuffer::~FrameBuffer()
{}

void FrameBuffer::clear(uint32_t color)
{
//    bool blend = _bBlend;
//    _bBlend = true;
    setColor(color);
//    _bBlend = blend;
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
        	color = 0xFF111111;
            //color = ((color >> 24) << 24) | 0x111111;
/*        
        uint8_t alpha = color >> 24;
        if(_bBlend && alpha < 255)
        {
            uint8_t r = (color >> 16) & 0xFF;
            uint8_t g = (color >> 8) & 0xFF;
            uint8_t b = (color) & 0xFF;
            _framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_RED] =
            	AlphaBlend(r, _framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_RED], alpha);
            _framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN] =
            	AlphaBlend(g, _framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN],  alpha);
            _framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE] =
            	AlphaBlend(b, _framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE],  alpha);
        }
        else
        {
*/
            _framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_RED]    = (color >> 16) & 0xFF;
            _framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN]  = (color >> 8) & 0xFF;
            _framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE]   = color & 0xFF;
//        }
    }
}

uint32_t FrameBuffer::getColor(int address)
{
    uint32_t color = 0x0000000;

    if(address >= 0 && address < FACADE_NUM_ADDR)
    {
    	color = 0xFF << 24 |	// alpha
        		(_framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_RED]) << 16 |
        		(_framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN]) << 8 |
        		(_framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE]);
    }
	
    return color;
}

void FrameBuffer::setFramebuffer(const uint8_t* frame)
{    
    try
    {
    	std::memcpy(_framebuffer, frame, FACADE_PKG_SIZE*FACADE_NUM_ADDR);
    }
    catch(std::exception& e)
    {
        std::cerr << "FrameBuffer: setFrameBuffer failed: " << e.what() << std::endl;
    }
}

} // namespace
