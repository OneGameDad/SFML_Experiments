#pragma once

#include "ATextBox.h"
#include "Player.h"

class Player;

class WeaponTextBox: public ATextBox
{
private:
    Player* m_pPlayer;
public:
    WeaponTextBox(sf::Font& pFont, Player* pPlayer);
    ~WeaponTextBox();

    void    initialize() override;
    void    update(float deltaTime) override;
    void    draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};