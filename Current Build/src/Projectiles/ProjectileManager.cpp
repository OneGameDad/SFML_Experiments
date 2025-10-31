#include "ProjectileManager.h"

ProjectileManager::ProjectileManager(Game* pGame)
    : m_pGame(pGame)
{}

ProjectileManager::~ProjectileManager()
{
    for(auto& projectile: pool)
        projectile->deactivate();
}

bool ProjectileManager::initialise()
{
    texture.loadFromFile(ResourceManager::getFilePath("square_whole.png"));
    pool.reserve(maxPoolSize);
    for (size_t i = 0; i < maxPoolSize; i++)
    {
        pool.emplace_back(std::make_unique<AProjectile>(m_pGame, &texture));
    }
    return true;
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

void ProjectileManager::spawn(sf::Vector2f a_position, float a_lifetime, float a_velocity, float a_direction)
{
   size_t projectile = getUseableProjectile();
   if (pool[projectile]->getState() != INACTIVE)
        pool[projectile]->deactivate();
    pool[projectile]->activate(a_position, a_lifetime, a_velocity, a_direction);
}

size_t ProjectileManager::getUseableProjectile()
{
    size_t projectile = 0;
    float currentLifeTime = 0.0f;
    float shortestLifeTime = std::numeric_limits<float>::max();
    for (size_t i = 0; i < pool.size(); i++)
    {
        if (pool[i]->getState() == INACTIVE)
        {
            projectile = i;
            return (projectile);
        }
        currentLifeTime = pool[i]->getLifetime();
        if (currentLifeTime < shortestLifeTime)
        {
            shortestLifeTime = currentLifeTime;
            projectile = i;
        }
    }
    return (projectile);
}