#pragma once

/*Based on the Player Class from 2024's Supercell Challenge*/
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "Game.hpp"
#include "Rectangle.hpp"
#include <iostream>

struct InputData;

class Game;

const float PlayerSpeed = 155.0f;

class Player: public Rectangle
{
private:
    Game*   m_pGame;
    sf::Texture texture;
    float currentHealth = 0.0f;
    const float maxHealth = 100.0f;

public:
    Player(Game* pGame);
    ~Player() = default;
    
    bool initialize();
    void move(InputData inputData, float deltaTime);
//    void attack();
    void update(float deltaTime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    float getNormalizedHealth() const;
    sf::Sprite getSprite() const;

//    bool isDead() const { return m_isDead; }
//    void setIsDead(bool isDead) { m_isDead = isDead; }

//    Weapon* getWeapon() { return m_pWeapon.get(); }
};
