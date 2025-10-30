#pragma once

#include <memory>
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Rectangle.h"
#include "ProjectileTextBox.h"
#include "Game.h"
#include "Vampire.h"


/* TODO:
    Projectile spawning and setting velocity/direction/path
    Add collidability to characters and objects
    Collision events
    Collision matrix
*/

enum e_proj_states
{
    INACTIVE,
    SPAWNING,
    FLYING,
    RICHOCETING,
    DYING,
}

#define END_EFFECT_DURATION 0.25f
#define PI 3.14159265f
#define DYING_TIME 3.5f

class AProjectile: public Rectangle
{
protected:
    Game*   m_pGame;
    float   lifetime = 0.0f;
    float   health = 0.0f;
    float   velocity = 0.0f;
    float   direction = 0.0f;
    float   death_rattle = DYING_TIME;
    e_proj_states state = INACTIVE;

    float   projWidth = 5.0f;
    float   projHeight = 5.0f;
    sf::Vector2f startPos = {0.0f, 0.0f};

    e_collibable collidable_type = PROJECTILE;

    std::unique_ptr<ProjectileTextBox> m_collisionEffect;
    std::string explosion = "*explosion*";
    std::string disarming = "plop";
    
    void    damage(Vampire* pOther);
    void    reset();
    void    updateMovement(float deltaTime);
    void    updateCollisions();
    void    dying(float delatTime);
    void    disarm();
    void    explode();
public:
    AProjectile(Game* pGame);
    ~AProjectile();

    void    update(float deltaTime);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void    activate(sf::Vector2f a_posiition, float a_lifetime, float a_velocity, float a_direction);
    void    deactivate();
    void    setFlying();
    e_proj_states    getState() const { return (state); }
    float   getLifetime() const { return (lifetime); }
};