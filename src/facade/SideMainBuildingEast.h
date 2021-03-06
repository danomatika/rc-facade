/*==============================================================================

SideMainBuildingEast.h

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
#ifndef FACADE_SIDE_MAIN_EAST_H
#define FACADE_SIDE_MAIN_EAST_H

#include "Side.h"

namespace facade {

class SideMainBuildingEast : public Side
{
	public:

		SideMainBuildingEast()
		{
			name = "Main Building East";

			startAddr = 120;
			endAddr = 349;

			nrRows = 24;
			nrCols = 10;

			c_startRow = 1;
			c_startCol = 20;
			setPos(c_startRow, c_startCol);

			int temp[] =
			{
				 -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 120, 121,
				122, 123, 124, 125, 126, 127, 128, 129, 130, 131,
				132, 133, 134, 135, 136, 137, 138, 139, 140, 141,
				142, 143, 144, 145, 146, 147, 148, 149, 150, 151,
				152, 153, 154, 155, 156, 157, 158, 159, 160, 161,
				162, 163, 164, 165, 166, 167, 168, 169, 170, 171,
				172, 173, 174, 175, 176, 177, 178, 179, 180, 181,
				182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
				192, 193, 194, 195, 196, 197, 198, 199, 200, 201,
				202, 203, 204, 205, 206, 207, 208, 209, 210, 211,
				212, 213, 214, 215, 216, 217, 218, 219, 220, 221,
				222, 223, 224, 225, 226, 227, 228, 229, 230, 231,
				232, 233, 234, 235, 236, 237, 238, 239, 240, 241,
				242, 243, 244, 245, 246, 247, 248, 249, 250, 251,
				252, 253, 254, 255, 256, 257, 258, 259, 260, 261,
				262, 263, 264, 265, 266, 267, 268, 269, 270, 271,
				272, 273, 274, 275, 276, 277, 278, 279, 280, 281,
				282, 283, 284, 285, 286, 287, 288, 289, 290, 291,
				292, 293, 294, 295, 296, 297, 298, 299, 300, 301,
				302, 303, 304, 305, 306, 307, 308, 309, 310, 311,
				312, 313, 314, 315, 316, 317, 318, 319, 320, 321,
				322, 323, 324, 325, 326, 327, 328, 329, 330, 331,
				332, 333, 334, 335, 336, 337, 338,  -1, 339, 340,
				341, 342, 343, 344, 345, 346, 347,  -1, 348, 349
			};
			windowAddrs = new int[nrRows*nrCols];
			memcpy(windowAddrs, temp, nrRows*nrCols*sizeof(int));
		}
};

} // namespace

#endif // FACADE_SIDE_MAIN_EAST_H
