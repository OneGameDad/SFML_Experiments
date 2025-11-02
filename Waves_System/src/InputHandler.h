#pragma once

#include <SFML/Window/Keyboard.hpp>
#include "SlowMotion.h"

class Player;
class Game;
class SlowMotion;

struct InputData
{
    bool m_movingUp = false;
    bool m_movingDown = false;
    bool m_movingLeft = false;
    bool m_movingRight = false;
    bool m_screenShake = false;
    bool m_googlyEye = false;
    bool m_fireProjectile = false;
    bool m_slowTime = false;
    bool m_speedTime = false;
    bool m_jumpKeyReleasedInThisFrame = false;

    bool hasInputs() { return m_movingUp || m_movingDown || m_movingLeft || m_movingRight || m_screenShake || m_googlyEye || m_fireProjectile || m_slowTime || m_speedTime || m_jumpKeyReleasedInThisFrame; }
};

class GameInput
{
public:
    GameInput(Game* pGame, Player* pPlayer, SlowMotion* pSlowMotion);
    ~GameInput();
    
    void update(float deltaTime);
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);
    
    
private:
    InputData m_inputData;
    Game* m_pGame;
    Player* m_pPlayer;
    SlowMotion * m_pSlowMotion;
};
