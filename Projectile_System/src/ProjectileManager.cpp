#include "ProjectileManager.h"

ProjectileManager::ProjectileManager(Game* pGame)
    : m_pGame(pGame)
{
    m_Font = m_pGame->getFont();
}

ProjectileManager::~ProjectileManager()
{
    for(auto& projectile: pool)
        projectile->deactivate();
}

bool ProjectileManager::initialise()
{
    pool->reserve(maxPoolSize);
    for (size_t i = 0; i < maxPoolSize; i++)
    {
        pool.emplace_back(std::make_unique<AProjectile>(m_Font));
    }
}

void ProjectileManager::update(float deltaTime)
{
    /*TODO set the number of active projectiles*/
    for (auto& projectile: pool)
    {   
        projectile->update(deltaTime);
    }
}

void ProjectileManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto& projectile: pool)
        projectile->draw(target, states);    
}

void launch(sf::Vector2f a_posiition, float a_lifetime, float a_velocity, float a_direction)
{
    /*
    - TODO deactive the oldest projectile
    - Activate the next available projectile
    - Update spawnCount
    */
}