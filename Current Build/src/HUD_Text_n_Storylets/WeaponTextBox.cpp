#include "WeaponTextBox.h"

WeaponTextBox::WeaponTextBox(sf::Font& pFont, Player* pPlayer) 
    : ATextBox(pFont), m_pPlayer(pPlayer)
{}

WeaponTextBox::~WeaponTextBox() = default;

void    WeaponTextBox::initialize()
{
    setPosition(m_pPlayer->getWeapon()->getPosition());
    text.setFont(*m_pFont);
    text.setString(content);
    text.setFillColor(sf::Color::White);
    sf::Vector2f size = m_pPlayer->getWeapon()->getSize();
    text.setPosition(getPosition().x + (size.x / 2.0f), getPosition().y + offsetY);
    text.setStyle(sf::Text::Italic);
    text.setCharacterSize(charSize);
}

void    WeaponTextBox::update(float deltaTime)
{
    setPosition(m_pPlayer->getWeapon()->getPosition());
    sf::Vector2f size = m_pPlayer->getWeapon()->getSize();
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

void    WeaponTextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}