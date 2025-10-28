#include "ProjectilePool.h"

ProjectilePool::ProjectilePool(Game* pGame)
    : m_pGame(pGame)
{
    m_Font = m_pGame->getFont();
}

ProjectilePool::~ProjectilePool(){}

bool ProjectilePool::initialise()
{
    //TODO reserve size for vector, and create Projectiles in in-active state
    m_pProjectiles->reserve(maxPoolSize);
    for (size_t i = 0; i < maxPoolSize; i++)
    {
        m_pProjectiles.emplace_back(std::make_unique<AProjectile>(m_Font));
    }
}

void ProjectilePool::update(float deltaTime)
{
    for (auto& projectile: m_pProjectiles)
        projectile->update(deltaTime);
}

void ProjectilePool::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auot& projectile: m_pProjectiles)
        projectile->draw(target, states);    
}