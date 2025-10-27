#pragma once

#include "ATextBox.h"

class StoryletBox: public ATextBox
{
private:

public:
    StoryletBox(sf::Font& pFont, std::string& value);
    ~StoryletBox();

    virtual void    initialize() override;
    virtual void    update(float deltaTime);
    virtual void    update(std::string& str);
    virtual void    activate() override;
    virtual void    deactivate();
};