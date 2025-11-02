#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

class HUDComponent: public sf::Drawable, public sf::Transformable
{
protected:
    
public:
    HUDComponent() = default;
    virtual ~HUDComponent() = 0;

    virtual void    initialize() = 0;
    virtual void    update(float deltaTime) = 0;
    virtual void    draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;
};