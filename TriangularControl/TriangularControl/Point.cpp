#include "Point.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <assert.h>

const float Point::selectionRadiusMultiplier = 2;
const float Point::pointRadius = 6;
const float Point::selectedPointRadius = 7;
const float Point::pointOutlineThickness = 3;

Point::Point(const sf::Vector2f pos)
	: position(pos), circle(pointRadius)
{
	circle.setPosition(position);
	circle.setFillColor(sf::Color::White);
}

bool Point::compareOwner(Point point) const
{
	if(point.owner == owner)
	{
		return true;
	}

	return false;
}

bool Point::compareOwner(const Player *player) const
{
	return owner == player;
}

bool Point::noOwner() const
{
	return owner == nullptr;
}

void Point::setOwner(const Player &newOwner)
{
	owner = &newOwner;
	circle.setOutlineThickness(pointOutlineThickness);
	circle.setOutlineColor(owner->getColor());
}

sf::Color Point::getOwnerColor() const
{
	if(owner == nullptr)
	{
		return sf::Color::White;
	}

	return owner->getColor();
}

void Point::setColorYellow()
{
	circle.setFillColor(sf::Color(255, 255, 30, 255));

}


void Point::setFamily(PointFamily *family)
{
	this->family = family;
}

PointFamily* Point::getFamily() const
{
	return family;
}

bool Point::hasFamily()
{
	return family != nullptr;
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

		const int radiusIncrease = selectedPointRadius - pointRadius;

		sf::Vector2f newPosition((int)position.x - radiusIncrease, 
			(int)position.y - radiusIncrease);

		circle.setPosition(newPosition);
		circle.setRadius(selectedPointRadius);
	}

	else
	{
		selected = false;
		circle.setPosition(position);
		circle.setRadius(pointRadius);
	}
}

const float Point::getPointSize()
{
	return pointRadius;
}


void Point::draw(sf::RenderWindow &window) const
{
	window.draw(circle);
}

bool Point::detectMouseClick(const sf::Vector2i mousePosition)
{
	const int centerX = (int)(getPosition().x + pointRadius);
	const int centerY = (int)(getPosition().y + pointRadius);
	const sf::Vector2i circleCenter(centerX, centerY);
	const int selectionRadiusSquared = pow(circle.getRadius() * selectionRadiusMultiplier, 2);

	if(squareDistance(circleCenter, mousePosition) < selectionRadiusSquared)
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
	return pow(vec1.x - vec2.x, 2) + pow(vec1.y - vec2.y, 2);
}
