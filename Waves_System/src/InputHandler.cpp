#include "InputHandler.h"
#include "Weapon.h"
#include "Player.h"
#include "Eye.h"

GameInput::GameInput(Game* pGame, Player* pPlayer, SlowMotion* pSlowMotion) :
    m_pGame(pGame), m_pPlayer(pPlayer), m_pSlowMotion(pSlowMotion)
{}

GameInput::~GameInput(){}

void GameInput::update(float deltaTime)
{
    if (m_inputData.hasInputs())
    {
        m_pPlayer->move(m_inputData, deltaTime);
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
    switch (key)
    {
        case sf::Keyboard::Down:
        {
            m_inputData.m_movingDown = true;
            break;
        }
        case sf::Keyboard::G:
        {
            m_inputData.m_fireProjectile = true;
            break;
        }
        case sf::Keyboard::C:
        {
            m_inputData.m_slowTime = true;
            break;
        }
        case sf::Keyboard::V:
        {
            m_inputData.m_speedTime = true;
            break;
        }
        case sf::Keyboard::Space:
        {
            m_inputData.m_jumpKeyReleasedInThisFrame = false;
            break;
        }
        default:
            break;
    }
}

void GameInput::onKeyReleased(sf::Keyboard::Key key)
{
    switch (key)
    {
        case sf::Keyboard::Down:
        {
            m_inputData.m_movingDown = false;
            break;
        }
        case sf::Keyboard::G:
        {
            m_inputData.m_fireProjectile = false;
            break;
        }
        case sf::Keyboard::C:
        {
            m_inputData.m_slowTime = false;
            break;
        }
        case sf::Keyboard::V:
        {
            m_inputData.m_speedTime = false;
            break;
        }
        case sf::Keyboard::Space:
        {
            m_inputData.m_jumpKeyReleasedInThisFrame = true;
            break;
        }
        default:
            break;
    }
}
