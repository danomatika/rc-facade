/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
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

		// enable blending?
        //inline void blend(bool yesno) {_bBlend = yesno;}

		/// get a pointer to the framebuffer packet
		inline const uint8_t* getFramebuffer() const {return _framebuffer;}
		
    	/// get the length of the framebuffer packet
        inline unsigned int getFramebufferLen() {return _length;}
        
        /// set the framebuffer from memory, assumes correct length!
        void setFramebuffer(const uint8_t* frame);
        
        /// is blending on?
        //inline bool getBlend() {return _bBlend;} 

	private:

        uint8_t _framebuffer[FACADE_PKG_SIZE*FACADE_NUM_ADDR];
        unsigned int _length;

       // bool _bBlend;
};

} // namespace

#endif // FACADE_FRAMEBUFFER_H
