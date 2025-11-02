#pragma once

#include <memory>
#include <vector>
#include <limits>
#include <SFML/System/Vector2.hpp>
#include "Projectilemanager.h"
#include "EnemyManager.h"
#include "Game.h"

class AProjectile;
class Game;

class WavesManager  : public sf::Drawable
{
private:
    Game* m_pGame;
    std::vector<std::unique_ptr<ProjectileManager>>* m_pProjectileManager;
    std::vector<std::unique_ptr<EnemyManager>>* m_pEnemyManager;
//    std::vector<std::unique_ptr</*TODO*/>>* m_pTerrainManager;
    float m_WavesCooldown = 0.0f;
    float m_nextWavesCooldown = 2.0f;
    size_t m_spawnCount = 0;
    float elapsed = 0.0f;

    sf::Vector2f topSpawnPos = {ScreenWidth, 0.0f};
    sf::Vector2f midSpawnPos = {ScreenWidth, ScreenHeight / 2};
    sf::Vector2f bottomSpawnPos = {ScreenWidth, ScreenHeight};

    const float fixedAngle = 90.0f;
    const float projectileSpeed = 10.0f;
    const float enemySpeed = 10.0f;
    const float terrainSpeed = 10.0f;

    void spawnWave(sf::Vector2f a_position, float a_speed, float a_angle);
public:
    WavesManager(Game* pGame);
    ~WavesManager();

    bool initialise();
    void update(float deltaTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
};