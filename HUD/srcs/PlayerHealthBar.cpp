#include "PlayerHealthBar.hpp"

PlayerHealthBar::PlayerHealthBar(Game *pGame)
    : m_pGame(pGame), m_pPlayer(m_pGame->getPlayer())
{}

PlayerHealthBar::~PlayerHealthBar()
{
    delete rectangle;
}

/*These two do nothing and are not meant to be used - purely to appease the compiler*/
void    PlayerHealthBar::initialize()
{
    setPosition(m_pPlayer->getPosition());
   
}
void    PlayerHealthBar::initialize(sf::Vector2f a_position)
{
    setPosition(a_position);
}

void   PlayerHealthBar::initialize(sf::Transformable& thePlayer)
{
    rectangle = new sf::RectangleShape();
    setQueryTarget(*m_pPlayer);
    setFollowTarget(thePlayer);
    setPosition(m_pPlayer->getPosition());
    rectangle->setSize({maxWidth, maxHeight});
    rectangle->setFillColor(sf::Color::Red);
    rectangle->setPosition(getTargetPositionAdjusted());
    std::cout << "Health Bar Position: " << getPosition().x << ", " << getPosition().y << std::endl;
}

void    PlayerHealthBar::setQueryTarget(Player& thePlayer)
{
    m_pPlayer = &thePlayer;
}

void    PlayerHealthBar::update(float deltaTime)
{
    (void)deltaTime; //Todo use to animate
    float health = m_pPlayer->getNormalizedHealth();
    float currentWidth = maxWidth * health;
    rectangle->setSize({currentWidth, maxHeight});
    followTarget();
    rectangle->setPosition(getPosition());
}

void    PlayerHealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    (void)states;
    target.draw(*rectangle);
}