/*==============================================================================

SideMainBuildingWest.h

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
#ifndef FACADE_SIDE_MAIN_WEST_H
#define FACADE_SIDE_MAIN_WEST_H

#include <string.h>

namespace facade {

class SideMainBuildingWest : public Side
{
	public:

		SideMainBuildingWest()
		{
			name = "Main Building West";

			startAddr = 633;
			endAddr = 841;

			nrRows = 22;
			nrCols = 10;

			c_startRow = 0;
			c_startCol = 0;
			setPos(c_startRow, c_startCol);

			int temp[] =
			{
				633, 634, 635, 636, 637, 638,  -1,  -1,  -1,  -1,
				639, 640, 641, 642, 643, 644, 645, 646, 647, 648,
				649, 650, 651, 652, 653, 654, 655, 656, 657, 658,
				659, 660, 661, 662, 663, 664, 665, 666, 667, 668,
				669, 670, 671, 672, 673, 674, 675, 676, 677, 678,
				679, 680, 681, 682, 683, 684, 685, 686, 687, 688,
				689, 690, 691, 692, 693, 694, 695, 696, 697, 698,
				699, 700, 701, 702, 703, 704, 705, 706, 707, 708,
				709, 710, 711, 712, 713, 714, 715, 716, 717, 718,
				719, 720, 721, 722, 723, 724, 725, 726, 727, 728,
				729, 730, 731, 732, 733, 734, 735, 736, 737, 738,
				739, 740, 741, 742, 743, 744, 745, 746, 747, 748,
				749, 750, 751, 752, 753, 754, 755, 756, 757, 758,
				759, 760, 761, 762, 763, 764, 765, 766, 767, 768,
				769, 770, 771, 772, 773, 774, 775, 776, 777, 778,
				779, 780, 781, 782, 783, 784, 785, 786, 787, 788,
				789, 790, 791, 792, 793, 794, 795, 796, 797, 798,
				799, 800, 801, 802, 803, 804, 805, 806, 807, 808,
				809, 810, 811, 812, 813, 814, 815, 816, 817, 818,
				819, 820, 821, 822, 823, 824, 825, 826, 827, 828,
				829, 830, 831, 832, 833, 834, 835, 836, 837, 838,
				839, 840, 841,  -1,  -1,  -1,  -1,  -1,  -1,  -1
			};
			windowAddrs = new int[nrRows*nrCols];
			memcpy(windowAddrs, temp, nrRows*nrCols*sizeof(int));
		}
};

} // namspace

#endif // FACADE_SIDE_MAIN_WEST_H
