#pragma once

/*Based on the Player Class from 2024's Supercell Challenge*/
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Game.hpp"

class Game;

class Player
{
private:
    Game*   m_pGame;
    sf::RectangleShape body;
    sf::Vector2f position;

public:
    Player();
    Player(Game* pGame);
    ~Player() = default;
    
    bool initialize();
//    void move(InputData inputData, float deltaTime);
//    void attack();
    void update(float deltaTime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

//    bool isDead() const { return m_isDead; }
//    void setIsDead(bool isDead) { m_isDead = isDead; }

//    Weapon* getWeapon() { return m_pWeapon.get(); }
};
