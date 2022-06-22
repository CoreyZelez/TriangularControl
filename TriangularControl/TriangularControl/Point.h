#pragma once
#include "Player.h"
#include "PointFamily.h"

class PointFamily;

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

	//Getters and setters.
	sf::Vector2f getPosition() const;

	void setOwner(const Player &newOwner);
	const Player *getOwner() const;
	sf::Color getOwnerColor() const;  //Returns white if no owner.
	void setColorYellow();  

	void setFamily(PointFamily *family);
	PointFamily* getFamily() const;
	bool hasFamily();

	bool getSelected() const;
	void changeSelected();

	const static float getPointSize();
private:
	//Static members.
	const static float selectionRadiusMultiplier;
	const static float pointRadius;
	const static float selectedPointRadius;  
	const static float pointOutlineThickness;  //Outline of circle thickness for player controlled points.

	//Primitive members.
	bool selected = false;

	//Objects.
	sf::CircleShape circle;
	const Player *owner = nullptr;  //nullptr indicates no owner.
	const sf::Vector2f position;
	PointFamily *family = nullptr;
};

int squareDistance(sf::Vector2i vec1, sf::Vector2i vec2);

