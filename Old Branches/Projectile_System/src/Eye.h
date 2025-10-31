#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include "APropertyAnimator.h"
#include "LinearAnimator.h"
#include "Tweener.h"
#include "Game.h"
#include "Rectangle.h"

class Game;

class Eye: public Rectangle
{
private:
    Game* m_pGame;
    std::vector<std::unique_ptr<sf::Texture>>*   textures;
    int currentTextureIndex = 0;
    double  duration = 1.0f;
    std::unique_ptr<Tweener>   tweener;
    size_t  frameCount = 0;
    bool    googlyRequested =  false;

    void    incrementTexture();
public:
    Eye(Game* pGame);
    virtual ~Eye();

    void    initialize();
    void    setDuration(double amount);
    void    update();
    void    setPosition(float x, float y);
    void    beginAnimating();
    void    requestGoogly();
    
};
