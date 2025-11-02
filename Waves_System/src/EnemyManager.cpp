#include "EnemyManager.h"

EnemyManager::EnemyManager(Game* pGame)
    : m_pGame(pGame)
{}

EnemyManager::~EnemyManager()
{
    for(auto& enemy: pool)
        enemy->deactivate();
}

bool EnemyManager::initialise()
{
    texture.loadFromFile(ResourceManager::getFilePath("vampire.png"));
    pool.reserve(maxPoolSize);
    for (size_t i = 0; i < maxPoolSize; i++)
    {
        pool.emplace_back(std::make_unique<Vampire>(m_pGame, &texture));
    }
    return true;
}

void EnemyManager::update(float deltaTime)
{
    /*TODO set the number of active projectiles*/
    for (auto& enemy: pool)
    {   
        enemy->update(deltaTime);
    }
}

void EnemyManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto& enemy: pool)
        enemy->draw(target, states);    
}

void EnemyManager::spawn(sf::Vector2f a_position, float a_lifetime, float a_speed, float a_angle)
{
   size_t enemy = getUseableenemy();
   if (pool[enemy]->getState() != DISABLED)
        pool[enemy]->deactivate();
    pool[enemy]->activate(a_position, a_lifetime, a_speed, a_angle);
}

size_t EnemyManager::getUseableEnemy()
{
    size_t enemy = 0;
    float currentLifeTime = 0.0f;
    float shortestLifeTime = std::numeric_limits<float>::max();
    for (size_t i = 0; i < pool.size(); i++)
    {
        if (pool[i]->getState() == INACTIVE)
        {
            enemy = i;
            return (enemy);
        }
        currentLifeTime = pool[i]->getLifetime();
        if (currentLifeTime < shortestLifeTime)
        {
            shortestLifeTime = currentLifeTime;
            enemy = i;
        }
    }
    return (enemy);
}