#include "Connection.h"


const float Connection::lineWidth = 6;

Connection::Connection(Point *p1, Point *p2)
	: point1(p1), point2(p2), color(point1->getOwnerColor())
{
	initLine();
	mergePointFamilies(p1, p2);
}

void Connection::draw(sf::RenderWindow &window)
{
	window.draw(line);
}

bool Connection::contains(const Point *p1, const Point *p2) const
{
	if((point1 == p1 && point2 == p2) || (point1 == p2 && point2 == p1))
	{
		return true;
	}

	return false;
}


void Connection::initLine()
{
	//Construction of the line member.
	const float xDiff = point2->getPosition().x - point1->getPosition().x;
	const float yDiff = point2->getPosition().y - point1->getPosition().y;
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
	//Origin starting position on screen of line.
	const float xPos = point1->getPosition().x + (2 * Point::getPointSize() - lineWidth) / 2;
	const float yPos = point1->getPosition().y + (2 * Point::getPointSize() - lineWidth) / 2;
	line.setPosition(sf::Vector2f(xPos, yPos));

	line.setFillColor(color);
}

bool connectionSearch(const std::vector<Connection> &connections, const Point *p1, const Point *p2)
{
	for(const Connection &connection : connections)
	{
		if(connection.contains(p1, p2))
		{
			return true;
		}
	}

	return false;
}


