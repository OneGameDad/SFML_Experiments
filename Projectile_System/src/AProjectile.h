#pragma once

#include <memory>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Rectangle.h"
#include "ProjectileTextBox.h"
#include "Game.h"

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
    Game*   m_pGame;
    float   lifetime = 0.0f;
    float   health = 0.0f;
    float   velocity = 0.0f;
    float   direction = 0.0f;
    bool    isActive = false;

    float   projWidth = 5.0f;
    float   projHeight = 5.0f;
    sf::Vector2f startPos = {0.0f, 0.0f};

    e_collibable collidable_type = PROJECTILE;

    std::unique_ptr<ProjectileTextBox> m_collisionEffect;

    void    reset();
    void    damage(Rectangle* pOther);
public:
    AProjectile(Game* pGame);
    ~AProjectile();

    void    update(float deltaTime);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};