#ifndef FACADE_SAMPLE_H
#define FACADE_SAMPLE_H

#include <vector>
#include "Building.h"

/**
 * sample for an application with the facade simulator
 */
class FacadeSample
{
    public:

        /**
         * display the whole building in a various colors
         */
        static void walkColors();

        /**
         * walk through the sides of the building and display various colors
         */
        static void walkSides();

        /**
         * walk through the window rows of the whole building
         */
        static void walkRows();

        /**
         * walk through the window columns of the whole building
         */
        static void walkColumns();

        static void main();

    private:

    	static std::vector<Color> colors;
        static Color background;
        static FrameBuffer frame;
        static Building building;
};

#endif // FACADE_SAMPLE_APP_H
