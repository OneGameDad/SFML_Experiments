#include "PlayerHealthBar.hpp"

PlayerHealthBar::PlayerHealthBar(Game *pGame)
    : m_pGame(pGame), m_pPlayer(m_pGame->getPlayer())
{}

PlayerHealthBar::~PlayerHealthBar()
{}

/*These two do nothing and are not meant to be used - purely to appease the compiler*/
void    PlayerHealthBar::initialize()
{
    std::cout << "HEALTH BAR INITILIZING...\n";
//    rectangle = new sf::RectangleShape();
//    setQueryTarget(*m_pPlayer);
//    setFollowTarget(thePlayer);
//    setPosition(adjustPosition());
    this->setPosition({100.0f, 400.0f});
    //playerWidth = m_pPlayer->getSprite().getLocalBounds().width * 3.5f;
    rectangle.setSize({maxWidth, maxHeight});
    rectangle.setOrigin({0.0f, 0.0f});
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(this->getPosition());
    std::cout << "Health Bar Position: " << rectangle.getPosition().x << ", " << rectangle.getPosition().y << std::endl;
//    texture.loadFromFile("images/square_whole.png");
//    m_sprite.setTexture(texture);
//    m_sprite.setPosition(adjustPosition());
//    m_sprite.setColor(sf::Color::Red);
//    m_sprite.setScale({-30.0f, -30.0f});
//    std::cout << "Health Bar Position: " << m_sprite.getPosition().x << ", " << m_sprite.getPosition().y << std::endl;
   
}
/*
void    PlayerHealthBar::initialize(sf::Vector2f a_position)
{
    setPosition(a_position);
}

void   PlayerHealthBar::initialize(sf::Transformable& thePlayer)
{
    std::cout << "HEALTH BAR INITILIZING...\n";
    rectangle = new sf::RectangleShape();
    setQueryTarget(*m_pPlayer);
//    setFollowTarget(thePlayer);
    setPosition(m_pPlayer->getPosition());
    playerWidth = m_pPlayer->getSprite().getLocalBounds().width * 3.5f;
    rectangle->setSize({playerWidth, maxHeight});
    rectangle->setFillColor(sf::Color::Red);
    rectangle->setPosition(adjustPosition());
    std::cout << "Health Bar Position: " << getPosition().x << ", " << getPosition().y << std::endl;
}*/

sf::Vector2f PlayerHealthBar::adjustPosition()
{
    sf::Vector2f adjustedPosition = {m_pPlayer->getSprite().getPosition().x + offsetX, m_pPlayer->getSprite().getPosition().y + offsetY};
    return (adjustedPosition);
}
/*
void    PlayerHealthBar::setQueryTarget(Player& thePlayer)
{
    m_pPlayer = &thePlayer;
}
*/
void    PlayerHealthBar::update(float deltaTime)
{
    (void)deltaTime; //Todo use to animate
    float health = m_pPlayer->getNormalizedHealth();
    float currentWidth = /*playerWidth*/maxWidth * health;
    rectangle.setSize({currentWidth, maxHeight});
//    followTarget();
    //setPosition(m_pPlayer->getPosition());
    rectangle.setPosition(getPosition());
    std::cout << "Health Bar Position: " << rectangle.getPosition().x << ", " << rectangle.getPosition().y << std::endl;
//    m_sprite.setPosition(adjustPosition());
//    std::cout << "Health Bar Position: " << m_sprite.getPosition().x << ", " << m_sprite.getPosition().y << std::endl;
}

void    PlayerHealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    (void)states;
    target.draw(rectangle);
}