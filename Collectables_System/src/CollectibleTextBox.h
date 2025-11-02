#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>
#include "ATextBox.h"
#include "Collectible.h"

class Collectible;

class CollectibleTextBox: public ATextBox
{
private:
    Collectible* m_pCollectible;
    float duration = 0.0f;
public:
    CollectibleTextBox(sf::Font& pFont, Collectible* pCollectible, float a_duration);
    ~CollectibleTextBox();

    void    initialize() override;
    void    update(float deltaTime) override;
    void    draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};