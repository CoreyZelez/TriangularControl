#include "Game2Player.h"
#include <assert.h>
#include <iostream>
#include <algorithm>


bool Game2Player::lockClick = false;

Game2Player::Game2Player(const sf::RenderWindow &window, const int size, const int safetyNum)
	: size(size), pointSpacing(47), sourcePointCoords{ -2, -2 }, safetyNum(safetyNum)
{
	assert(size > 0 && size <= maxSize);

	//Initialises players
	players.push_back(Player(sf::Color(25, 25, 255, 255)));
	players.push_back(Player(sf::Color(255, 30, 30)));
	currentPlayer = &players[0];

	//Initialises board
	sf::Vector2u boardTopLeft = calculateTopLeft(window, size, pointSpacing);
	const int topLeftX = boardTopLeft.x;
	const int topLeftY = boardTopLeft.y;

	for(int rowNum = 0; rowNum < size; ++rowNum)
	{
		std::vector<Point> row;
		for(int colNum = 0; colNum < size; ++colNum)
		{
			const float x = (float)topLeftX + (pointSpacing * colNum);
			const float y = (float)topLeftY + (pointSpacing * rowNum);
			row.push_back(Point(sf::Vector2f(x, y)));
		}

		points.push_back(row);
	}
}

void Game2Player::update(const sf::RenderWindow &window)
{
	currentPlayerMove(window);
}

void Game2Player::nextPlayer()
{
	if(currentPlayer == &players[0])
	{
		currentPlayer = &players[1];
	}
	else
	{
		currentPlayer = &players[0];
	}
}

void Game2Player::drawBoard(sf::RenderWindow &window) const
{
	for(Connection line : connections)
	{
		line.draw(window);
	}

	for(auto row : points)
	{
		for(Point point : row)
		{
			point.draw(window);
		}
	}
}

void Game2Player::resetSelectedPoint()
{
	if(sourcePoint != nullptr)
	{
		sourcePoint->changeSelected();
	}
	sourcePoint = nullptr;
	sourcePointCoords = { -2, -2 };
}

void Game2Player::completeConnections(const int row, const int col)
{
	assert(!points[row][col].noOwner());

	const Point &point = points[row][col];

	const int prevRow = row - 1;
	const int nextRow = row + 1;
	const int prevCol = col - 1;
	const int nextCol = col + 1;

	//Adds horizontal and vertical connections.
	if(prevRow >= 0 && point.compareOwner(points[prevRow][col])) 
	{
		//Only adds connection if not already in connections (no duplication of connections).
		if(!connectionSearch(connections, point, points[prevRow][col]))
		{
			connections.push_back(Connection(point, points[prevRow][col]));
		}
	}
	if(nextRow < size && point.compareOwner(points[nextRow][col]))
	{
		//Only adds connection if not already in connections (no duplication of connections).
		if(!connectionSearch(connections, point, points[nextRow][col]))
		{
			connections.push_back(Connection(point, points[nextRow][col]));
		}
	}
	if(prevCol >= 0 && point.compareOwner(points[row][prevCol]))
	{
		//Only adds connection if not already in connections (no duplication of connections).
		if(!connectionSearch(connections, point, points[row][prevCol]))
		{
			connections.push_back(Connection(point, points[row][prevCol]));
		}
	}
	if(nextCol < size && point.compareOwner(points[row][nextCol]))
	{
		//Only adds connection if not already in connections (no duplication of connections).
		if(!connectionSearch(connections, point, points[row][nextCol]))
		{
			connections.push_back(Connection(point, points[row][nextCol]));
		}
	}

	//Adds diagonal connections.
	//Upper right diagonal.
	if(prevRow >= 0 && nextCol < size)
	{
		if(point.compareOwner(points[prevRow][nextCol]) &&
			(point.compareOwner(points[prevRow][col]) || point.compareOwner(points[row][nextCol])))
		{
			if(!connectionSearch(connections, points[row][nextCol], points[prevRow][col]))
			{
				connections.push_back(Connection(points[row][col], points[prevRow][nextCol]));
			}
		}
	}
	//Lower right diagonal.
	if(nextRow < size && nextCol < size)
	{
		if(point.compareOwner(points[nextRow][nextCol]) &&
			(point.compareOwner(points[row][nextCol]) || point.compareOwner(points[nextRow][col])))
		{
			if(!connectionSearch(connections, points[row][nextCol], points[nextRow][col]))
			{
				connections.push_back(Connection(points[row][col], points[nextRow][nextCol]));
			}
		}
	}
	//Upper left diagonal.
	if(prevRow >= 0 && prevCol >= 0)
	{
		if(point.compareOwner(points[prevRow][prevCol]) &&
			(point.compareOwner(points[prevRow][col]) || point.compareOwner(points[row][prevCol])))
		{
			if(!connectionSearch(connections, points[prevRow][col], points[row][prevCol]))
			{
				connections.push_back(Connection(points[row][col], points[prevRow][prevCol]));
			}
		}
	}
	//Lower left diagonal.
	if(nextRow < size && prevCol >= 0)
	{
		if(point.compareOwner(points[nextRow][prevCol]) &&
			(point.compareOwner(points[row][prevCol]) || point.compareOwner(points[nextRow][col])))
		{
			if(!connectionSearch(connections, points[row][prevCol], points[nextRow][col]))
			{
				connections.push_back(Connection(points[row][col], points[nextRow][prevCol]));
			}
		}
	}
}

