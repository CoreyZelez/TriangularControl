#include "Player.h"

Player::Player(sf::Color col)
	: color(col)
{
}

sf::Color Player::getColor() const
{
	return color;
}
