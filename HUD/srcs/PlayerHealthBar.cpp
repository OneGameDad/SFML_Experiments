#include "PlayerHealthBar.hpp"

PlayerHealthBar::PlayerHealthBar(Game *pGame)
    : m_pGame(pGame), m_pPlayer(m_pGame->getPlayer())
{}

PlayerHealthBar::~PlayerHealthBar()
{
    delete rectangle;
}

/*These two do nothing and are not meant to be used - purely to appease the compiler*/
void    PlayerHealthBar::initialize(){}
void    PlayerHealthBar::initialize(sf::Vector2f a_position)
{
    (void)a_position;
}

void   PlayerHealthBar::initialize(sf::Transformable& thePlayer)
{
    rectangle = new sf::RectangleShape();
    setQueryTarget(*m_pPlayer);
    setFollowTarget(thePlayer);
    rectangle->setSize({maxWidth, maxHeight});
    rectangle->setFillColor(sf::Color::Red);
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