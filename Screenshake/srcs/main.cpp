#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "Eye.hpp"
#include "Camera.hpp"
#include "PerlinNoiseGenerator.hpp"
#include "data.hpp"

int main()
{
	try
	{
		//Setup
		sf::Clock clock;
		g_data.setTime(&clock);
		sf::RenderWindow window(sf::VideoMode(640, 480), "Camera Shake");
		window.setFramerateLimit(60);
		auto &PNG = PerlinNoiseGenerator::Instance(); 
		PNG.Load("images/noiseTexture.png"); //Must be loaded before camera
		
		Camera camera(&clock, &window);
		sf::Texture texture0;
		texture0.loadFromFile("images/googly-a.png");
		sf::Texture texture1;
		texture1.loadFromFile("images/googly-b.png");
		sf::Texture texture2;
		texture2.loadFromFile("images/googly-c.png");
		sf::Texture texture3;
		texture3.loadFromFile("images/googly-d.png");
		sf::Texture texture4;
		texture4.loadFromFile("images/googly-e.png");

		Eye eye(&clock);
		eye.setTextures(texture0);
		eye.setTextures(texture1);
		eye.setTextures(texture2);
		eye.setTextures(texture3);
		eye.setTextures(texture4);
		eye.setPosition(100, 100);

		while (window.isOpen())
		{
			g_data.updateTime(&clock);
			//Handle Events
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || event.type == sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::Space)
					{
						std::cout << "IsAnimating set to true\n";
						eye.setIsAnimating();
						camera.beginCameraShake();
					}
					else if (event.key.code != sf::Keyboard::Escape)
						continue;
					else
					{
						window.close();
						std::cout << "Exiting...\n";
						exit(EXIT_SUCCESS);
					}
				}
			}

			eye.Update();
			camera.Update();
			window.clear();
			window.draw(eye.getSprite());
			window.display();
		}
		//Cleanup
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}
