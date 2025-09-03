#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/VideoMode.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Hello World");
	sf::CircleShape shape(200);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(shape);
		window.display();
	}
	return (0);
}
