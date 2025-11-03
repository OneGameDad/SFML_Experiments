#include "ACollectible.h"

ACollectible::ACollectible(Game* pGame, sf::Texture *a_texture)
    : Rectangle(sf::Vector2f{10.0f, 10.0f}, startPos), m_pGame(pGame)
{
    m_collectedEffect = std::make_unique<CollectibleTextBox>(m_pGame->getFont(), this, pluckDuration); 
    m_sprite.setTexture(*a_texture);
    m_sprite.setScale({1.0f, 1.0f});
    m_sprite.setColor(sf::Color::Cyan);
}

ACollectible::~ACollectible(){}

void    ACollectible::update(float deltaTime)
{
    if (state == PLACED)
    {
        lifetime -= deltaTime;
        updateCollisions();
        if (lifetime <= 0.0f && state == PLACED)
            state = WAITING;
    }
    if (state == COLLECTED)
    {
        m_collectedEffect->update(deltaTime);
        if (!m_collectedEffect->getIsActive())
            deactivate();
    }
}


void    ACollectible::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (state == PLACED)
    {
        target.draw(m_sprite, states);   
    }
    if (state == COLLECTED)
    {
        target.draw(*m_collectedEffect, states);
    }
}

void    ACollectible::activate(sf::Vector2f a_position, float a_lifetime, e_coll_types a_kind)
{
    reset();
    setPosition(a_position);
    m_sprite.setPosition(getPosition());
    lifetime = a_lifetime;
    kind  = a_kind;
    if (kind == ENERGIZING)
        m_sprite.setColor(sf::Color::Yellow);
    else if (kind == HEALING)
        m_sprite.setColor(sf::Color::Red);
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
    kind = ENERGIZING;
    m_sprite.setColor(sf::Color::Cyan);
    sf::Vector2f startPos = {0.0f, 0.0f};
}

void    ACollectible::updateCollisions()
{
    Player* pPlayer = m_pGame->getPlayer();
    if (collidesWith(pPlayer))
    {
        state = COLLECTED;
        beCollected(pPlayer);
        setupTextBox();
    }
}

void    ACollectible::beCollected(Player* pPlayer)
{
    switch (kind)
    {
        case ENERGIZING:
            pPlayer->addEnergy(1);
            break;
        case HEALING:
            pPlayer->heal(2.0f);
            break;
        default:
            break;  
    }  
}

void    ACollectible::setupTextBox()
{
    m_collectedEffect->initialize();
    m_collectedEffect->setString(collectionStr);
    m_collectedEffect->activate();
    std::cout << "Collected\n";
}