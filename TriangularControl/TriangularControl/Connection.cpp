#include "Connection.h"
#include <assert.h>
#include <cstdlib>

const float Connection::lineWidth = 5;

Connection::Connection(const Point &p1, const Point &p2)
	: point1(p1), point2(p2), color(point1.getOwnerColor())
{
	//Construction of the line member.
	const float xDiff = point2.getPosition().x - point1.getPosition().x;
	const float yDiff = point2.getPosition().y - point1.getPosition().y;
	assert(xDiff == 0 || yDiff == 0 || abs(xDiff) == abs(yDiff));

	//Case line is diagonal.
	if(xDiff != 0 && yDiff != 0)
	{

		//Case line is right diagonal.
		if(xDiff > 0 && yDiff > 0 || xDiff < 0 && yDiff < 0)
		{
			line = sf::RectangleShape(sf::Vector2f(xDiff * sqrt(2), lineWidth));
			line.setOrigin(sf::Vector2f(0, Point::getPointSize() / 2));
			line.rotate(45);
		}
		//Case line is left diagonal
		else
		{
			line = sf::RectangleShape(sf::Vector2f(lineWidth, yDiff * sqrt(2)));
			line.setOrigin(sf::Vector2f(0, Point::getPointSize() / 2));
			line.rotate(45);
		}

	}
	//Case line is vertical.
	else if(xDiff == 0)
	{
		line = sf::RectangleShape(sf::Vector2f(lineWidth, yDiff));
	}
	//Case line is horizontal.
	else
	{
		line = sf::RectangleShape(sf::Vector2f(xDiff, lineWidth));
	}

	const float xPos = point1.getPosition().x + (2 * Point::getPointSize() - lineWidth) / 2;
	const float yPos = point1.getPosition().y + (2 * Point::getPointSize() - lineWidth) / 2;
	line.setPosition(sf::Vector2f(xPos, yPos));

	line.setFillColor(color);

}

void Connection::draw(sf::RenderWindow &window)
{
	window.draw(line);
}


