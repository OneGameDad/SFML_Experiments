#pragma once

#include <memory>
#include <cmath>
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Rectangle.h"
#include "Game.h"
#include "Player.h"
#include "CollectibleTextBox.h"
#include "Constants.h"

class Player;
class CollectibleTextBox;

class ACollectible: public Rectangle
{
protected:
    Game*   m_pGame;
    float   lifetime = 0.0f;
    e_coll_states state = WAITING;
    e_coll_types kind = ENERGIZING;

    sf::Vector2f startPos = {0.0f, 0.0f};

    std::unique_ptr<CollectibleTextBox> m_collectedEffect;
    std::string collectionStr = "*PLUCK*";
    const float pluckDuration = 2.0f;

    e_collidable collidable_type = COLLECTIBLE;
    
    void    beCollected(Player* pOther);
    void    reset();
    void    updateCollisions();
    void    setupTextBox();

public:
    ACollectible(Game* pGame, sf::Texture *a_texture);
    ~ACollectible();

    void    update(float deltaTime);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void    activate(sf::Vector2f a_posiition, float a_lifetime, e_coll_types a_kind);
    void    deactivate();
    e_coll_states    getState() const { return (state); }
    float   getLifetime() const { return (lifetime); }
    sf::Sprite getSprite() const { return (m_sprite); }
};