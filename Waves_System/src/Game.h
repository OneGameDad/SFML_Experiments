#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <vector>
#include <iostream>
#include "Constants.h"
#include "PlayerHealthBar.h"
#include "Camera.h"
#include "Eye.h"
#include "StoryletBox.h"
#include "StoryletReader.h"
#include "ProjectileManager.h"
#include "BoundingBox.h"
#include "CollectiblesManager.h"
#include "SlowMotion.h"
#include "EnergyBar.h"
#include "EnemyManager.h"
#include "WavesManager.h"
#include "TerrainManager.h"
#include "ResourceManager.h"
#include "InputHandler.h"
#include "Player.h"
#include "Rectangle.h"

class Player;
class Game;
class GameInput;
class PlayerHealthBar;
class Camera;
class Eye;
class StoryletBox;
class ProjectileManager;
class CollectiblesManager;
class SlowMotion;
class EnergyBar;
class WavesManager;
class EnemyManager;
class TerrainManager;

class Game : public sf::Drawable
{
public:
    
    enum class State
    {
        WAITING,
        ACTIVE,
    };
    
    Game();
    ~Game();
    
    bool initialise(sf::RenderWindow& window);
    void update(float deltaTime);
    void resetLevel();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    State getState() const { return m_state; }
    
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);

    Player* getPlayer() const;
    Camera* getCamera() const;
    sf::Texture* getPlayerTexture() { return &m_playerTexture; }
    std::vector<std::unique_ptr<sf::Texture>>* getEyeTextures() { return (&m_eyeTextures); }


    sf::Font& getFont() { return (m_font); }
    std::vector<std::unique_ptr<BoundingBox>>* getBoundingBoxes() { return (&boundingBoxes); }
    ProjectileManager& getProjectileManager() { return (*projPool); } 
    CollectiblesManager& getCollectiblesManager() { return (*collPool); }
    EnemyManager& getEnemyManager() { return (*enemyPool); }
    TerrainManager& getTerrainManager() { return (*terrPool); }
    CollectiblesManager* getCollectiblesManagerPtr() { return (collPool.get()); }
    EnemyManager* getEnemyManagerPtr() { return (enemyPool.get()); }
    TerrainManager* getTerrainManagerPtr() { return (terrPool.get()); }
    ProjectileManager* getProjectileManagerPtr() { return (projPool.get()); }
    
private:
    std::unique_ptr<Player> m_pPlayer;
    std::unique_ptr<PlayerHealthBar> m_pPlayerHealthBar;
    std::unique_ptr<EnergyBar> m_pEnergyBar;

    std::unique_ptr<Camera> m_pCamera;
    std::unique_ptr<Eye> m_pEye;

    std::unique_ptr<EnemyManager> enemyPool;

    const float boundingBoxThickness = 10.0f;
    std::vector<std::unique_ptr<BoundingBox>> boundingBoxes;

    State m_state;
    std::unique_ptr<GameInput> m_pGameInput;
    
    sf::Font m_font;
    sf::Texture m_playerTexture;
    std::vector<std::unique_ptr<sf::Texture>> m_eyeTextures;
    std::unique_ptr<StoryletBox> m_tutorial;

    std::unique_ptr<ProjectileManager> projPool;

    std::unique_ptr<CollectiblesManager> collPool;
    void    createBoundingBoxes();

    std::unique_ptr<SlowMotion> timeCtrl;

    std::unique_ptr<TerrainManager> terrPool;

    std::unique_ptr<WavesManager> wavesController;

    float elapsed = 0.0f;
};
