#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>
#include "ATextBox.h"
#include "AProjectile.h"

class AProjectile;

class ProjectileTextBox: public ATextBox
{
private:
    AProjectile* m_pProjectile;
    float duration = 0.0f;
public:
    ProjectileTextBox(sf::Font& pFont, AProjectile* pProjectile, float a_duration);
    ~ProjectileTextBox();

    void    initialize() override;
    void    update(float deltaTime) override;
    void    draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};