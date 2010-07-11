/*==============================================================================

	Point.h

	visualframework: a simple 2d graphics framework
  
	Copyright (C) 2010  Dan Wilcox <danomatika@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/
#ifndef VISUAL_POINT_H
#define VISUAL_POINT_H

#include <vector>

#include "vmmlib/vmmlib.h"

namespace visual {

class Point;

/// a list of points
typedef	std::vector<Point> PointList;

/**
	\class	Point
	\brief	a 2 dimensional point with vector functions (see vmml::Vector2f)
*/
class Point : public vmml::Vector2f
{
	public:

		Point();
        Point(const float a);	///< sets x and y to a
        Point(const float x, const float y);
        Point(const Point& p);
        
        /// modify point positions in a PointList
    	static void rotate(const PointList& points, const float angle);
        static void scale(const PointList& points, const float xscale, const float yscale);
        static void skew(const PointList& points, const float xskew, const float yskew);
        static void translate(const PointList& points, const float dx, const float dy);

		/// clone a points list and return a new, modified PointsList, does not alter original list
        static PointList rotateClone(const PointList& points, const float angle);
        static PointList scaleClone(const PointList& points, const float xscale, const float yscale);
        static PointList skewClone(const PointList& points, const float xskew, const float yskew);
        static PointList translateClone(const PointList& points, const float dx, const float fy);
};

} // namespace

#endif // VISUAL_POINT_H
