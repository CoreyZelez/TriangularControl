#include "Family.h"

Family::Family(Point point)
{
	addPoint(point);
}

Family::Family(Point point1, Point point2)
{
	addPoint(point1);
	addPoint(point2);
}

void Family::addPoint(Point point)
{
	points.push_back(point);
}
