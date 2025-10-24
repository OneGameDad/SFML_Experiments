#include "HUDComponentWithFollow.hpp"

HUDComponentWithFollow::HUDComponentWithFollow(){}

HUDComponentWithFollow::~HUDComponentWithFollow() = default;

void    HUDComponentWithFollow::setFollowTarget(sf::Transformable& following)
{
    target = &following;
}

sf::Vector2f HUDComponentWithFollow::getTargetPositionAdjusted()
{
    sf::Vector2f position = getPosition();
    sf::Vector2f result = {position.x + offsetX, position.y + offsetY };
    return (result);
}

void    HUDComponentWithFollow::followTarget()
{
    move(getTargetPositionAdjusted());
}