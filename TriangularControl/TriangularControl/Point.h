#pragma once
#include "Player.h"
#include "Family.h"

class Family; 

class Point
{
public:

	Point(const sf::Vector2f pos);

	//Functions.
	void draw(sf::RenderWindow &window) const;

	bool detectMouseClick(const sf::Vector2i mousePosition);

	bool compareOwner(Point point) const;
	bool compareOwner(const Player *player) const;
	bool noOwner() const;

	bool compareFamily(Point point) const;

	//Getters and setters.
	sf::Vector2f getPosition() const;

	void setOwner(const Player &newOwner);
	sf::Color getOwnerColor() const;  //Returns white if no owner.
	void setColorYellow();  

	bool getSelected() const;
	void changeSelected();

	const static float getPointSize();

	void setFamily(const Family *family);

private:
	//Primitive members.
	const static float selectionRadiusMultiplier;
	const static float pointRadius;
	const static float selectedPointRadius;  
	const static float pointOutlineThickness;  //Outline of circle thickness for player controlled points.

	bool selected = false;

	//Objects.
	const Family *family;
	sf::CircleShape circle;
	const Player *owner = nullptr;  //nullptr indicates no owner.
	const sf::Vector2f position;
};

int squareDistance(sf::Vector2i vec1, sf::Vector2i vec2);

