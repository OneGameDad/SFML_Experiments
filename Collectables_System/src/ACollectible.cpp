#include "ACollectible.h"

ACollectible::ACollectible(Game* pGame, sf::Texture *a_texture)
    : Rectangle(sf::Vector2f{10.0f, 10.0f}, startPos), m_pGame(pGame)
{
    m_sprite.setTexture(*a_texture);
    m_sprite.setScale({1.0f, 1.0f});
    m_sprite.setColor(sf::Color::Cyan);
}

ACollectible::~ACollectible(){}

void    ACollectible::update(float deltaTime)
{
    if (state == WAITING)
    {
        lifetime -= deltaTime;
        updateCollisions();
        if (lifetime <= 0.0f)
            state = WAITING;
    }
}


void    ACollectible::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (state == PLACED)
    {
        target.draw(m_sprite, states);   
    }
}

void    ACollectible::activate(sf::Vector2f a_position, float a_lifetime)
{
    reset();
    setPosition(a_position);
    m_sprite.setPosition(getPosition());
    lifetime = a_lifetime;
    state = PLACED;
}

void    ACollectible::deactivate()
{
    state = WAITING;
}

void    ACollectible::reset()
{
    deactivate();
    lifetime = 0.0f;
    sf::Vector2f startPos = {0.0f, 0.0f};
}

void    ACollectible::updateCollisions()
{
    Player* pPlayer = m_pGame->getPlayer();
    if (collidesWith(pPlayer))
    {
        beCollected(pPlayer);
        deactivate();
    }
}

void    ACollectible::beCollected(Player* pOther)
{
    pOther->addXP(2);
}