#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdlib>
#include <iostream>
#include "APropertyAnimator.hpp"
#include "LinearAnimator.hpp"
#include "Tweener.hpp"

class Eye
{
private:
    sf::Sprite  sprite_;
    std::vector<sf::Texture>    textures_;
    int currentTextureIndex = 0;
    bool    isAnimating = false;
    double  duration = 0.3f;
    Tweener   *tweener;
    size_t  frameCount = 0;
    bool    useModulo = false;

    void    incrementTexture();
public:
    Eye();
    ~Eye();

    void    setTextures(sf::Texture &texture);
    void    setDuration(double amount);
    void    Update();
    void    setPosition(float x, float y);
    sf::Sprite  getSprite() const;
    std::vector<sf::Texture> getTextures() const;
    void    setIsAnimating();
    void    beginAnimating();
};
