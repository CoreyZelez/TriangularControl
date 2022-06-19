#pragma once
#include <array>
#include "Point.h"
#include "Connection.h"
class Game
{
public:
	Game(const sf::RenderWindow &window, const int size);

	void drawBoard(sf::RenderWindow &window) const;

private:
	const int size;
	std::vector<Player> players;
	std::vector<std::vector<Point>> board;
	std::vector<Connection> connections;
};

sf::Vector2u calculateTopLeft(const sf::RenderWindow &window, const int size, const int spacing);

