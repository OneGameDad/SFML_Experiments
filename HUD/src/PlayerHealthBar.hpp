#pragma once

#include "HUDComponent.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>
#include <iostream>

class Player;
class Game;

class PlayerHealthBar: public HUDComponent
{
private:
    Game*   m_pGame;
    Player* m_pPlayer;
    std::unique_ptr<sf::RectangleShape> rectangle;
    sf::Sprite m_sprite;
    sf::Texture texture;
    float playerWidth = 0.0f;
    float playerScale = 0.0f;
    const float maxWidth = 100.0f;
    const float maxHeight = 10.0f;
    

    sf::Vector2f    adjustPosition();
public:
    explicit PlayerHealthBar(Game* pGame);
    ~PlayerHealthBar();
    
    void    initialize() override;
//    void    setQueryTarget(Player& thePlayer);
    void    update(float deltaTime) override;
    void    draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};