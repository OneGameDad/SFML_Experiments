#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdlib>
#include <iostream>

class Eye
{
private:
    sf::Sprite sprite_;
    std::vector<sf::Texture> textures_;
    int currentTextureIndex = 0;
    bool isAnimating = false;
    constexpr static int32_t MILLISECONDS_PER_FRAME = 333;
    int32_t nextAnimationTime = 0;

    void incrementTexture();
public:
    Eye();
    ~Eye();

    void setTextures(sf::Texture &texture);
    void Update();
    void setPosition(float x, float y);
    sf::Sprite getSprite() const;
    std::vector<sf::Texture> getTextures() const;
    void setIsAnimating();
};