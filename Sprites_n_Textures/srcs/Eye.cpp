#include "Eye.hpp"

Eye::Eye(){}

void Eye::setTextures(sf::Texture &texture)
{
    textures_.push_back(texture);
    sprite_.setTexture(textures_.back());
}

 void Eye::Update()
{
    if (isAnimating)
    {
        static auto start = std::chrono::steady_clock::now();
        auto now = std::chrono::steady_clock::now();
        float currTime = std::chrono::duration_cast<std::chrono::duration<float>>(now - start).count();
        if (currTime >= nextAnimationTime)
        {
            incrementTexture();
            nextAnimationTime = currTime + SECONDS_PER_FRAME;
        }
    }
}

void Eye::setPosition(float x, float y)
{
    sprite_.setPosition({x, y});
}

sf::Sprite Eye::getSprite() const { return (sprite_); }
std::vector<sf::Texture> Eye::getTextures() const { return (textures_); }

void Eye::incrementTexture()
{
    std::cout << "Current Index: " << currentTextureIndex << std::endl;
    size_t newIndex = currentTextureIndex + 1;
    std::cout << "New Index: " << newIndex << std::endl;
    if (newIndex >= textures_.size())
    {
        newIndex = 0;
        isAnimating = false;
    }
    currentTextureIndex = newIndex;
    sprite_.setTexture(textures_[currentTextureIndex]);
}

void Eye::setIsAnimating()
{
    if (!isAnimating)
        isAnimating = true;
}