#include "AProjectile.h"

AProjectile::AProjectile(Game* pGame)
    : Rectangle(sf::Vector2f{projWidth, projHeight}, startPos), m_pGame(pGame), m_collisionEffect(std::make_unique<ProjectileTextBox>(m_pGame->getFont(), this, END_EFFECT_DURATION))
{}

AProjectile::~AProjectile(){}

void    AProjectile::update(float deltaTime)
{
    if (state == INACTIVE)
        return;
    else if (state == ACTIVE)
    {
        lifetime -= deltaTime;
        uodateMovement(deltaTime);
        if (/*TODO Bounds check*/)
        {
            deactivate();
        }
        for (auto& vampire: m_pGame->getVampies())
        {
            if (collidesWith(vampire))
            {
                m_collisionEffect->initialize();
                m_collisionEffect->setString("*explosion*");
                damage(vampire);
                return();
            }
        }
        if (lifetime <= 0.0f)
        {
            deactivate();
        }
    }
    else if (state == DYING)
    {

    }
}


void    AProjectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (state == ACTIVE)
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
    isActive = true;
}

void    AProjectile::deactivate()
{
    state = INACTIVE;
}

void    AProjectile::reset()
{
    isActive = false;
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

void    AProjectile::damage(Vampire* pOther)
{
    pOther->setIsKilled();
    state = DYING;
}