/*==============================================================================

SideFuturelabSouth.h

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
#ifndef FACADE_SIDE_FL_SOUTH_H
#define FACADE_SIDE_FL_SOUTH_H

namespace facade {

class SideFuturelabSouth : public Side
{

	public:

		SideFuturelabSouth()
		{
			name = "FutureLab South";

			startAddr = 958;
			endAddr = 1084;

			nrRows = 10;
			nrCols = 23;

			c_startRow = 17;
			c_startCol = 22;
			setPos(c_startRow, c_startCol);

			int temp[] =
			{
				  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 965, 964, 963, 962, 961, 960, 959, 958,
				  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 974, 973, 972, 971, 970, 969, 968, 967, 966,
				  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 983, 982, 981, 980, 979, 978, 977, 976, 975,
				  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 993, 992, 991, 990, 989, 988, 987, 986, 985, 984,
				  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,1004,1003,1002,1001,1000, 999, 998, 997, 996, 995, 994,
				  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,1016,1015,1014,1013,1012,1011,1010,1009,1008,1007,1006,1005,
				  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,1029,1028,1027,1026,1025,1024,1023,1022,1021,1020,1019,1018,1017,
				1052,1051,1050,1049,1048,1047,1046,1045,1044,1043,1042,1041,1040,1039,1038,1037,1036,1035,1034,1033,1032,1031,1030,
				  -1,  -1,  -1,  -1,1071,1070,1069,1068,1067,1066,1065,1064,1063,1062,1061,1060,1059,1058,1057,1056,1055,1054,1053,
				  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,1084,1083,1082,1081,1080,1079,1078,1077,1076,1075,1074,1073,1072
			};
			windowAddrs = new int[nrRows*nrCols];
			memcpy(windowAddrs, temp, nrRows*nrCols*sizeof(int));
		}
};

} // namespace

#endif // FACADE_SIDE_FL_SOUTH_H
