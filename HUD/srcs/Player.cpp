#include "Player.hpp"

Player::Player() : position({250.0f, 250.0f}) {}

Player::Player(Game* pGame) 
    : m_pGame(pGame), position({250.0f, 250.0f})
{
    setPosition(position);
}

bool Player::initialize()
{
    body.setSize({100.0f, 100.0f});
    body.setFillColor(sf::Color::Magenta);
    body.setOrigin({0.0f, 0.0f});
    body.setPosition(getPosition());
    return true;
}

void Player::update(float deltaTime)
{
    (void)deltaTime;
    setPosition(position);
    body.setPosition(getPosition());
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    (void)states;
    target.draw(body);
}

float Player::getNormalizedHealth() const
{
    float normalized = currentHealth / maxHealth;
    return (normalized);
}