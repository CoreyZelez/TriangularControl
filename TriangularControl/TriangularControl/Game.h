#pragma once
#include <array>
#include "Point.h"
class Game
{
public:
	Game(const sf::RenderWindow &window, const int size);

	void drawBoard(sf::RenderWindow &window) const;

private:
	const int size;
	std::vector<std::vector<Point>> board;
};

sf::Vector2u calculateTopLeft(const sf::RenderWindow &window, const int size, const int spacing);

