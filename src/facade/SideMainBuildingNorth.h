/*==============================================================================

SideMainBuildingNorth.h

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
#ifndef FACADE_SIDE_MAIN_NORTH_H
#define FACADE_SIDE_MAIN_NORTH_H

#include "Side.h"

namespace facade {

class SideMainBuildingNorth : public Side
{
	public:

		SideMainBuildingNorth()
		{
			name = "Main Building North";

			startAddr = 0;
			endAddr = 119;

			nrRows = 25;
			nrCols = 5;

			c_startRow = 0;
			c_startCol = 30;
			setPos(c_startRow, c_startCol);

			int temp[] =
			{
				 -1,  -1,  -1,   0,   1,
				  2,   3,   4,   5,   6,
				  7,   8,   9,  10,  11,
				 12,  13,  14,  15,  16,
				 17,  18,  19,  20,  21,
				 22,  23,  24,  25,  26,
				 27,  28,  29,  30,  31,
				 32,  33,  34,  35,  36,
				 37,  38,  39,  40,  41,
				 42,  43,  44,  45,  46,
				 47,  48,  49,  50,  51,
				 52,  53,  54,  55,  56,
				 57,  58,  59,  60,  61,
				 62,  63,  64,  65,  66,
				 67,  68,  69,  70,  71,
				 72,  73,  74,  75,  76,
				 77,  78,  79,  80,  81,
				 82,  83,  84,  85,  86,
				 87,  88,  89,  90,  91,
				 92,  93,  94,  95,  96,
				 97,  98,  99, 100, 101,
				102, 103, 104, 105, 106,
				107, 108, 109, 110, 111,
				112, 113, 114, 115,  -1,
				116, 117, 118, 119,  -1
			};
			windowAddrs = new int[nrRows*nrCols];
			memcpy(windowAddrs, temp, nrRows*nrCols*sizeof(int));
		}
};

} // namespace

#endif // FACADE_SIDE_MAIN_NORTH_H
