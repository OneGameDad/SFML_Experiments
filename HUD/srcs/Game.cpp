#include "Game.hpp"

Game::Game() :
    m_state(State::WAITING),
    m_pPlayer(std::make_unique<Player>(this)),
    m_pPlayerHealthBar(std::make_unique<PlayerHealthBar>(this))
{
    m_pGameInput = std::make_unique<GameInput>(this, m_pPlayer.get());
}

Game::~Game()
{}

bool Game::initialize()
{
    /*
        PAY ATTENTION HIVER!
            If you want to load any assets (fonts, textures) please use the pattern shown below
    */
/*
    if (!m_font.loadFromFile(ResourceManager::getFilePath("Lavigne.ttf")))
    {
        std::cerr << "Unable to load font" << std::endl;
        return false;
    }
    if (!m_vampTexture.loadFromFile(ResourceManager::getFilePath("vampire.png")))
    {
        std::cerr << "Unable to load texture" << std::endl;
        return false;
    }
    if (!m_playerTexture.loadFromFile(ResourceManager::getFilePath("player.png")))
    {
        std::cerr << "Unable to load texture" << std::endl;
        return false;
    }
*/
    resetLevel();
    return true;
}

void Game::resetLevel()
{
    m_pPlayer->initialize();
    m_pPlayerHealthBar->initialize();
}

void Game::update(float deltaTime)
{
    
    switch (m_state)
    {
        m_pPlayerHealthBar->update(deltaTime);
        case State::WAITING:
        {
            if (GameTime::getInstance().getRealTime() >= 3.f)
            {
                m_state = State::ACTIVE;
                m_pGameInput->update(deltaTime);
            }
        }
        break;
        case State::ACTIVE:
        {
            m_pGameInput->update(deltaTime);
            m_pPlayer->update(deltaTime);
        }
        break;
    }
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //  Draw texts.
/*    if (m_state == State::WAITING)
    {
        sf::Text startText;
        startText.setFont(m_font);
        startText.setString("Game Start!");
        startText.setFillColor(sf::Color::White);
        startText.setPosition(80.0f, 80.0f);
        startText.setStyle(sf::Text::Bold);
        target.draw(startText);
    }
    else
    {
        sf::Text timerText;
        timerText.setFont(m_font);
        timerText.setFillColor(sf::Color::White);
        timerText.setStyle(sf::Text::Bold);
        timerText.setString(std::to_string((int)m_pClock->getElapsedTime().asSeconds()));
        timerText.setPosition(sf::Vector2f((ScreenWidth - timerText.getLocalBounds().getSize().x) * 0.5, 20));
        target.draw(timerText);
    }
*/
    // Draw player & healthbad
    m_pPlayer->draw(target, states);
    m_pPlayerHealthBar->draw(target, states);
    

    //  Draw world.
/*    for (auto& temp : m_pVampires)
    {
        temp->draw(target, states);
    }*/
}

Player* Game::getPlayer() const 
{
    return m_pPlayer.get();
}

void Game::onKeyPressed(sf::Keyboard::Key key)
{
    m_pGameInput->onKeyPressed(key);
}

void Game::onKeyReleased(sf::Keyboard::Key key)
{
    m_pGameInput->onKeyReleased(key);
}