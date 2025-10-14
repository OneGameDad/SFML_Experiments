#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/VideoMode.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Hello World");
	sf::CircleShape circle(100, 30);
	circle.setFillColor(sf::Color::Cyan);
	circle.setOutlineColor(sf::Color::Magenta);
	circle.setOutlineThickness(4.0f);
	circle.setPosition(320, 240);

	sf::ConvexShape polygon;
	polygon.setPointCount(3);
	polygon.setPoint(0, sf::Vector2f(0, 0));
	polygon.setPoint(1, sf::Vector2f(0, 10));
	polygon.setPoint(2, sf::Vector2f(100, 50));
	polygon.setFillColor(sf::Color::Green);
	polygon.setOutlineColor(sf::Color::Blue);
	polygon.setOutlineThickness(5);
	polygon.setPosition(10, 20);

	sf::RectangleShape rect({100, 60});
	rect.setFillColor(sf::Color::Red);
	rect.setOutlineColor(sf::Color::Yellow);
	rect.setOutlineThickness(4.0f);
	rect.setPosition(300, 10);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(circle);
		window.draw(polygon);
		window.draw(rect);
		window.display();
	}
	return (0);
}
