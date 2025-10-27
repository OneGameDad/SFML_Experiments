#include "StoryletBox.h"

StoryletBox::StoryletBox(sf::Font& pFont, std::string& value)
    : ATextBox(pFont)
{
    content = value;
    text.setString(content);
}

StoryletBox::~StoryletBox() = default;

void    StoryletBox::initialize()
{
    setPosition({0.0f, 0.0f});
    text.setFont(*m_pFont);
    text.setFillColor(sf::Color::White);
    text.setPosition(getPosition());
    text.setStyle(sf::Text::Italic);
    text.setCharacterSize(charSize);
}

void    StoryletBox::update(std::string& str)
{
    content = str;
    text.setString(content);
}

void    StoryletBox::activate()
{
    if (!isActive)
        isActive = true;
}

void    StoryletBox::deactivate()
{
    if (isActive)
        isActive = false;
}
