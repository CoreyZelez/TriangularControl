#include <SFML/Graphics.hpp>
#include "Test.h"

int main()
{
	using namespace sf;

	RenderWindow window(VideoMode(1280, 720), "Triangular Control", Style::Default);
	window.setFramerateLimit(60);

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


		window.display();
	}

	
	return 0;
}