#pragma once

#include <memory>
#include <cmath>
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Rectangle.h"
#include "ProjectileTextBox.h"
#include "Game.h"
#include "Constants.h"


#define PI 3.14159265f

class ProjectileTextBox;

class Terrain: public Rectangle
{
protected:
    Game*   m_pGame;
    float   lifetime = 0.0f;
    float   health = 0.0f;
    float   speed = 0.0f;
    float   angle = 0.0f;

    const float terrainWidth = 150.0f;
    const float terrainHeight = 50.0f;
    e_terr_states state = INVIS;

    sf::Vector2f startPos = {0.0f, 0.0f};

    e_collidable collidable_type = TERRAIN;

    void    reset();
    void    updateMovement(float deltaTime);
    void    updateCollisions();

public:
    Terrain(Game* pGame, sf::Texture *a_texture);
    ~Terrain();

    void    update(float deltaTime);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void    activate(sf::Vector2f a_position, float a_lifetime, float a_speed, float a_angle);
    void    deactivate();
    e_terr_states    getState() const { return (state); }
    float   getLifetime() const { return (lifetime); }
    sf::Sprite getSprite() const { return (m_sprite); }
};