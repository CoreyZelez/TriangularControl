#pragma once
#include <List>
#include "Point.h"
#include "Connection.h"
#include "Coordinate2i.h"
#include "PointFamily.h"

class Game2Player
{
public:
	Game2Player(const sf::RenderWindow &window, const int size, const int safetyNum);

	//Functions.
	void update(const sf::RenderWindow &window);
	void drawBoard(sf::RenderWindow &window);

private:
	//Functions.
	bool libertyMoveExists(const int row, const int col, const Player &player) const;  //Checks if there is a possible move from the given coordinates.
	bool diagonalLibertyExists(const int row, const int col, const Player &player) const;

	bool familySurrounded(const PointFamily &family) const;
	void transferWeakFamiliesOwnership(const Player &player);  //Gives weak "enemy" surrounded families to player.

	int familyIsEdgeSafe(const PointFamily &family);  //determines if family has enough edge triangles to be safe.

	void nextPlayer();

	void currentPlayerMove(const sf::RenderWindow &window);

	void connectionMove(const int row, const int col);  //called when player connects 2 points successfully.
	void diagonalMove(bool &wasPointSelected, const int row, const int col);
	void rightDiagonalMove(bool &wasPointSelected, const int row, const int col);
	void leftDiagonalMove(bool &wasPointSelected, const int row, const int col);

	void completeConnections(const int row, const int col);
	void completeAdjacentConnections(const int row, const int col); //Completes connections to adjacent coordinates.
	void completeAllConnections();

	void resetSelectedPoint();  //Sets it to nullptr.

	void removeEmptyFamilies();


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
	std::list<PointFamily> families;
};

bool isDiagonal(const Coordinate2i c1, const Coordinate2i c2);

sf::Vector2u calculateTopLeft(const sf::RenderWindow &window, const int size, const int spacing);
bool isNeighbouringCoord(Coordinate2i coord1, Coordinate2i coord2);
int max(int a, int b);
int min(int a, int b);


