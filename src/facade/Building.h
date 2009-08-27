#ifndef BUILDING_APP_H
#define BUILDING_APP_H

#include "../Common.h"

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

/**
 * represents the building as a list of bulding sides
 */
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

            for(unsigned int i = 0; i < sides.size(); ++i)
            {
                Side* side = sides.at(i);

                if(side->getEndRow() > nrRows)
                {
                    nrRows = side->getEndRow()+1;
                }

                if(side->getEndCol() > nrCols)
                {
                    nrCols = side->getEndCol()+1;
                }
            }

            LOG << "Building: " << nrRows << "x" << nrCols << std::endl;
        }

        inline int getNrRows()  {return nrRows;}
        inline int getNrCols()  {return nrCols;}
        inline std::vector<Side*>& getSides() {return sides;}

        void print()
        {
            for(unsigned int i = 0; i < sides.size(); ++i)
            {
                Side* side = sides.at(i);
                LOG << "Side: " << side->getName() << " "
                    <<side->getNrCols() << "x" << side->getNrRows()
                    << " at " << side->getStartCol() << "x" << side->getStartRow()
                    << std::endl;
                side->print();
                LOG << std::endl;
            }
        }

	private:

        std::vector<Side*> sides;   /// pointer vector to all sides
        int nrRows;		///< the overall number of rows of the building
        int nrCols;     ///< the maximum number of columns of a side
};

#endif // BUILDING_APP_H
