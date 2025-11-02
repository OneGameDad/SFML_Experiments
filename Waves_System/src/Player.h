#pragma once

#include "Rectangle.h"
#include "ResourceManager.h"
#include <memory>
#include "InputHandler.h"
#include "Constants.h"
#include <vector>
#include "Game.h"
#include "WeaponTextBox.h"
#include "Constants.h"
#include <SFML/System/Vector2.hpp>

struct InputData;

class Game;
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
    void takeDamage(float num);

    float getNormalizedHealth() const;
    void heal(float num);
    sf::Sprite getSprite() const;

    void fire();

    void addEnergy(size_t num);
    void drainEnergy();
    float getNormalizedEnergy() const;

    void jump();
private:
    bool    m_isDead = false;
    eDirection m_direction = LEFT;
    Game*   m_pGame;

    float currentHealth = 0.0f;
    const float maxHealth = 100.0f;

    bool    firedProjectile = false;
    float   fireCooldown = 3.5f;
    float   elapsed = 0.0f;
    void    updateGun(float deltaTimeUnScaled);
    
    float currentEnergy = 0.0f;
    const float maxEnergy = 10.0f;
    const float slowMotionEnergyCostPerSecond = 2.0f;

    bool onGround = true;
    const float gravity = 1500.f;
    const float maxYSpeed = 700.f;
    const float forwardSpeed = 10.0f;
    const float dropBoost = -8.0f;

    void updateCollisions();
    void setOnGround();
    void setOffGround();
};
