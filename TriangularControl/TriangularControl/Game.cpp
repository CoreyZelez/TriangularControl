#include "Game.h"
#include <assert.h>


bool Game::lockClick = false;

Game::Game(const sf::RenderWindow &window, const int size)
	: size(size), pointSpacing(44)
{
	assert(size > 0 && size <= maxSize);

	//Initialises players
	players.push_back(Player(sf::Color::Blue));
	players.push_back(Player(sf::Color::Red));
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
	if(!lockClick && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		lockClick = true;
		for(auto row : points)
		{
			for(Point point : row)
			{
				if(point.detectMouseClick(window))
				{

				}
			}
		}
	}

	if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		lockClick = false;
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

//Calculates the correct top left position of the board.
sf::Vector2u calculateTopLeft(const sf::RenderWindow &window, const int size, const int spacing)
{
	sf::Vector2u windowRegion = window.getSize();
	const int x = (windowRegion.x - (size * spacing)) / 2;
	const int y = ((windowRegion.y - (size * spacing)) / 2) + 10;
	return sf::Vector2u(x, y);
}
