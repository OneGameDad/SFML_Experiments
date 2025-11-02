#include "Enemy.h"

Enemy::Enemy(Game* pGame, sf::Texture *a_texture)
    : Rectangle(sf::Vector2f{VampireWidth, VampireHeight}, startPos), m_pGame(pGame), m_collisionEffect(std::make_unique<ProjectileTextBox>(m_pGame->getFont(), this, END_EFFECT_DURATION))
{
    m_sprite.setTexture(*a_texture);
    m_sprite.setScale({2.0f, 2.0f});
    m_sprite.setColor(sf::Color::Magenta);
}

Enemy::~Enemy(){}

void    Enemy::update(float deltaTime)
{
    if (state == DISABLED)
        return;
    else if (state == INITIATING)
    {
        updateCollisions();
        setFlying();
        return;
    }
    else if (state == ENABLED)
    {
        lifetime -= deltaTime;
        updateMovement(deltaTime);
        updateCollisions();
        if (lifetime <= 0.0f)
        {
            deactivate();
        }
    }
    else if (state == DEAD)
    {
        dying(deltaTime);
    }
    else if (state == BEYOND)
        deactivate();
}


void    Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (state == INITIATING || state == ENABLED || state == BEYOND)
    {
        target.draw(m_sprite, states);   
    }
    else if (state == DEAD)
    {
        target.draw(*m_collisionEffect, states);
    }
}

void    Enemy::activate(sf::Vector2f a_position, float a_lifetime, float a_speed, float a_angle)
{
    reset();
    setPosition(a_position);
    m_sprite.setPosition(getPosition());
    lifetime = a_lifetime;
    speed = a_speed;
    angle = a_angle;
    state = INITIATING;
}

void    Enemy::deactivate()
{
    state = DISABLED;
}

void    Enemy::reset()
{
    state = DISABLED;
    lifetime = 0.0f;
    health = 0.0f;
    speed = 0.0f;
    angle = 0.0f;
    sf::Vector2f startPos = {0.0f, 0.0f};
    deathTime = AFTER_TIME;
}

void    Enemy::updateMovement(float deltaTime)
{
    float radians = angle * PI / 180.f;
    float dx = speed * std::cos(radians) * deltaTime;
    float dy = speed * std::sin(radians) * deltaTime;
    Rectangle::move(sf::Vector2f(dx, dy));
    m_sprite.setPosition(getPosition().x, getPosition().y);
    m_sprite.setRotation(angle);
}

void    Enemy::updateCollisions()
{
    for (auto& box: *m_pGame->getBoundingBoxes())
    {
        if (collidesWith(box.get()))
        {
            setBeyond();
            return;
        }
    }
    Player* pPlayer = m_pGame->getPlayer();
    if (collidesWith(pPlayer))
    {
        pPlayer->takeDamage(2);
        explode();
        m_pGame->getCamera()->addTrauma(0.25f);
        m_pGame->getCamera()->requestShake();
        return;
    }
    }
    ProjectileManager* pProjectiles = m_pGame->getProjectileManager();
    for (auto& projectile: pProjectiles->getProjectilePool())
    {
        if (collidesWith(projectile.get()))
        {
            explode();
            m_pGame->getCollectiblesManager()->spawn(getPosition(), spawnLifetime, spawnType);
        }
    }
}

void    Enemy::explode()
{
    m_collisionEffect->initialize();
    m_collisionEffect->setString(explosion);
    state = DEAD;
}

void    Enemy::dying(float deltaTime)
{
    deathTime -= deltaTime;
    if (deathTime <= 0.0f)
        deactivate();
}

void    Enemy::setFlying()
{
    if (state == INITIATING)
    {
        state = ENABLED;
    }
}

void    Enemy::setBeyond()
{
    state = BEYOND;
}