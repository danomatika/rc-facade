/*==============================================================================

SideFuturelabNorth.h

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
#ifndef FACADE_SIDE_FL_NORTH_H
#define FACADE_SIDE_FL_NORTH_H

namespace facade {

class SideFuturelabNorth : public Side
{

	public:

		SideFuturelabNorth()
		{
			name = "FutureLab North";

			startAddr = 842;
			endAddr = 911;

			nrRows = 8;
			nrCols = 13;

			c_startRow = 16;
			c_startCol = 50;
			setPos(c_startRow, c_startCol);

			int temp[] =
			{
				842, 843, 844, 845, 846, 847,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
				848, 849, 850, 851, 852, 853, 854,  -1,  -1,  -1,  -1,  -1,  -1,
				855, 856,  -1, 857, 858, 859, 860, 861,  -1,  -1,  -1,  -1,  -1,
				862, 863,  -1, 864, 865, 866, 867, 868, 869,  -1,  -1,  -1,  -1,
				870, 871, 872, 873, 874, 875, 876, 877, 878, 879,  -1,  -1,  -1,
				880, 881, 882, 883, 884, 885, 886, 887, 888, 889, 890,  -1,  -1,
				891, 892, 893,  -1,  -1, 894, 895, 896, 897, 898, 899, 900,  -1,
				901, 902, 903,  -1,  -1, 904, 905, 906, 907, 908, 909, 910, 911
			};
			windowAddrs = new int[nrRows*nrCols];
			memcpy(windowAddrs, temp, nrRows*nrCols*sizeof(int));
		}
};

} // namespace

#endif // FACADE_SIDE_FL_NORTH_H
