#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>

int main()
{
	//Setup
	sf::RenderWindow window(sf::VideoMode(640, 480), "Hello World");

	sf::Font font;
	font.loadFromFile("images/NotoSans.ttf");

	sf::Text text("Hello World!", font, 30);
	text.move(100.0f, 0.0f);
	while (window.isOpen())
	{
		//Handle Events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyReleased)
			{
				if (event.key.code != sf::Keyboard::Escape)
					continue;
				else
				{
					window.close();
					std::cout << "Exiting...\n";
					exit(EXIT_SUCCESS);
				}
			}
		}

		window.clear();
		window.draw(text);
		window.display();
	}
	//Cleanup
	return (0);
}
