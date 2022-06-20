#include "Family.h"

Family::Family(Point &point)
{
	addPoint(point);
	point.setFamily(this);
}

Family::Family(Point &point1, Point &point2)
{
	addPoint(point1);
	addPoint(point2);
	point1.setFamily(this);
	point2.setFamily(this);
}

void Family::addPoint(Point &point)
{
	points.push_back(&point);
}

void Family::absorb(const Family &family)
{
	for(auto point : family.points)
	{
		points.push_back(point);
	}
}
