#include "ATextBox.h"

ATextBox::ATextBox(sf::Font& pFont)
{
    m_pFont = &pFont;
}

ATextBox::~ATextBox(){}

void ATextBox::initialize(float a_duration)
{
    setPosition(0.0f, 0.0f);
    duration = a_duration;
    text.setFont(*m_pFont);
    text.setString(content);
    text.setFillColor(sf::Color::White);
    text.setPosition(getPosition().x + offsetX, getPosition().y + offsetY);
    text.setStyle(sf::Text::Italic);
    text.setCharacterSize(charSize);
}

void ATextBox::update(float deltaTime)
{
    //TODO Update position
    if (isActive)
    {
        elapsed += deltaTime;
        if (elapsed >= duration)
        {
            isActive = false;
            elapsed = 0.0f;
            return;
        }
    }
}

void ATextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (isActive)
    {  
        target.draw(text);
    }
}

void ATextBox::activate()
{
    if (!isActive)
        isActive = true;
}

void ATextBox::setString(const std::string& str)
{
    content = str;
    text.setString(content);
}

void    ATextBox::setTextOffsets(float x, float y)
{
    offsetX = x;
    offsetY = y;
}