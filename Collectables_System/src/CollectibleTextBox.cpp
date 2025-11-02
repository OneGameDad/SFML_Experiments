#include "CollectibleTextBox.h"

CollectibleTextBox::CollectibleTextBox(sf::Font& pFont, ACollectible* pCollectible, float a_duration) 
    : ATextBox(pFont), m_pCollectible(pCollectible), duration(a_duration)
{}

CollectibleTextBox::~CollectibleTextBox() = default;

void    CollectibleTextBox::initialize()
{
    setPosition(m_pCollectible->getSprite().getPosition());
    text.setFont(*m_pFont);
    text.setString(content);
    text.setFillColor(sf::Color::White);
    text.setPosition(getPosition());
    text.setStyle(sf::Text::Italic);
    text.setCharacterSize(charSize);
    std::cout << "Text Box Initialized\n";
}

void    CollectibleTextBox::update(float deltaTime)
{
    if (isActive)
    {
        std::cout << "Text Box Active\n";
        elapsed += deltaTime;
        if (elapsed >= duration)
        {
            isActive = false;
            elapsed = 0.0f;
            return;
        }
    }
}

void    CollectibleTextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{   
        target.draw(text, states);
}