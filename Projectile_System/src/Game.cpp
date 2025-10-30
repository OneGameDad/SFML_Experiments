#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "ResourceManager.h"
#include "InputHandler.h"
#include "Weapon.h"
#include "Player.h"
#include "Rectangle.h"
#include "Vampire.h"

Game::Game() :
    m_state(State::WAITING),
    m_pPlayer(std::make_unique<Player>(this, getFont())),
    m_pPlayerHealthBar(std::make_unique<PlayerHealthBar>(this)),
    m_pCamera(std::make_unique<Camera>(this)),
    m_pEye(std::make_unique<Eye>(this)),
    m_vampireCooldown(2.0f),
    m_nextVampireCooldown(2.0f),
    projPool(std::make_unique<ProjectileManager>(this));
{
    m_pGameInput = std::make_unique<GameInput>(this, m_pPlayer.get(), m_pCamera.get(), m_pEye.get());
}

Game::~Game(){}

bool Game::initialise(sf::RenderWindow& window)
{
    /*
        PAY ATTENTION HIVER!
            If you want to load any assets (fonts, textures) please use the pattern shown below
    */

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
    for (const std::string& filename : { "googly-a.png", "googly-b.png", "googly-c.png", "googly-d.png", "googly-e.png" })
    {
        auto tex = std::make_unique<sf::Texture>();
        if (tex->loadFromFile(ResourceManager::getFilePath(filename))) {
            m_eyeTextures.push_back(std::move(tex));
        } else {
            std::cerr << "Failed to load " << filename << "\n";
        }
    }
    
    //My Code
    m_pCamera->initialize(window);
    createBoundingBoxes();
    m_tutorial = std::make_unique<StoryletBox>(m_font, StoryletReader::getInstance().getValue("ID_WAIT"));
    resetLevel();
    return true;
}

void Game::createBoundingBoxes()
{
    boundingBoxes.reserve(4);
    boundingBoxes.emplace_back(std::make_unique<Rectangle>({ScreenWidth, boundingBoxThickness}, {0.0f, 0.0f}));
    boundingBoxes.emplace_back(std::make_unique<Rectangle>({boundingBoxThickness, ScreenHeight}, {0.0f, 0.0f}));
    boundingBoxes.emplace_back(std::make_unique<Rectangle>({boundingBoxThickness, ScreenHeight}, {ScreenWidth - boundingBoxThickness, 0.0f}));
    boundingBoxes.emplace_back(std::make_unique<Rectangle>({ScreenWidth, boundingBoxThickness}, {0.0f, ScreenHeight - boundingBoxThickness}));
}

void Game::resetLevel()
{
    m_pVampires.clear();

    m_pPlayer->initialise();
    m_pPlayerHealthBar->initialize();

    m_pEye->initialize();
    m_tutorial->initialize({300.0f, 100.0f}, 24);
    projPool->initialise();
}

void Game::update(float deltaTime)
{
    switch (m_state)
    {
        case State::WAITING:
        {
            elapsed += deltaTime;
            if (elapsed >= 3.f)
            {
                m_state = State::ACTIVE;
                m_tutorial->update(StoryletReader::getInstance().getValue("ID_PLAY"));
                elapsed = 0.0f;
            }
        }
        break;
            
        case State::ACTIVE:
        {
            m_pGameInput->update(deltaTime);
            m_pPlayer->update(deltaTime);
            m_pPlayerHealthBar->update(deltaTime);
            m_pCamera->update();
            m_pEye->update();

            vampireSpawner(deltaTime);
            for (auto& temp : m_pVampires)
            {
                temp->update(deltaTime);
            }

            if (m_pPlayer->isDead())
            {
                m_state = State::WAITING;
                m_tutorial->update(StoryletReader::getInstance().getValue("ID_WAIT"));
                resetLevel();
            }
        }
        break;
    }

    int i = 0;
    while (i < m_pVampires.size())
    {
        if (m_pVampires[i]->isKilled())
        {
            std::swap(m_pVampires[i], m_pVampires.back());
            m_pVampires.pop_back();
            continue;
        }
        i++;
    }
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //Draw Storylet
    m_tutorial->draw(target, states);
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
        timerText.setString(std::to_string((int)GameTime::getInstance().getDeltaTime()));
        timerText.setPosition(sf::Vector2f((ScreenWidth - timerText.getLocalBounds().getSize().x) * 0.5, 20));
        target.draw(timerText);
    }
*/    
    // Draw player.
    m_pPlayer->draw(target, states);

    //  Draw world.
    for (auto& temp : m_pVampires)
    {
        temp->draw(target, states);
    }

    //Player Health Bar
    m_pPlayerHealthBar->draw(target, states);

    //Googly Eye
    m_pEye->draw(target, states);

    
}


void Game::onKeyPressed(sf::Keyboard::Key key)
{
    m_pGameInput->onKeyPressed(key);
}

void Game::onKeyReleased(sf::Keyboard::Key key)
{
    m_pGameInput->onKeyReleased(key);
}

Player* Game::getPlayer() const 
{
    return m_pPlayer.get();
}

Camera* Game::getCamera() const
{
    return (m_pCamera.get());
}

void Game::vampireSpawner(float deltaTime)
{
    if (m_vampireCooldown > 0.0f)
    {
        m_vampireCooldown -= deltaTime;
        return;
    }

    float randomXPos = rand() % ScreenWidth;
    float randomYPos = rand() % ScreenHeight;

    float distToRight = (float) ScreenWidth - randomXPos;
    float distToBottom = (float) ScreenHeight - randomYPos;

    float xMinDist = randomXPos < distToRight ? -randomXPos : distToRight;
    float yMinDist = randomYPos < distToBottom ? -randomYPos : distToBottom;

    if (abs(xMinDist) < abs(yMinDist))
        randomXPos += xMinDist;
    else
        randomYPos += yMinDist;

    sf::Vector2f spawnPosition = sf::Vector2f(randomXPos, randomYPos);
    m_pVampires.push_back(std::make_unique<Vampire>(this, spawnPosition));

    m_spawnCount++;
    if (m_spawnCount % 5 == 0)
    {
        m_nextVampireCooldown -= 0.1f;
    }
    m_vampireCooldown = m_nextVampireCooldown;
}