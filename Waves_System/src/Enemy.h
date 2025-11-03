#pragma once

#include <memory>
#include <cmath>
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Rectangle.h"
#include "EnemyTextBox.h"
#include "Game.h"
#include "Constants.h"

class EnemyTextBox;

class Enemy: public Rectangle
{
protected:
    Game*   m_pGame;
    float   lifetime = 0.0f;
    float   health = 0.0f;
    float   speed = 0.0f;
    float   angle = 0.0f;
    float   deathTime = AFTER_TIME;
    e_enem_states state = DISABLED;

    sf::Vector2f startPos = {0.0f, 0.0f};

    e_collidable collidable_type = ENEMY;
    e_coll_types spawnType = HEALING;
    float   spawnLifetime = 3.5f;

    std::unique_ptr<EnemyTextBox> m_collisionEffect;
    std::string explosion = "*HAVE AT YE*";
    
    //void    damage(Vampire* pOther);
    void    reset();
    void    updateMovement(float deltaTime);
    void    updateCollisions();
    void    dying(float delatTime);
    
    void    setBeyond();
public:
    Enemy(Game* pGame, sf::Texture *a_texture);
    ~Enemy();

    void    update(float deltaTime);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void    activate(sf::Vector2f a_position, float a_lifetime, float a_speed, float a_angle);
    void    deactivate();
    void    setFlying();
    e_enem_states    getState() const { return (state); }
    float   getLifetime() const { return (lifetime); }
    sf::Sprite getSprite() const { return (m_sprite); }
    void    explode();
};