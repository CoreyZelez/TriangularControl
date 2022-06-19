#include "Point.h"
#include <SFML/Graphics.hpp>

const float Point::pointSize = 5;
const float Point::selectedPointSize = 8;

Point::Point(const sf::Vector2f pos)
	: position(pos), circle(pointSize)
{
	circle.setPosition(position);

	//Determines circle fill color.
	if(owner == nullptr)
	{
		circle.setFillColor(sf::Color(255, 255, 255, 255));
	}
	else
	{
		circle.setFillColor(owner->getColor());
	}
}

bool Point::compareOwner(const Player &player) const
{
	return owner == &player;
}

void Point::setOwner(const Player &newOwner)
{
	owner = &newOwner;
}

sf::Color Point::getOwnerColor() const
{
	return owner->getColor();
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

const float Point::getPointSize()
{
	return pointSize;
}

void Point::draw(sf::RenderWindow &window) const
{
	window.draw(circle);
}

sf::Vector2f Point::getPosition() const
{
	return position;
}
