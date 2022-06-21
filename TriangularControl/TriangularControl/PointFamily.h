#pragma once
#include "Point.h"
#include <vector>

class Point;

class PointFamily
{
public:
	PointFamily(Point *p);
	PointFamily(Point *p1, Point *p2);

	void absorb(PointFamily *family);

	void transferFamilyOwnership(Player &newOwner);
	bool isGreaterSize(PointFamily *family) const;
	bool isEmpty() const;
private:
	std::vector<Point*> points;
};

void mergePointFamilies(Point *p1, Point *p2);
