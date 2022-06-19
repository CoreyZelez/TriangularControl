#pragma once
#include "Point.h"
class Connection
{
public:
	Connection(const Point &p1, const Point &p2);

	void draw(sf::RenderWindow &window);
private:
	const static float lineWidth;

	const Point &point1;
	const Point &point2;
	sf::RectangleShape line;
	const sf::Color color;
};

