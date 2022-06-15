#include <SFML/Graphics.hpp>
#include <memory>
#include "stdafx.h"
#include "project.hpp"
#include "c_application.h"
#include "ArrayElementBar.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(project::SCREEN_WIDTH, project::SCREEN_HEIGHT), "sort visualiser");
	window.setFramerateLimit(60);

	sf::Event event;
	
	g_application->initialize();
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) window.close();
			}
		}
		window.clear();
		window.draw(*g_application.get());
		window.display();
	}

	return 0;
}

