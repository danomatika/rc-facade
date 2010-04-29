/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#include "Point.h"

#include "graphics/sprig/sprig.h"

namespace visual {

Point::Point() : vmml::Vector2f(0, 0) {}
Point::Point(const float a) : vmml::Vector2f(a) {}
Point::Point(const float x, const float y) : vmml::Vector2f(x, y) {}
Point::Point(const Point& p) : vmml::Vector2f(p) {}


void Point::rotate(const PointList& points, const float angle)
{
	SPG_RotatePoints(points.size(), (SPG_Point*) &points[0], angle);
}
void Point::scale(const PointList& points, const float xscale, const float yscale)
{
	SPG_ScalePoints(points.size(), (SPG_Point*) &points[0], xscale, yscale);
}
void Point::skew(const PointList& points, const float xskew, const float yskew)
{
	SPG_SkewPoints(points.size(), (SPG_Point*) &points[0], xskew, yskew);
}
void Point::translate(const PointList& points, const float dx, const float dy)
{
	SPG_TranslatePoints(points.size(), (SPG_Point*) &points[0], dx, dy);
}
    

PointList Point::rotateClone(const PointList& points, const float angle)
{
	PointList newPoints = points;
    SPG_RotatePoints(newPoints.size(), (SPG_Point*) &newPoints[0], angle);
    return newPoints;
}
PointList Point::scaleClone(const PointList& points, const float xscale, const float yscale)
{
	PointList newPoints = points;
    SPG_ScalePoints(newPoints.size(), (SPG_Point*) &newPoints[0], xscale, yscale);
    return newPoints;
}
PointList Point::skewClone(const PointList& points, const float xskew, const float yskew)
{
	PointList newPoints = points;
    SPG_SkewPoints(newPoints.size(), (SPG_Point*) &newPoints[0], xskew, yskew);
    return newPoints;
}
PointList Point::translateClone(const PointList& points, const float dx, const float dy)
{
	PointList newPoints = points;
    SPG_TranslatePoints(newPoints.size(), (SPG_Point*) &newPoints[0], dx, dy);
    return newPoints;
}

} // namespace
