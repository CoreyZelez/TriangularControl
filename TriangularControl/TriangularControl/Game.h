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
	static const int maxSize = 27;
	const int size;
	const float pointSpacing;  //Should be dependant on size in future.


	std::vector<Player> players;
	std::vector<std::vector<Point>> board;
	std::vector<Connection> connections;
};

sf::Vector2u calculateTopLeft(const sf::RenderWindow &window, const int size, const int spacing);

