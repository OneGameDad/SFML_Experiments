#include "HUDComponentWithFollow.hpp"

HUDComponentWithFollow::HUDComponentWithFollow(){}

void    HUDComponentWithFollow::setFollowTarget(sf::Drawable& following)
{
    target = following;
}