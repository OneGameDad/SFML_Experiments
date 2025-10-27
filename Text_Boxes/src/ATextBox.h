#pragma once

#include "HUDComponent.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

class ATextBox: public HUDComponent
{
protected:
    sf::Font* m_pFont;
    sf::Text text;
    unsigned int charSize = 14;
    std::string content;
    bool isActive = false;
    float duration = 0.0f;
    float elapsed = 0.0f;

    float offsetX = 0.0f;
    float offsetY = 0.0f;
public:
    ATextBox(sf::Font& pFont);
    virtual ~ATextBox();

    virtual void    initialize(float a_duration);
    virtual void    update(float deltaTime);
    virtual void    activate();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void    setString(const std::string &str);
    virtual void    setTextOffsets(float x, float y);
};