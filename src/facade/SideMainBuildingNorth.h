#ifndef SIDE_MAIN_NORTH_APP_H
#define SIDE_MAIN_NORTH_APP_H

#include "Side.h"

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

            startRow = 0;
            endRow = 25;

            startCol = 30;
            endCol = 34;

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

#endif // SIDE_MAIN_NORTH_APP_H
