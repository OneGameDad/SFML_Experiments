#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include "HUDComponent.hpp"

class HUDComponentWithFollow: public HUDComponent
{
protected:
    sf::Drawable *target;
public:
    HUDComponentWithFollow();
    virtual ~HUDComponentWithFollow();

    void    setFollowTarget(sf::Drawable& following);
};