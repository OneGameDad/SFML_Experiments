#include "Player.hpp"

Player::Player() : position({250.0f, 250.0f}) {}

Player::Player(Game* pGame) 
    : m_pGame(pGame), position({250.0f, 250.0f})
{}

bool Player::initialize()
{
    body.setSize({100.0f, 100.0f});
    body.setFillColor(sf::Color::Magenta);
    body.setOrigin({0.0f, 0.0f});
    body.setPosition(position);
    return true;
}

void Player::update(float deltaTime)
{
    (void)deltaTime;
    body.setPosition(position);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    (void)states;
    target.draw(body);
}