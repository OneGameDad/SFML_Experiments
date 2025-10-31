#include "AProjectile.h"

AProjectile::AProjectile(Game* pGame, sf::Texture *a_texture)
    : Rectangle(sf::Vector2f{10.0f, 10.0f}, startPos), m_pGame(pGame), m_collisionEffect(std::make_unique<ProjectileTextBox>(m_pGame->getFont(), this, END_EFFECT_DURATION))
{
    m_sprite.setTexture(*a_texture);
    m_sprite.setScale({0.025f, 0.025f});
//    auto textureSize = m_sprite.getTexture()->getSize();
//    sf::Vector2f size (static_cast<float>(textureSize.x), static_cast<float>(textureSize.y));
//    setSize(size);
    m_sprite.setColor(sf::Color::Magenta);
}

AProjectile::~AProjectile(){}

void    AProjectile::update(float deltaTime)
{
    if (state == INACTIVE)
        return;
    else if (state == SPAWNING)
    {
        updateCollisions();
        setFlying();
        return;
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
        target.draw(m_sprite, states);   
    }
    else if (state == DYING)
    {
        target.draw(*m_collisionEffect, states);
    }
}

void    AProjectile::activate(sf::Vector2f a_position, float a_lifetime, float a_velocity, float a_direction)
{
    reset();
    setPosition(a_position);
    m_sprite.setPosition(getPosition());
    lifetime = a_lifetime;
    velocity = a_velocity;
    direction = a_direction;
    state = SPAWNING;
    std::cout << "Projectile Spawned at: " << getPosition().x << ", " << getPosition().y << std::endl;
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
    death_rattle = DYING_TIME;
}

void    AProjectile::updateMovement(float deltaTime)
{
    std::cout << "Velocity: " << velocity << std::endl;
    float radians = direction * PI / 180.f;
    float dx = velocity * std::cos(radians) * deltaTime;
    float dy = velocity * std::sin(radians) * deltaTime;
    std::cout << "DX: " << dx << " DY: " << dy << std::endl;
    Rectangle::move(sf::Vector2f(dx, dy));
    m_sprite.setPosition(getPosition().x, getPosition().y);
    //m_sprite.move(dx, dy);  // moves relative to current position
    m_sprite.setRotation(direction);

    //std::cout << "Projectile Pos: " << getPosition().x << ", " << getPosition().y << std::endl;
}

void    AProjectile::updateCollisions()
{
    for (auto& box: *m_pGame->getBoundingBoxes())
    {
        if (collidesWith(box.get()))
        {
            disarm();
            return;
        }
    }
    for (auto& vampire: *m_pGame->getVampies())
    {
        if (collidesWith(vampire.get()))
        {
            damage(vampire.get());
            explode();
            m_pGame->getCamera()->addTrauma(0.5f);
            m_pGame->getCamera()->requestShake();
            return;
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
    pOther->setIsKilled(true);
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
    {
        state = FLYING;
        std::cout << "PROJECTILE FLYING\n";
    }
}

void    AProjectile::disarm()
{
    std::cout << "PROJECTILE DISARMING\n";
    m_collisionEffect->initialize();
    m_collisionEffect->setString(disarming);
    state = DYING;
}