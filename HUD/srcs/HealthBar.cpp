#include "HealthBar.hpp"

HealthBar::HealthBar(){}

HealthBar::~HealthBar(){}
    
void    initialize()
{
    sprite = std::make_unique<sf::Sprite>(this);
    setQueryTarget()
}

void    setQueryTarget(Player& thePlayer)
{
    player = thePlayer;
}