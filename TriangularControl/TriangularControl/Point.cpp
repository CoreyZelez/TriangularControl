#include "Point.h"

const int POINT_SIZE = 5;
const int SELECTED_POINT_SIZE = 8;

Point::Point(const sf::Vector2f pos)
	: position(pos)
{
}

void Point::setOwner(const Player &newOwner)
{
	owner = &newOwner;
}

const Player *Point::getOwner() const
{
	return owner;
}

bool Point::getSelected() const
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

void Point::draw(sf::RenderWindow &window) const
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
