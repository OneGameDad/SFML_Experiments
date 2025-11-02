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

void CollectiblesManager::spawn(sf::Vector2f a_position, float a_lifetime, e_coll_types a_kind)
{
   size_t Collectible = getUseableCollectible();
   if (pool[Collectible]->getState() != WAITING)
        pool[Collectible]->deactivate();
    pool[Collectible]->activate(a_position, a_lifetime, a_kind);
}

size_t CollectiblesManager::getUseableCollectible()
{
    size_t Collectible = 0;
    float currentLifeTime = 0.0f;
    float shortestLifeTime = std::numeric_limits<float>::max();
    for (size_t i = 0; i < pool.size(); i++)
    {
        if (pool[i]->getState() == WAITING)
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