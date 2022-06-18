#include <SFML/Graphics.hpp>
#include "Test.h"

#include "Point.h"

int main()
{
	using namespace sf;

	ContextSettings settings;
	settings.antialiasingLevel = 8;

	RenderWindow window(VideoMode(1280, 720), "Triangular Control", Style::Default, settings); 
	window.setFramerateLimit(60);

	Point point(Vector2f(30, 30));
	Player player(Color(200, 30, 30));
	point.setOwner(player);


	while(window.isOpen())
	{
		Event event;

		while(window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		
		//Update


		//Draw
		window.clear();

		point.draw(window);

		window.display();
	}

	return 0;
}