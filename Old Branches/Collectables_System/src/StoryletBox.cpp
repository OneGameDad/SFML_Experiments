#include "StoryletBox.h"

StoryletBox::StoryletBox(sf::Font& pFont, const std::string& value)
    : ATextBox(pFont)
{
    content = value;
    content = wrapText(content);
    text.setString(content);
}

StoryletBox::~StoryletBox() = default;

void    StoryletBox::initialize()
{
    text.setPosition(getPosition());
    text.setFont(*m_pFont);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Italic);
    text.setCharacterSize(charSize);
}

void    StoryletBox::initialize(sf::Vector2f a_position, unsigned int fontSize)
{
    setPosition(a_position);
    text.setPosition(getPosition());
    text.setFont(*m_pFont);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Italic);
    text.setCharacterSize(fontSize);
}

void    StoryletBox::update(float deltatime)
{
    (void) deltatime;
}

void    StoryletBox::update(const std::string& str)
{
    content = str;
    content = wrapText(content);
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

void StoryletBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}
