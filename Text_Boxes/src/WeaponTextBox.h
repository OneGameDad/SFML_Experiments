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

    virtual void    initialize(float a_duration) override;
    virtual void    update(float deltaTime) override;
};