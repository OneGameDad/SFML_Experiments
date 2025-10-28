#pragma once

#include "Rectangle.h"
#include "ResourceManager.h"
#include "ParticleSystem.h"
#include "FireEffect.h"
#include <memory>
#include "Weapon.h"
#include "InputHandler.h"
#include "Constants.h"
#include <vector>
#include "Game.h"
#include "WeaponTextBox.h"
#include "Constants.h"

struct InputData;

class Game;
class Weapon;
class WeaponTextBox;

enum eDirection
{
    LEFT,
    RIGHT
};

class Player : public Rectangle
{
public:
    Player(Game* pGame, sf::Font& pFont);
    virtual ~Player();
    
    bool initialise();
    void move(InputData inputData, float deltaTime);
    void attack();
    void update(float deltaTime);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool isDead() const { return m_isDead; }
    void setIsDead(bool isDead) { m_isDead = isDead; }

    Weapon* getWeapon() { return m_pWeapon.get(); }

    float getNormalizedHealth() const;
    sf::Sprite getSprite() const;

private:
    bool    m_isDead = false;
    eDirection m_direction = LEFT;
    Game*   m_pGame;
    std::unique_ptr<Weapon> m_pWeapon;
    std::unique_ptr<WeaponTextBox> m_pWeaponEffect;

    float currentHealth = 0.0f;
    const float maxHealth = 100.0f;
};
