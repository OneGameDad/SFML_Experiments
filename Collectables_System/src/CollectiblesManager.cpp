#include "CollectiblesManager.h"

CollectiblesManager::CollectiblesManager(Game* pGame)
    : m_pGame(pGame)
{}

CollectiblesManager::~CollectiblesManager()
{
    for(auto& Collectible: pool)
        Collectible->deactivate();
}

bool CollectiblesManager::initialise()
{
    texture.loadFromFile(ResourceManager::getFilePath("GlowDot.png"));
    pool.reserve(maxPoolSize);
    for (size_t i = 0; i < maxPoolSize; i++)
    {
        pool.emplace_back(std::make_unique<ACollectible>(m_pGame, &texture));
    }
    return true;
}

void CollectiblesManager::update(float deltaTime)
{
    /*TODO set the number of active Collectibles*/
    for (auto& Collectible: pool)
    {   
        Collectible->update(deltaTime);
    }
}

void CollectiblesManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto& Collectible: pool)
        Collectible->draw(target, states);    
}

void CollectiblesManager::spawn(sf::Vector2f a_position, float a_lifetime, float a_velocity, float a_direction)
{
   size_t Collectible = getUseableCollectible();
   if (pool[Collectible]->getState() != INACTIVE)
        pool[Collectible]->deactivate();
    pool[Collectible]->activate(a_position, a_lifetime, a_velocity, a_direction);
}

size_t CollectiblesManager::getUseableCollectible()
{
    size_t Collectible = 0;
    float currentLifeTime = 0.0f;
    float shortestLifeTime = std::numeric_limits<float>::max();
    for (size_t i = 0; i < pool.size(); i++)
    {
        if (pool[i]->getState() == INACTIVE)
        {
            Collectible = i;
            return (Collectible);
        }
        currentLifeTime = pool[i]->getLifetime();
        if (currentLifeTime < shortestLifeTime)
        {
            shortestLifeTime = currentLifeTime;
            Collectible = i;
        }
    }
    return (Collectible);
}