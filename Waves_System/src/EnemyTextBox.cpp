#include "EnemyTextBox.h"

EnemyTextBox::EnemyTextBox(sf::Font& pFont, Enemy* pEnemy, float a_duration) 
    : ATextBox(pFont), m_pEnemy(pEnemy), duration(a_duration)
{}

EnemyTextBox::~EnemyTextBox() = default;

void    EnemyTextBox::initialize()
{
    setPosition(m_pEnemy->getSprite().getPosition());
    text.setFont(*m_pFont);
    text.setString(content);
    text.setFillColor(sf::Color::White);
    auto textureSize = m_pEnemy->getSprite().getTexture()->getSize();
    sf::Vector2f size (static_cast<float>(textureSize.x), static_cast<float>(textureSize.y));
    text.setPosition(getPosition().x + (size.x / 2.0f), getPosition().y + offsetY);
    text.setStyle(sf::Text::Italic);
    text.setCharacterSize(charSize);
}

void    EnemyTextBox::update(float deltaTime)
{
    setPosition(m_pEnemy->getSprite().getPosition());
    auto textureSize = m_pEnemy->getSprite().getTexture()->getSize();
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

void    EnemyTextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}