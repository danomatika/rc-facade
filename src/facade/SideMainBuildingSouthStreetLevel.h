/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#ifndef SIDE_MAIN_SOUTH_STREET_APP_H
#define SIDE_MAIN_SOUTH_STREET_APP_H

class SideMainBuildingSouthStreetLevel : public Side
{
    public:

        SideMainBuildingSouthStreetLevel()
        {
            name = "Main Building South Street Level";

            startAddr = 547;
            endAddr = 632;

            nrRows = 5;
            nrCols = 27;

            setPos(23, 9);

            int temp[] =
            {
                 547, 548, 549, 550, 551, 552, 553, 554, 555, 556, 557,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
                 558, 559, 560, 561,  -1,  -1,  -1, 562, 563, 564, 565, 566, 567, 568, 569, 570, 571, 572, 573,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
                 574, 575, 576, 577,  -1,  -1,  -1, 578, 579, 580, 581, 582, 583, 584, 585, 586, 587, 588, 589, 590, 591, 592, 593, 594, 595,  -1,  -1,
                 596, 597, 598, 599,  -1,  -1,  -1, 600, 601, 602, 603, 604, 605, 606, 607, 608, 609, 610, 611, 612, 613, 614, 615, 616, 617, 618, 619,
                 620, 621, 622, 623,  -1,  -1,  -1, 624, 625, 626, 627, 628, 629, 630, 631, 632,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
            };
            windowAddrs = new int[nrRows*nrCols];
            memcpy(windowAddrs, temp, nrRows*nrCols*sizeof(int));
        }
};

#endif // SIDE_MAIN_SOUTH_STREET_APP_H
