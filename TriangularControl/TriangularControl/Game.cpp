#include "Game.h"
#include <assert.h>
#include <iostream>
#include <algorithm>


bool Game::lockClick = false;

Game::Game(const sf::RenderWindow &window, const int size)
	: size(size), pointSpacing(47), sourcePointCoords{-2, -2}
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

void Game::update(const sf::RenderWindow &window)
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
						sourcePoint->setOwner(*currentPlayer);
						resetSelectedPoint();
						nextPlayer();
					}
					//Case point is different to prev selected
					else if(sourcePointCoords.row >= 0)
					{
						//Case move is diagonal. Must check for blocking diagonal.
						if(Connection(*sourcePoint, point).isDiagonal())
						{
							int r1, c1, r2, c2;

							//Case diagonal is left.
							if(sourcePointCoords.row - row == sourcePointCoords.col - col)
							{
								r1 = max(sourcePointCoords.row, row);
								c1 = min(sourcePointCoords.col, col);
								r2 = r1 - 1;
								c2 = c1 + 1;		
							}
							//Case diagonal is right.
							else
							{
								r1 = max(sourcePointCoords.row, row);
								c1 = max(sourcePointCoords.col, col);
								r2 = r1 - 1;
								c2 = c1 - 1;
							}

							//Adds the connection if valid.
							if(connectionSearch(connections, points[r1][c1], points[r2][c2]))
							{
								wasPointSelected = false;
							}
							else
							{
								sourcePoint->setOwner(*currentPlayer);
								point.setOwner(*currentPlayer);
								connections.push_back(Connection(*sourcePoint, point));
								resetSelectedPoint();
								nextPlayer();
							}
						}
						//Case connections is not diagonal.
						else
						{
							sourcePoint->setOwner(*currentPlayer);
							point.setOwner(*currentPlayer);
							connections.push_back(Connection(*sourcePoint, point));
							resetSelectedPoint();
							nextPlayer();
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

void Game::nextPlayer()
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

void Game::drawBoard(sf::RenderWindow &window) const
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

void Game::resetSelectedPoint()
{
	if(sourcePoint != nullptr)
	{
		sourcePoint->changeSelected();
	}
	sourcePoint = nullptr;
	sourcePointCoords = { -2, -2 };
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
