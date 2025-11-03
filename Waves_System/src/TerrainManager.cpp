#include "TerrainManager.h"

TerrainManager::TerrainManager(Game* pGame)
    : m_pGame(pGame)
{}

TerrainManager::~TerrainManager()
{
    for(auto& terrain: pool)
        terrain->deactivate();
}

bool TerrainManager::initialise()
{
    texture.loadFromFile(ResourceManager::getFilePath("square_whole.png"));
    pool.reserve(maxPoolSize);
    for (size_t i = 0; i < maxPoolSize; i++)
    {
        pool.emplace_back(std::make_unique<Terrain>(m_pGame, &texture));
    }
    return true;
}

void TerrainManager::update(float deltaTime)
{
    for (auto& Terrain: pool)
    {   
        Terrain->update(deltaTime);
    }
}

void TerrainManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto& Terrain: pool)
        Terrain->draw(target, states);    
}

void TerrainManager::spawn(sf::Vector2f a_position, float a_lifetime, float a_speed, float a_angle)
{
   size_t Terrain = getUseableTerrain();
   if (pool[Terrain]->getState() != INVIS)
        pool[Terrain]->deactivate();
    pool[Terrain]->activate(a_position, a_lifetime, a_speed, a_angle);
}

size_t TerrainManager::getUseableTerrain()
{
    size_t block = 0;
    float currentLifeTime = 0.0f;
    float shortestLifeTime = std::numeric_limits<float>::max();
    for (size_t i = 0; i < pool.size(); i++)
    {
        if (pool[i]->getState() == INVIS)
        {
            block = i;
            return (block);
        }
        currentLifeTime = pool[i]->getLifetime();
        if (currentLifeTime < shortestLifeTime)
        {
            shortestLifeTime = currentLifeTime;
            block = i;
        }
    }
    return (block);
}