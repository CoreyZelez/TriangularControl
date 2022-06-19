#include "Point.h"
#include <SFML/Graphics.hpp>
#include <assert.h>

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

bool Point::detectMouseClick(const sf::RenderWindow &window)
{
	assert(sf::Mouse::isButtonPressed(sf::Mouse::Left));

	const int centerX = (int)(getPosition().x - pointSize);
	const int centerY = (int)(getPosition().y - pointSize);
	const sf::Vector2i circleCenter(centerX, centerY);
	const sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	const int radiusSquared = (int)circle.getRadius() ^ 2;

	if(squareDistance(circleCenter, mousePosition) < radiusSquared)
	{
		return true;
	}

	return false;
}

sf::Vector2f Point::getPosition() const
{
	return position;
}

int squareDistance(sf::Vector2i vec1, sf::Vector2i vec2)
{
	return (vec1.x - vec2.x) ^ 2 + (vec1.y - vec2.y) ^ 2;
}
