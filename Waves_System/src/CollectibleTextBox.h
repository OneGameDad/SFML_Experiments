#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>
#include "ATextBox.h"
#include "ACollectible.h"

class ACollectible;

class CollectibleTextBox: public ATextBox
{
private:
    ACollectible* m_pCollectible;
    float duration = 0.0f;
public:
    CollectibleTextBox(sf::Font& pFont, ACollectible* pCollectible, float a_duration);
    ~CollectibleTextBox();

    void    initialize() override;
    void    update(float deltaTime) override;
    void    draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};