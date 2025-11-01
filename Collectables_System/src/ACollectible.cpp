#include "ACollectible.h"

ACollectible::ACollectible(Game* pGame, sf::Texture *a_texture)
    : Rectangle(sf::Vector2f{10.0f, 10.0f}, startPos), m_pGame(pGame), m_collisionEffect(std::make_unique<CollectibleTextBox>(m_pGame->getFont(), this, END_EFFECT_DURATION))
{
    m_sprite.setTexture(*a_texture);
    m_sprite.setScale({0.025f, 0.025f});
    m_sprite.setColor(sf::Color::Cyan);
}

ACollectible::~ACollectible(){}

void    ACollectible::update(float deltaTime)
{
    if (state == NACTIVE)
    {
        lifetime -= deltaTime;
        updateCollisons();
        if (lifetime <= 0.0f)
            state = INACTIVE;
    }
}


void    ACollectible::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (state == ACTIVE)
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
    state = ACTIVE;
}

void    ACollectible::deactivate()
{
    state = INACTIVE;
}

void    ACollectible::reset()
{
    state = INACTIVE;
    lifetime = 0.0f;
    sf::Vector2f startPos = {0.0f, 0.0f};
}

void    ACollectible::updateCollisions()
{
    if (collidesWith(m_pGame->getPlayer()))
    {
        beCollected(m_pGame->getPlayer());
        state = INACTIVE;
    }
}

void    ACollectible::beCollected(Player* pOther)
{
    pOther->addXP(2);
}