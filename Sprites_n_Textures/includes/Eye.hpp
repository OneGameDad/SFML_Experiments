#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdlib>
#include <iostream>
#include <chrono>

class Eye
{
private:
    sf::Sprite sprite_;
    std::vector<sf::Texture> textures_;
    int currentTextureIndex = 0;
    bool isAnimating = false;
    constexpr static float SECONDS_PER_FRAME = 0.0333f;
    float nextAnimationTime = 0.0f;

    void incrementTexture();
public:
    Eye();

    void setTextures(sf::Texture &texture);
    void Update();
    void setPosition(float x, float y);
    sf::Sprite getSprite() const;
    std::vector<sf::Texture> getTextures() const;
    void setIsAnimating();
};