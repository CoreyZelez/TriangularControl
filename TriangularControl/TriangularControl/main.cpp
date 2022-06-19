#include "Test.h"
#include "Game.h"
#include "Point.h"

int main()
{
	using namespace sf;

	ContextSettings settings;
	settings.antialiasingLevel = 8;

	RenderWindow window(VideoMode(1920, 1080), "Triangular Control", Style::Fullscreen, settings); 
	window.setFramerateLimit(60);

	Game game(window, 21);


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
		game.update(window);

		//Draw
		window.clear();

		game.drawBoard(window);

		window.display();
	}

	return 0;
}