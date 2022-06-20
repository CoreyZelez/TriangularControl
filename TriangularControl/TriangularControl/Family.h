#pragma once
#include <set>
#include "Point.h"

class Point;

class Family
{
public:
	Family(Point &point);
	Family(Point &point1, Point &point2);

	//Functions.
	void addPoint(Point &point);
	void absorb(const Family &family);
private:

	//Containers.
	std::vector<Point*> points;
};

