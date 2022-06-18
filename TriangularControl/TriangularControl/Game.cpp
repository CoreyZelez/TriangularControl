#include "Game.h"
#include <assert.h>

const int MAX_SIZE = 23;
const int POINT_SPACING = 44;

Game::Game(const sf::RenderWindow &window, const int size)
	: size(size)
{
	assert(size > 0 && size <= MAX_SIZE);

	sf::Vector2u boardTopLeft = calculateTopLeft(window, size, POINT_SPACING);
	const int topLeftX = boardTopLeft.x;
	const int topLeftY = boardTopLeft.y;

	// Initialises board
	for(int rowNum = 0; rowNum < size; ++rowNum)
	{
		std::vector<Point> row;
		for(int colNum = 0; colNum < size; ++colNum)
		{
			const float x = (float)topLeftX + (POINT_SPACING * colNum);
			const float y = (float)topLeftY + (POINT_SPACING * rowNum);
			row.push_back(Point(sf::Vector2f(x, y)));
		}

		board.push_back(row);
	}
}

void Game::drawBoard(sf::RenderWindow &window) const
{
	for(auto row : board)
	{
		for(Point point : row)
		{
			point.draw(window);
		}
	}
}

sf::Vector2u calculateTopLeft(const sf::RenderWindow &window, const int size, const int spacing)
{
	sf::Vector2u windowRegion = window.getSize();
	const int x = (windowRegion.x - (size * spacing)) / 2;
	const int y = ((windowRegion.y - (size * spacing)) / 2) + 8;
	return sf::Vector2u(x, y);
}
