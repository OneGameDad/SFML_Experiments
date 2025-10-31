#include "ProjectileTextBox.h"

ProjectileTextBox::ProjectileTextBox(sf::Font& pFont, AProjectile* pProjectile, float a_duration) 
    : ATextBox(pFont), m_pProjectile(pProjectile), duration(a_duration)
{}

ProjectileTextBox::~ProjectileTextBox() = default;

void    ProjectileTextBox::initialize()
{
    setPosition(m_pProjectile->getSprite().getPosition());
    text.setFont(*m_pFont);
    text.setString(content);
    text.setFillColor(sf::Color::White);
    auto textureSize = m_pProjectile->getSprite().getTexture()->getSize();
    sf::Vector2f size (static_cast<float>(textureSize.x), static_cast<float>(textureSize.y));
    text.setPosition(getPosition().x + (size.x / 2.0f), getPosition().y + offsetY);
    text.setStyle(sf::Text::Italic);
    text.setCharacterSize(charSize);
}

void    ProjectileTextBox::update(float deltaTime)
{
    setPosition(m_pProjectile->getSprite().getPosition());
    auto textureSize = m_pProjectile->getSprite().getTexture()->getSize();
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

void    ProjectileTextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}