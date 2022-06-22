#include "Test.h"
#include "Game2Player.h"
#include "Point.h"


int main()
{
	using namespace sf;

	ContextSettings settings;
	settings.antialiasingLevel = 8;

	RenderWindow window(VideoMode(1920, 1080), "Triangular Control", Style::Fullscreen, settings); 
	window.setFramerateLimit(60);

	Game2Player game2Player(window, 21, 13);


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
		game2Player.update(window);

		//Draw
		window.clear();

		game2Player.drawBoard(window);

		window.display();
	}

	return 0;
}
