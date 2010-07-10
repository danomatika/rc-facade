/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
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

            setPos(17, 43);

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
