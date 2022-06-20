#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player(sf::Color col);

	//Functions.
	sf::Color getColor() const;
private:
	const sf::Color color;
};

