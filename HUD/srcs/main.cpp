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
#include "ParticleSystem.hpp"
#include "FireEffect.hpp"
#include "Player.hpp"

int main()
{
	try
	{
		//Setup
		GameTime::getInstance();
		GameTime::getInstance().setTime();
		sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "HUD");
		window.setFramerateLimit(60);
		auto &PNG = PerlinNoiseGenerator::Instance(); 
		PNG.Load("images/noiseTexture.png"); //Must be loaded before camera
		
		Camera camera(&window);
		 std::unique_ptr<Game> pGame = std::make_unique<Game>();
		if (!pGame->initialize())
		{
			std::cerr << "Game Failed to initialise" << std::endl;
			return 1;
		}
/*		sf::Texture texture0;
		texture0.loadFromFile("images/googly-a.png");
		sf::Texture texture1;
		texture1.loadFromFile("images/googly-b.png");
		sf::Texture texture2;
		texture2.loadFromFile("images/googly-c.png");
		sf::Texture texture3;
		texture3.loadFromFile("images/googly-d.png");
		sf::Texture texture4;
		texture4.loadFromFile("images/googly-e.png");

		sf::Texture flame;
		flame.loadFromFile("images/flame_05.png");
		FireEffect fire(50, flame);
		fire.addEmitter(sf::Vector2f({400,500}));
		fire.addEmitter(sf::Vector2f({150,150}));



		Eye eye;
		eye.setTextures(texture0);
		eye.setTextures(texture1);
		eye.setTextures(texture2);
		eye.setTextures(texture3);
		eye.setTextures(texture4);
		eye.setPosition(100, 100);
*/
		sf::RectangleShape rectangle;
		rectangle.setSize({100.0f, 20.0f});
    	rectangle.setOrigin({0.0f, 0.0f});
   		rectangle.setFillColor(sf::Color::Red);
    	rectangle.setPosition({100.0f, 100.0f});
		while (window.isOpen())
		{
			GameTime::getInstance().updateTime();
			//Handle Events
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch(event.type)
				{
					case sf::Event::Closed:
						// "close requested" event: we close the window
						window.close();
						break;
					case sf::Event::KeyPressed:
						pGame->onKeyPressed(event.key.code);
						break;
					case sf::Event::KeyReleased:
						pGame->onKeyReleased(event.key.code);
						break;
					default:
						break;
				}
			}
/*				if (event.type == sf::Event::Closed || event.type == sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::Space)
					{
						camera.beginCameraShake();
					}
					else if (event.key.code == sf::Keyboard::Tab)
					{
						eye.requestGoogly();
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
*/	

//			fire.getEmitters()[0].localPosition = sf::Vector2f(sf::Mouse::getPosition(window));
			pGame->update(GameTime::getInstance().getDeltaTime());
//			eye.Update();
			camera.Update();
//			fire.update();
			window.clear();
			window.draw(rectangle);
			window.draw(*pGame.get());
//			window.draw(eye.getSprite());
//			window.draw(fire);
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
