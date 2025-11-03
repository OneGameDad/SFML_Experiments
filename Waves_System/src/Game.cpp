#include "Game.h"



Game::Game() :
    m_state(State::WAITING),
    m_pPlayer(std::make_unique<Player>(this, getFont())),
    m_pPlayerHealthBar(std::make_unique<PlayerHealthBar>(this)),
    m_pEnergyBar(std::make_unique<EnergyBar>(this)),
    m_pCamera(std::make_unique<Camera>(this)),
    m_pEye(std::make_unique<Eye>(this)),
    enemyPool(std::make_unique<EnemyManager>(this)),
    projPool(std::make_unique<ProjectileManager>(this)),
    collPool(std::make_unique<CollectiblesManager>(this)),
    timeCtrl(std::make_unique<SlowMotion>(this)),
    terrPool(std::make_unique<TerrainManager>(this)),
    wavesController(std::make_unique<WavesManager>(this))
{
    m_pGameInput = std::make_unique<GameInput>(this, m_pPlayer.get(), timeCtrl.get());    
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
    boundingBoxes.emplace_back(std::make_unique<BoundingBox>(sf::Vector2f {ScreenWidth, boundingBoxThickness}, sf::Vector2f {0.0f, 0.0f}));
    boundingBoxes.emplace_back(std::make_unique<BoundingBox>(sf::Vector2f {boundingBoxThickness, ScreenHeight}, sf::Vector2f {0.0f, 0.0f}));
    boundingBoxes.emplace_back(std::make_unique<BoundingBox>(sf::Vector2f {boundingBoxThickness, ScreenHeight}, sf::Vector2f {ScreenWidth - boundingBoxThickness, 0.0f}));
    boundingBoxes.emplace_back(std::make_unique<BoundingBox>(sf::Vector2f {ScreenWidth, boundingBoxThickness}, sf::Vector2f {0.0f, ScreenHeight - boundingBoxThickness}));
}

void Game::resetLevel()
{
    GameTime::getInstance().restart();

    m_pPlayer->initialise();
    m_pPlayerHealthBar->initialize();
    m_pEnergyBar->initialize();

    m_pEye->initialize();
    m_tutorial->initialize({300.0f, 100.0f}, 24);
    projPool->initialise();
    collPool->initialise();
    enemyPool->initialise();
    terrPool->initialise();
    wavesController->initialise();
    
    terrPool->spawn({ScreenWidth / 2, ScreenHeight + 50}, 100.0f, 0.0f, 0.0f);
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
            m_pGameInput->update(GameTime::getInstance().getDeltaTimeUnscaled());
            m_pPlayer->update(GameTime::getInstance().getDeltaTimeUnscaled());
            m_pPlayerHealthBar->update(GameTime::getInstance().getDeltaTimeUnscaled());
            m_pEnergyBar->update(GameTime::getInstance().getDeltaTimeUnscaled());
            m_pCamera->update();
            m_pEye->update();

            timeCtrl->update(); //Uses the GameTime internally
            
            wavesController->update(deltaTime); // Controls Enemies, projectiles & terrain

            if (m_pPlayer->isDead())
            {
                m_state = State::WAITING;
                m_tutorial->update(StoryletReader::getInstance().getValue("ID_WAIT"));
                resetLevel();
            }
        }
        break;
    }
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //Draw Storylet
    m_tutorial->draw(target, states);
   
    // Draw player.
    m_pPlayer->draw(target, states);

    //  Draw world.
    wavesController->draw(target, states);

    //Draw collectibles
    collPool->draw(target, states);

    //Player Health & Energy Bar
    m_pPlayerHealthBar->draw(target, states);
    m_pEnergyBar->draw(target, states);

    //Googly Eye
    m_pEye->draw(target, states);

    for (auto& box: boundingBoxes)
    {
        box->draw(target, states);
    }
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