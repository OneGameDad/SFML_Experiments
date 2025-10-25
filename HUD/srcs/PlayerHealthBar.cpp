#include "PlayerHealthBar.hpp"

PlayerHealthBar::PlayerHealthBar(Game *pGame)
    : m_pGame(pGame), m_pPlayer(m_pGame->getPlayer())
{
    try
    {
        rectangle = std::make_unique<sf::RectangleShape>();
        std::cout << "Rectangle Size X: " << rectangle->getSize().x << ", Y: " << rectangle->getSize().y << std::endl;
    }
    catch (const std::bad_alloc& e)
    {
        std::cerr << "RectangleShape Allocation failed: " << e.what() << std::endl;
    }
}

PlayerHealthBar::~PlayerHealthBar()
{ 
    std::cout << "PlayerHealthBar destroyed\n";
}

void    PlayerHealthBar::initialize()
{
    std::cout << "HEALTH BAR INITILIZING...\n";
    sf::Vector2f playerPos = m_pPlayer->getPosition();
    sf::Vector2f spritePos = m_pPlayer->getSprite().getPosition();
    std::cout << "Player Position: " << playerPos.x << ", " << playerPos.y << std::endl;
    std::cout << "Sprite Position: " << spritePos.x << ", " << spritePos.y << std::endl;
    this->setPosition(adjustPosition());
    playerScale = m_pPlayer->getSprite().getScale().x;
    playerWidth = m_pPlayer->getSprite().getLocalBounds().width * playerScale;
    rectangle->setSize({playerWidth, maxHeight});
    std::cout << "Rectangle Size X: " << rectangle->getSize().x << ", Y: " << rectangle->getSize().y << std::endl;
    rectangle->setOrigin({0.0f, 0.0f});
    rectangle->setFillColor(sf::Color::Red);
    rectangle->setPosition(getPosition());
    std::cout << "Health Bar Position: " << getPosition().x << ", " << getPosition().y << std::endl; 
}

sf::Vector2f PlayerHealthBar::adjustPosition()
{
    static const float offsetX = 0.0f;
    static const float offsetY = -20.0f;
    sf::Vector2f pos = m_pPlayer->getPosition();
    sf::Vector2f adjustedPosition = {pos.x + offsetX, pos.y + offsetY};
    return (adjustedPosition);
}

void    PlayerHealthBar::update(float deltaTime)
{
    (void)deltaTime; //Todo use to animate
    std::cout << "HEALTH BAR UPDATE\n";
    float health = m_pPlayer->getNormalizedHealth();
    float currentWidth = playerWidth * health;
    
    rectangle->setSize({currentWidth, maxHeight});
    rectangle->setOrigin({0.0f, 0.f});
    
    sf::Vector2f pos = adjustPosition();
    setPosition(pos);
    rectangle->setPosition(getPosition());
    sf::Vector2f playerPos = m_pPlayer->getSprite().getPosition();
    sf::Vector2f barPos = rectangle->getPosition();
    std::cout << "Player: " << playerPos.x << "," << playerPos.y << " | Bar: " << barPos.x << "," << barPos.y << std::endl;

}

void    PlayerHealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    (void)states;
    target.draw(*rectangle);
//    std::cout << "Drawing HEALTH BAR\n";
}