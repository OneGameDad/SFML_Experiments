#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

class HUDComponent: public sf::Drawable
{
protected:
    sf::Vector2f position;
    void    setPosition();
public:
    HUDComponent();
    ~HUDComponent();

    virtual void    init();
    virtual void    update(float deltaTime);
    virtual void    draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};