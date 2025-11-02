#include "WavesManager.h"

WavesManager::WavesManager(Game* pGame)
    : m_pGame(pGame)
{}

WavesManager::~WavesManager()
{
    m_pCollectiblesManager = nullptr;
    m_pEnemyManager = nullptr;
    m_pTerrainManager = nullptr;
}

bool WavesManager::initialise()
{
    m_pCollectiblesManager = m_pGame->getCollectiblesManagerPtr();
    m_pEnemyManager = m_pGame->getEnemyManagerPtr();
    m_pTerrainManager = m_pGame->getTerrainManagerPtr();
    return true;
}

void WavesManager::update(float deltaTime)
{
    /*TODO wave spawn logic*/

    m_pCollectiblesManager->update(deltaTime);
    m_pEnemyManager->update(deltaTime);
    m_pTerrainManager->update(deltaTime);
}

void WavesManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    m_pCollectiblesManager->draw(target, states);
    m_pEnemyManager->draw(target, states);
    m_pTerrainManager->draw(target, states);
}

void WavesManager::spawnWave(sf::Vector2f a_position, float a_speed, float a_angle)
{

}

void WavesManager::spawnTerrain()
{

}

void WavesManager::spawnEnemies()
{

}

void WavesManager::spawnCollectibles()
{

}