#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>
#include "ATextBox.h"
#include "Enemy.h"

class Enemy;

class EnemyTextBox: public ATextBox
{
private:
    Enemy* m_pEnemy;
    float duration = 0.0f;
public:
    EnemyTextBox(sf::Font& pFont, Enemy* pEnemy, float a_duration);
    ~EnemyTextBox();

    void    initialize() override;
    void    update(float deltaTime) override;
    void    draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};