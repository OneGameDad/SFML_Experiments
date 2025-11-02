#pragma once

#include <memory>
#include <vector>
#include <limits>
#include "Enemy.h"
#include "Game.h"

class Enemy;
class Game;

class EnemyManager  : public sf::Drawable
{
private:
    Game* m_pGame;
    std::vector<std::unique_ptr<Enemy>> pool;
    static const size_t maxPoolSize = 50;

    sf::Texture texture;

    size_t getUseableEnemy();
public:
    EnemyManager(Game* pGame);
    ~EnemyManager();

    bool initialise();
    void update(float deltaTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void spawn(sf::Vector2f a_position, float a_lifetime, float a_velocity, float a_direction);
};