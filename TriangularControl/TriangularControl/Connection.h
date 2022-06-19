#pragma once
#include "Point.h"
class Connection
{
public:
	Connection(const Point &p1, const Point &p2);

	void draw(sf::RenderWindow &window);

	bool contains(const Point &p1, const Point &p2) const;

	bool isDiagonal();
private:
	const static float lineWidth;

	const Point &point1;
	const Point &point2;
	sf::RectangleShape line;
	const sf::Color color;
};

//Searches for a connection in connections between p1 and p2.
bool connectionSearch(const std::vector<Connection> &connections, const Point &p1, const Point &p2);



