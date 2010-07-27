/*==============================================================================

	SideMainBuildingSouth.h
    
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
#ifndef FACADE_SIDE_MAIN_SOUTH_H
#define FACADE_SIDE_MAIN_SOUTH_H

namespace facade {

class SideMainBuildingSouth : public Side
{
    public:

        SideMainBuildingSouth()
        {
            name = "Main Building South";

            startAddr = 350;
            endAddr = 546;

            nrRows = 22;
            nrCols = 10;

            c_startRow = 1;
			c_startCol = 10;
            setPos(c_startRow, c_startCol);

            int temp[] =
            {
                 350, 351, 352, 353,  -1,  -1,  -1,  -1,  -1,  -1,
                 354, 355, 356, 357, 358, 359, 360, 361, 362, 363,
                 364, 365, 366, 367, 368, 369, 370, 371, 372, 373,
                 374, 375, 376, 377, 378, 379, 380, 381, 382, 383,
                 384, 385, 386, 387, 388, 389, 390, 391, 392, 393,
                 394, 395, 396, 397, 398, 399, 400, 401, 402, 403,
                 404, 405, 406, 407, 408, 409, 410, 411, 412, 413,
                 414, 415, 416, 417, 418, 419, 420, 421, 422, 423,
                 424, 425, 426, 427, 428, 429, 430, 431, 432, 433,
                 434, 435, 436, 437, 438, 439, 440, 441, 442, 443,
                 444, 445, 446, 447, 448, 449, 450, 451, 452, 453,
                 454, 455, 456, 457, 458, 459, 460, 461, 462, 463,
                 464, 465, 466, 467, 468, 469, 470, 471, 472, 473,
                 474, 475, 476, 477, 478, 479, 480, 481, 482, 483,
                 484, 485, 486, 487, 488, 489, 490, 491, 492, 493,
                 494, 495, 496, 497, 498, 499, 500, 501, 502, 503,
                 504, 505, 506, 507, 508, 509, 510, 511, 512, 513,
                 514, 515, 516, 517, 518, 519, 520, 521, 522, 523,
                 524, 525, 526, 527,  -1,  -1, 528, 529, 530, 531,
                 532, 533, 534, 535,  -1,  -1, 536, 537, 538, 539,
                  -1,  -1,  -1,  -1,  -1,  -1, 540, 541, 542, 543,
                  -1,  -1,  -1,  -1,  -1,  -1,  -1, 544, 545, 546
            };
            windowAddrs = new int[nrRows*nrCols];
            memcpy(windowAddrs, temp, nrRows*nrCols*sizeof(int));
        }
};

} // namespace

#endif // FACADE_SIDE_MAIN_SOUTH_H
