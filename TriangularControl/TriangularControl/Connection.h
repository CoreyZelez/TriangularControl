#pragma once
#include "Point.h"
class Connection
{
public:
	Connection(Point *p1, Point *p2);

	//Functions.
	void draw(sf::RenderWindow &window);
	bool contains(const Point *p1, const Point *p2) const;

private:
	//Functions
	void initLine();

	//Primitive members.
	const static float lineWidth;

	//Objects.
	const Point *point1;
	const Point *point2;
	sf::RectangleShape line;
};

//Searches for a connection in connections between p1 and p2.
bool connectionSearch(const std::vector<Connection> &connections, const Point *p1, const Point *p2);





