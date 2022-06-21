#include "PointFamily.h"
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

const Player* PointFamily::getOwner() const
{
	return points[0]->getOwner();
}

void PointFamily::transferOwnership(const Player &player)
{
	for(Point *point : points)
	{
		point->setOwner(player);
	}
}

void PointFamily::absorb(PointFamily *family)
{
	for(Point *point : family->points)
	{
		points.push_back(point);
		point->setFamily(this);
	}

	if(family != nullptr)
	{
		family->points.clear();
	}
}

bool PointFamily::contains(Point *point) const
{
	if(std::find(points.begin(), points.end(), point) != points.end())
	{
		return true;
	}

	return false;
}

bool PointFamily::isEmpty() const
{
	return points.empty();
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
