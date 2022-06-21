#include "PointFamily.h"
#include <iostream>
#include <assert.h>

PointFamily::PointFamily(Point *p)
{
	points.push_back(p);
}

PointFamily::PointFamily(Point *p1, Point *p2)
{
	points.push_back(p1);
	points.push_back(p2);
}

void PointFamily::absorb(PointFamily *family)
{
	for(Point *point : family->points)
	{
		points.push_back(point);
		point->setFamily(this);
	}

	std::cout << family << std::endl;
	if(family != nullptr)
	{
		family->points.clear();
	}
}

bool PointFamily::isEmpty() const
{
	return points.empty();
}

void PointFamily::transferFamilyOwnership(Player & newOwner)
{
	for(Point *point : points)
	{

	}
}

bool PointFamily::isGreaterSize(PointFamily *family) const
{
	return points.size() > family->points.size();
}

void mergePointFamilies(Point *p1, Point *p2)
{
	PointFamily *f1 = p1->getFamily();
	PointFamily *f2 = p2->getFamily();

	assert(f1 != nullptr && f2 != nullptr);

	//Absorbs smaller family into larger family if families differ.
	if(f1 != f2)
	{
		if(f1->isGreaterSize(f2))
		{
			f1->absorb(f2);
		}
		else
		{
			f2->absorb(f1);
		}
	}

}
