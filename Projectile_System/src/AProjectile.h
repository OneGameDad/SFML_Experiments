#pragma once

#include <memory>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Rectangle.h"
#include "ProjectileTextBox.h"

/* TODO:
    Projectile spawning and setting velocity/direction/path
    Add collidability to characters and objects
    Collision events
    Collision matrix
*/

#define END_EFFECT_DURATION 0.25f

class AProjectile: public Rectangle
{
protected:
    float lifetime = 0.0f;
    float health = 0.0f;
    float velocity = 0.0f;
    float direction = 0.0f;
    e_collibable collidable_type = PROJECTILE;

    std::unique_ptr<ProjectileTextBox> m_collisionEffect;
public:
    AProjectile(sf::Vector2f a_size, sf::Vector2f a_position, sf::Font* pFont);
    ~AProjectile();

    void damage(Rectangle* pOther);
};