#pragma once

#include <memory>
#include <vector>
#include <limits>
#include "Terrain.h"
#include "Game.h"

class Terrain;
class Game;

class TerrainManager  : public sf::Drawable
{
private:
    Game* m_pGame;
    std::vector<std::unique_ptr<Terrain>> pool;
    static const size_t maxPoolSize = 50;

    sf::Texture texture;

    size_t getUseableTerrain();
public:
    TerrainManager(Game* pGame);
    ~TerrainManager();

    bool initialise();
    void update(float deltaTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void spawn(sf::Vector2f a_position, float a_lifetime, float a_velocity, float a_direction);
    std::vector<std::unique_ptr<Terrain>>& getPool() { return (pool); }
    const std::vector<std::unique_ptr<Terrain>>& getPool() const { return (pool); }
};