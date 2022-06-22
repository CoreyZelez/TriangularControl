#pragma once
#include "Point.h"
#include <vector>

class Point;

class PointFamily
{
public:
	PointFamily(Point *p);
	PointFamily(Point *p1, Point *p2);

	const Player* getOwner() const;
	void transferOwnership(const Player &player);
	void absorb(PointFamily *family);
	bool contains(Point *point) const;
	bool isGreaterSize(PointFamily *family) const;
	bool isEmpty() const;
private:
	std::vector<Point*> points;
};

void mergePointFamilies(Point *p1, Point *p2);
