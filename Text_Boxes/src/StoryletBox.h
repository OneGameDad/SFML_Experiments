#pragma once

#include "ATextBox.h"
#include <iostream>

class StoryletBox: public ATextBox
{
private:

public:
    StoryletBox(sf::Font& pFont, const std::string& value);
    ~StoryletBox();

    virtual void    initialize() override;
    virtual void    initialize(sf::Vector2f position, unsigned int fontSize);
    virtual void    update(float deltaTime);
    virtual void    update(const std::string& str);
    virtual void    activate() override;
    virtual void    deactivate();
    virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};