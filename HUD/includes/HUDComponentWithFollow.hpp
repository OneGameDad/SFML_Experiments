#pragma once


#include <SFML/System/Vector2.hpp>
#include "HUDComponent.hpp"

class HUDComponentWithFollow: public HUDComponent
{
protected:
    sf::Transformable *target;
    const float offsetX = 0.0f;
    const float offsetY = -20.0f;

    sf::Vector2f getTargetPositionAdjusted();
    void followTarget();
public:
    HUDComponentWithFollow();
    virtual ~HUDComponentWithFollow() = 0;

    virtual void    update(float deltaTime) = 0;
    void    setFollowTarget(sf::Transformable& following);
};