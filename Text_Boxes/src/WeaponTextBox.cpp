#include "WeaponTextBox.h"

WeaponTextBox::WeaponTextBox(sf::Font& pFont, Player* pPlayer) 
    : ATextBox(pFont), m_pPlayer(pPlayer)
{}

WeaponTextBox::~WeaponTextBox(){};

void    WeaponTextBox::initialize(float a_duration)
{
    setPosition(m_pPlayer->getWeapon()->getPosition());
    duration = a_duration;
    text.setFont(*m_pFont);
    text.setString(content);
    text.setFillColor(sf::Color::White);
    text.setPosition(getPosition().x + offsetX, getPosition().y + offsetY);
    text.setStyle(sf::Text::Italic);
    text.setCharacterSize(charSize);
}

void    WeaponTextBox::update(float deltaTime)
{
    setPosition(m_pPlayer->getWeapon()->getPosition());
    text.setPosition(getPosition());
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