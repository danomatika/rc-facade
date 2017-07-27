/*==============================================================================

FrameBuffer.cpp

libfacade: a 2d framebuffer for the Ars Electronica Facade

Copyright (c) 2009, 2010 Dan Wilcox <danomatika@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
	
==============================================================================*/
#include "FrameBuffer.h"

#include <cassert>
#include <string.h>

namespace facade {

FrameBuffer::FrameBuffer() : _length(FACADE_PKG_SIZE*FACADE_NUM_ADDR)
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
	setColor(color);
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

		_framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_RED]    = (color >> 16) & 0xFF;
		_framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN]  = (color >> 8) & 0xFF;
		_framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE]   = color & 0xFF;
	}
}

uint32_t FrameBuffer::getColor(int address)
{
	uint32_t color = 0x0000000;

	if(address >= 0 && address < FACADE_NUM_ADDR)
	{
		color = (0xFF << 24) | // alpha
				_framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_RED] << 16 |
				_framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_GREEN] << 8 |
				_framebuffer[address*FACADE_PKG_SIZE + FACADE_OFFSET_BLUE];
	}
	
	return color;
}

void FrameBuffer::setFramebuffer(const uint8_t* frame)
{   
	assert(frame); // shouldn't be nULL
	 
	try
	{
		memcpy(_framebuffer, frame, FACADE_PKG_SIZE*FACADE_NUM_ADDR);
	}
	catch(std::exception& e)
	{
		std::cerr << "FrameBuffer: setFrameBuffer failed: " << e.what() << std::endl;
	}
}

} // namespace
