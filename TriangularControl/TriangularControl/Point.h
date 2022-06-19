#pragma once
#include "Player.h"
class Point
{
public:

	Point(const sf::Vector2f pos);

	void draw(sf::RenderWindow &window) const;

	bool detectMouseClick(const sf::Vector2i mousePosition);

	bool compareOwner(const Player *player) const;
	bool noOwner();

	void changeColor(){ circle.setFillColor(sf::Color::Green); }

	//Getters and setters.
	sf::Vector2f getPosition() const;

	void setOwner(const Player &newOwner);
	sf::Color getOwnerColor() const;  //Returns white if no owner.

	bool getSelected() const;
	void changeSelected();

	const static float getPointSize();

private:
	const static float pointRadius;
	const static float selectedPointRadius;
	const static float pointOutlineThickness;

	sf::CircleShape circle;
	const Player *owner = nullptr;  //nullptr indicates no owner.
	bool selected = false;
	const sf::Vector2f position;
};

int squareDistance(sf::Vector2i vec1, sf::Vector2i vec2);

