/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#ifndef FACADE_BUILDING_H
#define FACADE_BUILDING_H

#include <vector>
#include "Side.h"
#include "SideFuturelabEast.h"
#include "SideFuturelabNorth.h"
#include "SideFuturelabSouth.h"
#include "SideMainBuildingEast.h"
#include "SideMainBuildingNorth.h"
#include "SideMainBuildingSouth.h"
#include "SideMainBuildingSouthStreetLevel.h"
#include "SideMainBuildingWest.h"

namespace facade {

/// represents the building as a list of bulding sides
class Building
{
    public:

        // the individual sides
        SideMainBuildingNorth   main_N;
        SideMainBuildingEast    main_E;
        SideMainBuildingSouth   main_S;
        SideMainBuildingSouthStreetLevel main_S_street;
        SideMainBuildingWest    main_W;
        SideFuturelabNorth      lab_N;
        SideFuturelabEast       lab_E;
        SideFuturelabSouth      lab_S;

        Building() : nrRows(0), nrCols(0)
        {
            sides.push_back(&main_N);
            sides.push_back(&main_E);
            sides.push_back(&main_S);
            sides.push_back(&main_S_street);
            sides.push_back(&main_W);
            sides.push_back(&lab_N);
            sides.push_back(&lab_E);
            sides.push_back(&lab_S);

            computeSize();
        }

        /// compute the size of the building's grid based on enabled sides
        /// call this after enabling/disabling a side to resize the grid
        void computeSize()
        {
            nrRows = 0; nrCols = 0;

            for(unsigned int i = 0; i < sides.size(); ++i)
            {
                Side* side = sides.at(i);
                if(side->isEnabled())
                {

                    if(side->getEndRow() >= (int) nrRows)
                    {
                        nrRows = side->getEndRow()+1;
                    }

                    if(side->getEndCol() >= (int) nrCols)
                    {
                        nrCols = side->getEndCol()+1;
                    }
                }
            }
        }

        inline unsigned int getNrRows()  {return nrRows;}
        inline unsigned int getNrCols()  {return nrCols;}
        inline std::vector<Side*>& getSides() {return sides;}

        void print()
        {
            std::cout << "Building: " << nrCols << "x" << nrRows << std::endl << std::endl;

            for(unsigned int i = 0; i < sides.size(); ++i)
            {
                Side* side = sides.at(i);
                if(side->isEnabled())
                {
                    std::cout << "Side: " << side->getName() << " "
                        <<side->getNrCols() << "x" << side->getNrRows()
                        << " at (" << side->getStartCol() << ", " << side->getStartRow()
                        << ")" << std::endl;
                    side->print();
                    std::cout << std::endl;
                }
            }
        }

	private:

        std::vector<Side*> sides;   ///< pointer vector to all sides
        unsigned int nrRows;		///< the overall number of rows of the building
        unsigned int nrCols;     	///< the maximum number of columns of a side
};

} // namespace

#endif // BUILDING_APP_H
