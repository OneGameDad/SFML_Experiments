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
#include "GameTime.hpp"

int main()
{
	try
	{
		//Setup
		GameTime::getInstance();
		GameTime::getInstance().setTime();
		sf::RenderWindow window(sf::VideoMode(640, 480), "Camera Shake");
		window.setFramerateLimit(60);
		auto &PNG = PerlinNoiseGenerator::Instance(); 
		PNG.Load("images/noiseTexture.png"); //Must be loaded before camera
		
		Camera camera(&window);
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

		Eye eye;
		eye.setTextures(texture0);
		eye.setTextures(texture1);
		eye.setTextures(texture2);
		eye.setTextures(texture3);
		eye.setTextures(texture4);
		eye.setPosition(100, 100);

		while (window.isOpen())
		{
			GameTime::getInstance().updateTime();
			//Handle Events
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || event.type == sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::Space)
					{
						eye.setIsAnimating();
						//camera.beginCameraShake();
					}
					else if (event.key.code == sf::Keyboard::Enter)
					{
						std::cout << "Time Scale: " << GameTime::getInstance().getTimeScale() << std::endl;
						if (GameTime::getInstance().getTimeScale() != 1.0)
							GameTime::getInstance().setTimeScale(1.0);
						else
							GameTime::getInstance().setTimeScale(0.1);
						std::cout << "Time Scale: " << GameTime::getInstance().getTimeScale() << std::endl;
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
