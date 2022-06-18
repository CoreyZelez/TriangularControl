#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>
class Point
{
public:

	Point(const sf::Vector2f pos);

	void draw(sf::RenderWindow &window) const;

	const Player *getOwner() const;
	void setOwner(const Player &newOwner);

	bool getSelected() const;
	void changeSelected();

private:
	const Player *owner = nullptr;  //nullptr indicates no owner.
	bool selected = false;
	const sf::Vector2f position;
};

