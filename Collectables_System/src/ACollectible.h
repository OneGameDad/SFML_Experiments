#pragma once

#include <memory>
#include <cmath>
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Rectangle.h"
#include "Game.h"
#include "Player.h"

enum e_coll_states
{
    INACTIVE,
    ACTIVE
};

class ProjectileTextBox;

class AProjectile: public Rectangle
{
protected:
    Game*   m_pGame;
    float   lifetime = 0.0f;
    e_coll_states state = INACTIVE;

    sf::Vector2f startPos = {0.0f, 0.0f};


    e_collidable collidable_type = COLLECTIBLE;
    
    void    beCollected(Player* pOther);
    void    reset();
    void    updateCollisions();

public:
    AProjectile(Game* pGame, sf::Texture *a_texture);
    ~AProjectile();

    void    update(float deltaTime);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void    activate(sf::Vector2f a_posiition, float a_lifetime, float a_velocity, float a_direction);
    void    deactivate();
    e_coll_states    getState() const { return (state); }
    float   getLifetime() const { return (lifetime); }
    sf::Sprite getSprite() const { return (m_sprite); }
};