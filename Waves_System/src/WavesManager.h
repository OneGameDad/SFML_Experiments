#pragma once

#include <memory>
#include <vector>
#include <limits>
#include <SFML/System/Vector2.hpp>
#include "CollectiblesManager.h"
#include "EnemyManager.h"
#include "Game.h"
#include "TerrainManager.h"

class AProjectile;
class Game;
class CollectiblesManager;
class EnemyManager;
class TerrainManager;

class WavesManager  : public sf::Drawable
{
private:
    Game* m_pGame;
    CollectiblesManager* m_pCollectiblesManager = nullptr;
    EnemyManager* m_pEnemyManager = nullptr;
    TerrainManager* m_pTerrainManager = nullptr;
    float m_WavesCooldown = 0.0f;
    float m_nextWavesCooldown = 2.0f;
    size_t m_spawnCount = 0;
    float elapsed = 0.0f;

    sf::Vector2f topSpawnPos = {ScreenWidth, 50.0f + 20.0f};
    sf::Vector2f topTerrainPos = {ScreenWidth, 50.0f};
    sf::Vector2f midSpawnPos = {ScreenWidth, ScreenHeight / 2};
    sf::Vector2f midTerrainPos = {ScreenWidth, (ScreenHeight / 2) + 20.0f};
    sf::Vector2f bottomSpawnPos = {ScreenWidth, ScreenHeight + 20.0f};
    sf::Vector2f bottomTerrainPos = {ScreenWidth, ScreenHeight};

    const float fixedAngle = 90.0f;
    const float projectileSpeed = 10.0f;
    const float enemySpeed = 10.0f;
    const float terrainSpeed = 10.0f;

    void spawnTerrain();
    void spawnEnemies();
    void spawnCollectibles();
    void spawnWave(sf::Vector2f a_position, float a_speed, float a_angle);
public:
    WavesManager(Game* pGame);
    ~WavesManager();

    bool initialise();
    void update(float deltaTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
};