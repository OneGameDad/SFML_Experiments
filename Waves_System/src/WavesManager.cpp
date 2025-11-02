#include "WavesManager.h"

WavesManager::WavesManager(Game* pGame)
    : m_pGame(pGame)
{}

WavesManager::~WavesManager()
{}

bool WavesManager::initialise()
{
    m_pProjectileManager = m_pGame->getProjectileManager();
    m_pEnemyManager = m_pGame->getEnemyManager();
    //TODO get Terrain Manager
    return true;
}

void WavesManager::update(float deltaTime)
{
    /*TODO wave spawn logic*/

    m_pProjectileManager->update(deltaTime);
    m_pEnemyManager->update(deltaTime);
    //TODO add terrain manager update
}

void WavesManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    m_pProjectileManager->draw(target, states);
    m_pEnemyManager->draw(target, states);
    //TODO add terrian manager draw  
}

void WavesManager::spawnWave(sf::Vector2f a_position, float a_speed, float a_angle)
{

}