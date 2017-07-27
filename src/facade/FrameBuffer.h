/*==============================================================================

FrameBuffer.h

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
#ifndef FACADE_FRAMEUFFER_H
#define FACADE_FRAMEBUFFER_H

#include <stdint.h>
#include <iostream>

#define FACADE_PKG_SIZE     5
#define FACADE_NUM_ADDR     1085
#define FACADE_OFFSET_RED   2
#define FACADE_OFFSET_GREEN 3
#define FACADE_OFFSET_BLUE  4

namespace facade {

/// implements the packet interface to the facade simulator
class FrameBuffer
{
	public:

		FrameBuffer();
		~FrameBuffer();

		/// clear the framebuffer with a certain color, does alpha
		void clear(uint32_t color);

		/// set all packages to the same color, uses alpha as blend amount if belnd is on
		void setColor(uint32_t color);

		/// set package at address to color, uses alpha as blend amount if blend is on
		void setColor(int address, uint32_t color);

		/// get the color from a specific address package, returns 0 if address out of bounds
		uint32_t getColor(int address);

		/// get a pointer to the framebuffer packet
		inline const uint8_t* getFramebuffer() const {return _framebuffer;}
		
		/// get the length of the framebuffer packet
		inline unsigned int getFramebufferLen() {return _length;}
		
		/// set the framebuffer from memory, assumes correct length!
		void setFramebuffer(const uint8_t* frame);

	private:

		uint8_t _framebuffer[FACADE_PKG_SIZE*FACADE_NUM_ADDR];
		unsigned int _length;
};

} // namespace

#endif // FACADE_FRAMEBUFFER_H
