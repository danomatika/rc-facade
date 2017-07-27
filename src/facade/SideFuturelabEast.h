/*==============================================================================

SideFuturelabEast.h

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
#ifndef FACADE_SIDE_FL_EAST_H
#define FACADE_SIDE_FL_EAST_H

namespace facade {

class SideFuturelabEast : public Side
{

	public :

		SideFuturelabEast()
		{
			name = "FutureLab East";

			startAddr = 917;
			endAddr = 957;

			nrRows = 9;
			nrCols = 5;

			c_startRow = 17;
			c_startCol = 45;
			setPos(c_startRow, c_startCol);

			int temp[] =
			{
				917, 918, 919, 920, 921,
				922, 923, 924, 925, 926,
				927, 928, 929, 930, 931,
				932, 933, 934, 935, 936,
				937, 938, 939, 940, 941,
				942, 943, 944, 945, 946,
				947, 948, 949, 950, 951,
				952, 953, 954, 955, 956,
				957,  -1,  -1,  -1,  -1
			};
			windowAddrs = new int[nrRows*nrCols];
			memcpy(windowAddrs, temp, nrRows*nrCols*sizeof(int));
		}
};

} // namespace

#endif // FACADE_SIDE_FL_EAST_H
