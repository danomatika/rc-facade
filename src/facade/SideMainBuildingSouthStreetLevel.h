/*==============================================================================

	SideMainBuildingSouthStreetLevel.h
    
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
#ifndef FACADE_SIDE_MAIN_SOUTH_STREET_H
#define FACADE_SIDE_MAIN_SOUTH_STREET_H

namespace facade {

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

} // namespace

#endif // FACADE_SIDE_MAIN_SOUTH_STREET_H