void Game2Player::completeAdjacentConnections(const int row, const int col)
{
	const int nextRow = row + 1;
	const int prevRow = row - 1;
	const int nextCol = col + 1;
	const int prevCol = col - 1;
	if(nextCol < size && points[row][nextCol].compareOwner(currentPlayer))
	{
		completeConnections(row, nextCol);
	}
	if(nextRow < size && points[nextRow][col].compareOwner(currentPlayer))
	{
		completeConnections(nextRow, col);
	}
	if(prevCol > 0 && points[row][prevCol].compareOwner(currentPlayer))
	{
		completeConnections(row, prevCol);
	}
	if(prevRow > 0 && points[prevRow][col].compareOwner(currentPlayer))
	{
		completeConnections(prevRow, col);
	}
}

void Game2Player::currentPlayerMove(const sf::RenderWindow &window)
{
	//Updates board based on move by current player.
	if(!lockClick && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		lockClick = true;
		const sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		bool wasPointSelected = false;
		for(int row = 0; row < size; ++row)
		{
			for(int col = 0; col < size; ++col)
			{
				Point &point = points[row][col];
				if(point.detectMouseClick(mousePosition))
				{
					wasPointSelected = true;

					//Case invalid point selection
					if((!point.compareOwner(currentPlayer) && !point.noOwner())
						|| (sourcePoint != nullptr && !isNeighbouringCoord(sourcePointCoords, { row, col })))
					{
						wasPointSelected = false;
					}
					//Case this is the first point selected.
					else if(sourcePoint == nullptr)
					{
						sourcePoint = &point;
						sourcePointCoords = { row, col };
						sourcePoint->changeSelected();
					}
					//Case point is the same as the previously selected point.
					else if(&point == sourcePoint)
					{
						//Checks point has no owner.
						if(sourcePoint->noOwner())
						{
							sourcePoint->setOwner(*currentPlayer);
							completeConnections(row, col);
							completeAdjacentConnections(row, col);
							resetSelectedPoint();
							nextPlayer();
						}
						else
						{
							wasPointSelected = false;
						}
					}
					//Case both points already have existing connection.
					else if(connectionSearch(connections, *sourcePoint, point))
					{
						wasPointSelected = false;
					}
					//Case point is different to prev selected
					else
					{
						//Case move is diagonal. Must check for blocking diagonal.
						if(Connection(*sourcePoint, point).isDiagonal())
						{
							diagonalMove(wasPointSelected, row, col);
						}
						//Case connection is not diagonal.
						else
						{
							playerConnectionMove(row, col);
						}
					}

					goto EndLoop;
				}
			}
		}
	EndLoop:
		//Case the selection was cancelled or no point selected.
		if(!wasPointSelected)
		{
			resetSelectedPoint();
		}
	}

	if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		lockClick = false;
	}
}

void Game2Player::playerConnectionMove(const int row, const int col)
{
	Point &point = points[row][col];

	sourcePoint->setOwner(*currentPlayer);
	point.setOwner(*currentPlayer);

	connections.push_back(Connection(*sourcePoint, point));

	//Connects necessary points.
	completeConnections(sourcePointCoords.row, sourcePointCoords.col);
	completeConnections(row, col);
	completeAdjacentConnections(sourcePointCoords.row, sourcePointCoords.col);
	completeAdjacentConnections(row, col);

	resetSelectedPoint();
	nextPlayer();
}

void Game2Player::diagonalMove(bool &wasPointSelected, const int row, const int col)
{
	Point &point = points[row][col];

	int r1, c1, r2, c2;

	//Case diagonal is left.
	if(sourcePointCoords.row - row == sourcePointCoords.col - col)
	{
		leftDiagonalMove(wasPointSelected, row, col);
	}
	//Case diagonal is right.
	else
	{
		rightDiagonalMove(wasPointSelected, row, col);
	}
}

void Game2Player::rightDiagonalMove(bool &wasPointSelected, const int row, const int col)
{
	const int r1 = max(sourcePointCoords.row, row);
	const int c1 = max(sourcePointCoords.col, col);
	const int r2 = r1 - 1;
	const int c2 = c1 - 1;

	//Adds the connection if valid.
	if(connectionSearch(connections, points[r1][c1], points[r2][c2]))
	{
		wasPointSelected = false;
	}
	else
	{
		playerConnectionMove(row, col);
	}
}

void Game2Player::leftDiagonalMove(bool &wasPointSelected, const int row, const int col)
{
	const int r1 = max(sourcePointCoords.row, row);
	const int c1 = min(sourcePointCoords.col, col);
	const int r2 = r1 - 1;
	const int c2 = c1 + 1;

	//Adds the connection if valid.
	if(connectionSearch(connections, points[r1][c1], points[r2][c2]))
	{
		wasPointSelected = false;
	}
	else
	{
		playerConnectionMove(row, col);
	}
}


//Calculates the correct top left position of the board.
sf::Vector2u calculateTopLeft(const sf::RenderWindow &window, const int size, const int spacing)
{
	sf::Vector2u windowRegion = window.getSize();
	const int x = (windowRegion.x - (size * spacing)) / 2;
	const int y = ((windowRegion.y - (size * spacing)) / 2) + 10;  //+10 because slightly too low.
	return sf::Vector2u(x, y);
}

bool isNeighbouringCoord(Coordinates2i coord1, Coordinates2i coord2)
{
	if(abs(coord1.row - coord2.row) > 1 || abs(coord1.col - coord2.col) > 1)
	{
		return false;
	}
	 
	return true;
}

int max(int a, int b)
{
	if(a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int min(int a, int b)
{
	if(a > b)
	{
		return b;
	}
	else
	{
		return a;
	}
}
