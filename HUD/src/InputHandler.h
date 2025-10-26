#pragma once

#include <SFML/Window/Keyboard.hpp>
#include "Camera.h"
#include "Eye.h"

class Player;
class Game;
class Camera;
class Eye;

struct InputData
{
    bool m_movingUp = false;
    bool m_movingDown = false;
    bool m_movingLeft = false;
    bool m_movingRight = false;
    bool m_space = false;
    bool m_spaceReleased = true;
    bool m_screenShake = false;
    bool m_googlyEye = false;

    bool hasInputs() { return m_movingUp || m_movingDown || m_movingLeft || m_movingRight || m_space || m_screenShake || m_googlyEye; }
};

class GameInput
{
public:
    GameInput(Game* pGame, Player* pPlayer, Camera* pCamera, Eye* pEye);
    ~GameInput();
    
    void update(float deltaTime);
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);
    
    
private:
    InputData m_inputData;
    Game* m_pGame;
    Player* m_pPlayer;
    Camera* m_pCamera;
    Eye* m_pEye;
};
