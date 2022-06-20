#pragma once
#include <array>
#include "Point.h"
#include "Connection.h"
#include "Coordinate2i.h"
class Game2Player
{
public:
	Game2Player(const sf::RenderWindow &window, const int size, const int safetyNum);

	//Functions.
	void update(const sf::RenderWindow &window);
	void drawBoard(sf::RenderWindow &window) const;

private:
	//Functions.
	void nextPlayer();
	void completeConnections(const int row, const int col);
	void completeAdjacentConnections(const int row, const int col);
	void currentPlayerMove(const sf::RenderWindow &window);
	void connectionMove(const int row, const int col);  //called when player connects 2 points successfully.
	void diagonalMove(bool &wasPointSelected, const int row, const int col);
	void rightDiagonalMove(bool &wasPointSelected, const int row, const int col);
	void leftDiagonalMove(bool &wasPointSelected, const int row, const int col);
	void resetSelectedPoint();  //Sets it to nullptr.

	//Primitive members.
	static bool lockClick;
	static const int maxSize = 27;
	static const int minSize = 9;
	const int size;
	const float pointSpacing;  //Should be dependant on size in future.
	const int safetyNum;  //Number of edge triangles to secure family of connections.

    //Objects.
	Point *sourcePoint = nullptr; //First point selected in a given player move.
	Coordinate2i sourcePointCoords;  //x->row, y->col
	Player *currentPlayer;

	//Containers.
	std::vector<Player> players;
	std::vector<std::vector<Point>> points;
	std::vector<Connection> connections;
};

sf::Vector2u calculateTopLeft(const sf::RenderWindow &window, const int size, const int spacing);
bool isNeighbouringCoord(Coordinate2i coord1, Coordinate2i coord2);
int max(int a, int b);
int min(int a, int b);


