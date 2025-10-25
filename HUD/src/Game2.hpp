#pragma once

/*Based on the Game Class from 2024's Supercell Challenge*/

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include "Player.hpp"
#include "GameTime.hpp"
#include "PlayerHealthBar.hpp"
#include "InputHandler.hpp"

class Player;
class PlayerHealthBar;
class GameInput;

const int ScreenWidth = 800;
const int ScreenHeight = 600;

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
    
    bool initialize();
    void update(float deltaTime);
    void resetLevel();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    State getState() const { return m_state; }

    Player* getPlayer() const;

    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);

private:
    State m_state;
    std::unique_ptr<Player> m_pPlayer;
    std::unique_ptr<PlayerHealthBar> m_pPlayerHealthBar;
    std::unique_ptr<GameInput> m_pGameInput;
    
};
