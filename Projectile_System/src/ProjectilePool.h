#pragma once

#include <memory>
#include <vector>
#include "AProjectile.h"
#include "Game.h"

class AProjectile;
class Game;

class ProjectilePool  : public sf::Drawable
{
private:
    Game* m_pGame;
    std::vector<std::unique_ptr<AProjectile>> m_pProjectiles;
    float m_projectileCooldown = 0.0f;
    float m_nextProjectileCooldown = 2.0f;
    size_t m_spawnCount = 0;
    float elapsed = 0.0f;
    static const size_t maxPoolSize = 50;

public:
    ProjectilePool(Game* pGame);
    ~ProjectilePool();

    bool initialise();
    void update(float deltaTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

};