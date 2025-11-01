#pragma once

#include <memory>
#include <vector>
#include <limits>
#include "ACollectible.h"
#include "Game.h"

class ACollectible;
class Game;

class CollectiblesManager  : public sf::Drawable
{
private:
    Game* m_pGame;
    std::vector<std::unique_ptr<ACollectible>> pool;
    static const size_t maxPoolSize = 50;

    sf::Texture texture;

    size_t getUseableCollectible();
public:
    CollectiblesManagerGame* pGame);
    ~CollectiblesManager();

    bool initialise();
    void update(float deltaTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void spawn(sf::Vector2f a_posiition, float a_lifetime, float a_velocity, float a_direction);
};