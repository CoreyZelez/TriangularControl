#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>
class Point
{
public:

	Point(sf::Vector2f pos);

	const Player *getOwner();
	bool getSelected();
	void changeSelected();
	void setOwner(Player &newOwner);

	void draw(sf::RenderWindow &window);

private:
	const Player *owner = nullptr;  //nullptr indicates no owner.
	bool selected = false;
	const sf::Vector2f position;
};

