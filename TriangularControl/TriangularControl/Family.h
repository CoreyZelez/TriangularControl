#pragma once
#include <set>
#include "Point.h"
class Family
{
public:
	Family(Point point);
	Family(Point point1, Point point2);

	void addPoint(Point point);
private:
	std::vector<Point> points;
};

