#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player(sf::Color col);

	sf::Color getColor() const;

private:

	const sf::Color color;
};

