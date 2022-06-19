#include "Game.h"
#include <assert.h>


Game::Game(const sf::RenderWindow &window, const int size)
	: size(size), pointSpacing(44)
{
	assert(size > 0 && size <= maxSize);

	sf::Vector2u boardTopLeft = calculateTopLeft(window, size, pointSpacing);
	const int topLeftX = boardTopLeft.x;
	const int topLeftY = boardTopLeft.y;

	// Initialises board
	for(int rowNum = 0; rowNum < size; ++rowNum)
	{
		std::vector<Point> row;
		for(int colNum = 0; colNum < size; ++colNum)
		{
			const float x = (float)topLeftX + (pointSpacing * colNum);
			const float y = (float)topLeftY + (pointSpacing * rowNum);
			row.push_back(Point(sf::Vector2f(x, y)));
		}

		board.push_back(row);
	}

	//testing
	players.push_back(sf::Color::Red);
	board[0][0].setOwner(players[0]);
	board[0][1].setOwner(players[0]);
	board[4][4].setOwner(players[0]);
	board[5][4].setOwner(players[0]);
	board[8][10].setOwner(players[0]);
	board[7][11].setOwner(players[0]);
	board[9][11].setOwner(players[0]);
	board[9][9].setOwner(players[0]);
	board[9][10].setOwner(players[0]);
	board[13][3].setOwner(players[0]);
	board[13][4].setOwner(players[0]);
	board[5][20].setOwner(players[0]);
	board[6][20].setOwner(players[0]);

	connections.push_back(Connection(board[0][1], board[0][0]));
	connections.push_back(Connection(board[13][3], board[13][4]));


	connections.push_back(Connection(board[4][4], board[5][4]));
	connections.push_back(Connection(board[6][20], board[5][20]));


	connections.push_back(Connection(board[8][10], board[9][11]));
	connections.push_back(Connection(board[8][10], board[9][9]));
	connections.push_back(Connection(board[8][10], board[7][11]));
	connections.push_back(Connection(board[8][10], board[7][9]));

}

void Game::drawBoard(sf::RenderWindow &window) const
{
	for(Connection line : connections)
	{
		line.draw(window);
	}

	for(auto row : board)
	{
		for(Point point : row)
		{
			point.draw(window);
		}
	}
}

//Calculates the correct top left position of the board.
sf::Vector2u calculateTopLeft(const sf::RenderWindow &window, const int size, const int spacing)
{
	sf::Vector2u windowRegion = window.getSize();
	const int x = (windowRegion.x - (size * spacing)) / 2;
	const int y = ((windowRegion.y - (size * spacing)) / 2) + 10;
	return sf::Vector2u(x, y);
}
