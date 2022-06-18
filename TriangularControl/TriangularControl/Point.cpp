#include "Point.h"

const int POINT_SIZE = 60;
const int SELECTED_POINT_SIZE = 80;

void Point::setOwner(Player &newOwner)
{
	owner = &newOwner;
}

Point::Point(sf::Vector2f pos)
	: position(pos)
{
}

const Player *Point::getOwner()
{
	return owner;
}

bool Point::getSelected()
{
	return selected;
}

void Point::changeSelected()
{
	if(selected == false)
	{
		selected = true;
	}
	else
	{
		selected = false;
	}
}

void Point::draw(sf::RenderWindow &window)
{
	sf::CircleShape circle(POINT_SIZE);
	circle.setPosition(position);
	
	if(owner == nullptr)
	{
		circle.setFillColor(sf::Color(255, 255, 255, 255));
	}
	else
	{
		circle.setFillColor(owner->getColor());
	}

	window.draw(circle);
}
