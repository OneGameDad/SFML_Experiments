#include "AProjectile.h"

AProjectile::AProjectile(Game* pGame)
    : Rectangle(sf::Vector2f{projWidth, projHeight}, startPos), m_pGame(pGame), m_collisionEffect(std::make_unique<ProjectileTextBox>(m_pGame->getFont(), this, END_EFFECT_DURATION))
{}

AProjectile::~AProjectile(){}

void    AProjectile::update(float deltaTime)
{
    if (state == INACTIVE)
        return;
    else if (state == SPAWNING)
    {
        updateCollisions();
        setFlying();
        return ();
    }
    else if (state == FLYING)
    {
        lifetime -= deltaTime;
        updateMovement(deltaTime);
        updateCollisions();
        if (lifetime <= 0.0f)
        {
            disarm();
        }
    }
    else if (state == DYING)
    {
        dying(deltaTime);
    }
}


void    AProjectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (state == SPAWNING || state == FLYING || state == RICHOCETING)
    {
        target->draw(m_sprite, states);   
    }
    else if (state == DYING)
    {
        target->draw(m_collisionEffect, states);
    }
}

void    AProjectile::activate(sf::Vector2f a_posiition, float a_lifetime, float a_velocity, float a_direction)
{
    reset();
    setPosition(a_position);
    sprite.setPosition(getPosition());
    lifetime = a_lifetime;
    a_velocity = a_velocity;
    direction = a_direction;
    state = SPAWNING;
}

void    AProjectile::deactivate()
{
    state = INACTIVE;
}

void    AProjectile::reset()
{
    state = INACTIVE;
    lifetime = 0.0f;
    health = 0.0f;
    velocity = 0.0f;
    direction = 0.0f;
    sf::Vector2f startPos = {0.0f, 0.0f};
}

void    AProjectile::updateMovement(float deltaTime)
{
    float radians = direction * PI / 180.f;
    position.x += velocity * std::cos(radians) * deltaTime;
    position.y += velocity * std::sin(radians) * deltaTime;
    sprite.setPosition(getPosition());
    sprite.setRotation(direction);
}

void    AProjectile::updateCollisions()
{
    for (auto& box: m_pGame->getBoundingBoxes())
    {
        if (collidesWith(box))
        {
            disarm();
            return();
        }
    }
    for (auto& vampire: m_pGame->getVampies())
    {
        if (collidesWith(vampire))
        {
            damage(vampire);
            explode();
            return();
        }
    }
}

void    AProjectile::explode()
{
    m_collisionEffect->initialize();
    m_collisionEffect->setString(explosion);
    state = DYING;
}

void    AProjectile::damage(Vampire* pOther)
{
    pOther->setIsKilled();
}

void    AProjectile::dying(float deltaTime)
{
    death_rattle -= deltaTime;
    if (death_rattle <= 0.0f)
        deactivate();
}

void    AProjectile::setFlying()
{
    if (state == SPAWNING)
        state = FLYING;
}

void    AProjectile::disarm()
{
    m_collisionEffect->initialize();
    m_collisionEffect->setString(disarming);
    state = DYING;
}