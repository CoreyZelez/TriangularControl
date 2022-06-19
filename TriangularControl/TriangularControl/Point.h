#pragma once
#include "Player.h"
class Point
{
public:

	Point(const sf::Vector2f pos);

	void draw(sf::RenderWindow &window) const;

	bool detectMouseClick(const sf::RenderWindow &window);

	bool compareOwner(const Player &player) const;

	//Getters and setters.
	sf::Vector2f getPosition() const;

	void setOwner(const Player &newOwner);
	sf::Color getOwnerColor() const;

	bool getSelected() const;
	void changeSelected();

	const static float getPointSize();

private:
	const static float pointSize;
	const static float selectedPointSize;

	sf::CircleShape circle;
	const Player *owner = nullptr;  //nullptr indicates no owner.
	bool selected = false;
	const sf::Vector2f position;
};

int squareDistance(sf::Vector2i vec1, sf::Vector2i vec2);

