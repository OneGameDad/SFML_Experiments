#include "InputHandler.h"
#include "Weapon.h"
#include "Player.h"
#include "Eye.h"

GameInput::GameInput(Game* pGame, Player* pPlayer, Camera* pCamera, Eye* pEye, SlowMotion* pSlowMotion) :
    m_pGame(pGame), m_pPlayer(pPlayer), m_pCamera(pCamera), m_pEye(pEye), m_pSlowMotion(pSlowMotion)
{}

GameInput::~GameInput(){}

void GameInput::update(float deltaTime)
{
    if (m_inputData.hasInputs())
    {
        m_pPlayer->move(m_inputData, deltaTime);
    }

    if (m_inputData.m_space)
    {
        m_pPlayer->attack();
    }

    if (m_inputData.m_screenShake)
    {
        m_pCamera->requestShake();
    }

    if (m_inputData.m_googlyEye)
    {
        m_pEye->requestGoogly();
    }
    
    if (m_inputData.m_fireProjectile)
    {
        m_pPlayer->fire();
    }
    
    if (m_inputData.m_slowTime)
    {
        m_pSlowMotion->activate();
    }

    if (m_inputData.m_speedTime)
    {
        m_pSlowMotion->deactivate();
    }
}

void GameInput::onKeyPressed(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
    {
        m_inputData.m_movingUp = true;
    }
    else if (key == sf::Keyboard::Down)
    {
        m_inputData.m_movingDown = true;
    }
    else if (key == sf::Keyboard::Left)
    {
        m_inputData.m_movingLeft = true;
    }
    else if (key == sf::Keyboard::Right)
    {
        m_inputData.m_movingRight = true;
    }
    else if (key == sf::Keyboard::Space)
    {
        if (m_inputData.m_spaceReleased)
        {
            m_inputData.m_space = true;
        }
        m_inputData.m_spaceReleased = false;
    }
    else if (key == sf::Keyboard::Enter)
    {
        m_inputData.m_screenShake = true;
    }
    else if (key == sf::Keyboard::Tab)
    {
        m_inputData.m_googlyEye = true;
    }
    else if (key == sf::Keyboard::G)
    {
        m_inputData.m_fireProjectile = true;
    }
    else if (key == sf::Keyboard::C)
    {
        m_inputData.m_slowTime = true;
    }
    else if (key == sf::Keyboard::V)
    {
        m_inputData.m_speedTime = true;
    }
}

void GameInput::onKeyReleased(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
    {
        m_inputData.m_movingUp = false;
    }
    else if (key == sf::Keyboard::Down)
    {
        m_inputData.m_movingDown = false;
    }
    else if (key == sf::Keyboard::Left)
    {
        m_inputData.m_movingLeft = false;
    }
    else if (key == sf::Keyboard::Right)
    {
        m_inputData.m_movingRight = false;
    }
    else if (key == sf::Keyboard::Space)
    {
        m_inputData.m_space = false;
        m_inputData.m_spaceReleased = true;
    }
    else if (key == sf::Keyboard::Enter)
    {
        m_inputData.m_screenShake = false;
    }
    else if (key == sf::Keyboard::Tab)
    {
        m_inputData.m_googlyEye = false;
    }
    else if (key == sf::Keyboard::G)
    {
        m_inputData.m_fireProjectile = false;
    }
    else if (key == sf::Keyboard::C)
    {
        m_inputData.m_slowTime = false;
    }
    else if (key == sf::Keyboard::V)
    {
        m_inputData.m_speedTime = false;
    }
}
