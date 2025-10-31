#pragma once

#include <memory>
#include <vector>
#include <limits>
#include "AProjectile.h"
#include "Game.h"

class AProjectile;
class Game;

class ProjectileManager  : public sf::Drawable
{
private:
    Game* m_pGame;
    std::vector<std::unique_ptr<AProjectile>> pool;
    float m_projectileCooldown = 0.0f;
    float m_nextProjectileCooldown = 2.0f;
    size_t m_spawnCount = 0;
    float elapsed = 0.0f;
    static const size_t maxPoolSize = 50;

    sf::Texture texture;

    size_t getUseableProjectile();
public:
    ProjectileManager(Game* pGame);
    ~ProjectileManager();

    bool initialise();
    void update(float deltaTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void spawn(sf::Vector2f a_posiition, float a_lifetime, float a_velocity, float a_direction);
};