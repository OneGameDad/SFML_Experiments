#pragma once

#include "HUDComponentWithFollow.hpp"
#include "Player.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

class HealthBar: public HUDComponentWithFollow
{
private:
    Player* player;
    std::unique_ptr<sf::Sprite> sprite;
public:
    HealthBar();
    ~HealthBar();
    
    void    initialize();
    void    setQueryTarget(Player& thePlayer) override;
}