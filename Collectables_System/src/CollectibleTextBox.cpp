#include "CollectibleTextBox.h"

CollectibleTextBox::CollectibleTextBox(sf::Font& pFont, Collectible* pCollectible, float a_duration) 
    : ATextBox(pFont), m_pCollectible(pCollectible), duration(a_duration)
{}

CollectibleTextBox::~CollectibleTextBox() = default;

void    CollectibleTextBox::initialize()
{
    setPosition(m_pCollectible->getSprite().getPosition());
    text.setFont(*m_pFont);
    text.setString(content);
    text.setFillColor(sf::Color::White);
    auto textureSize = m_pCollectible->getSprite().getTexture()->getSize();
    sf::Vector2f size (static_cast<float>(textureSize.x), static_cast<float>(textureSize.y));
    text.setPosition(getPosition().x + (size.x / 2.0f), getPosition().y + offsetY);
    text.setStyle(sf::Text::Italic);
    text.setCharacterSize(charSize);
}

void    CollectibleTextBox::update(float deltaTime)
{
    setPosition(m_pCollectible->getSprite().getPosition());
    auto textureSize = m_pCollectible->getSprite().getTexture()->getSize();
    sf::Vector2f size (static_cast<float>(textureSize.x), static_cast<float>(textureSize.y));
    text.setPosition(getPosition().x + (size.x / 2.0f), getPosition().y + offsetY);
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

void    CollectibleTextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (isActive)
    {    
        target.draw(text, states);
    }
}