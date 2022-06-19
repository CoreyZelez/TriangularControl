#pragma once
#include <array>
#include "Point.h"
#include "Connection.h"
#include "Coordinates2i.h"
class Game
{
public:
	Game(const sf::RenderWindow &window, const int size);

	void update(const sf::RenderWindow &window);

	void nextPlayer();

	void drawBoard(sf::RenderWindow &window) const;

	void resetSelectedPoint();

private:
	static bool lockClick;
	static const int maxSize = 27;
	const int size;
	const float pointSpacing;  //Should be dependant on size in future.

	Point *sourcePoint = nullptr; //nullptr indicates no selected point.
	Coordinates2i sourcePointCoords;  //x->row, y->col
	Player *currentPlayer;

	std::vector<Player> players;
	std::vector<std::vector<Point>> points;
	std::vector<Connection> connections;
};

sf::Vector2u calculateTopLeft(const sf::RenderWindow &window, const int size, const int spacing);
bool isNeighbouringCoord(Coordinates2i coord1, Coordinates2i coord2);
int max(int a, int b);
int min(int a, int b);


