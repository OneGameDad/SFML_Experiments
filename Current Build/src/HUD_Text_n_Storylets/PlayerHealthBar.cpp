#include "PlayerHealthBar.h"

PlayerHealthBar::PlayerHealthBar(Game *pGame)
    : m_pGame(pGame), m_pPlayer(m_pGame->getPlayer())
{
    try
    {
        rectangle = std::make_unique<sf::RectangleShape>();
    }
    catch (const std::bad_alloc& e)
    {
        std::cerr << "RectangleShape Allocation failed: " << e.what() << std::endl;
    }
}

PlayerHealthBar::~PlayerHealthBar(){}

void    PlayerHealthBar::initialize()
{
    sf::Vector2f playerPos = m_pPlayer->getPosition();
    sf::Vector2f spritePos = m_pPlayer->getSprite().getPosition();
    this->setPosition(adjustPosition());
    playerScale = m_pPlayer->getSprite().getScale().x;
    playerWidth = m_pPlayer->getSprite().getLocalBounds().width * playerScale;
    rectangle->setSize({playerWidth, maxHeight});
    rectangle->setOrigin({0.0f, 0.0f});
    rectangle->setFillColor(sf::Color::Red);
    rectangle->setPosition(getPosition());
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
    float health = m_pPlayer->getNormalizedHealth();
    float currentWidth = playerWidth * health;
    
    rectangle->setSize({currentWidth, maxHeight});
    rectangle->setOrigin({0.0f, 0.f});
    
    sf::Vector2f pos = adjustPosition();
    setPosition(pos);
    rectangle->setPosition(getPosition());
    sf::Vector2f playerPos = m_pPlayer->getSprite().getPosition();
    sf::Vector2f barPos = rectangle->getPosition();
}

void    PlayerHealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    (void)states;
    target.draw(*rectangle);
}