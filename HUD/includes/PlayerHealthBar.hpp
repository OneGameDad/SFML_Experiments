#pragma once

#include "HUDComponentWithFollow.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>

class Player;
class Game;

class PlayerHealthBar: public HUDComponentWithFollow
{
private:
    Game*   m_pGame;
    Player* m_pPlayer;
    sf::RectangleShape* rectangle;
    const float maxWidth = 20.0f;
    const float maxHeight = 5.0f;
public:
    explicit PlayerHealthBar(Game* pGame);
    ~PlayerHealthBar();
    
    void    initialize() override;
    void    initialize(sf::Transformable& thePlayer) override;
    void    initialize(sf::Vector2f a_position) override;
    void    setQueryTarget(Player& thePlayer);
    void    update(float deltaTime) override;
    void    draw(sf::RenderTarget& target, sf::RenderStates states) const;
};