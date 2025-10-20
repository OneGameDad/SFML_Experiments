#include "Eye.hpp"

Eye::Eye()
{
    textureAnimator = new LinearAnimator(textureSpeedMultipliear);
}

Eye::~Eye()
{
    delete textureAnimator;
}

void Eye::setTextures(sf::Texture &texture)
{
    textures_.push_back(texture);
    sprite_.setTexture(textures_.back());
    frameCount = textures_.size();
}

void Eye::setDuration(double amount)
{
    if (amount < 0.1)
        duration = 0.1;
    else
        duration = amount;
}

 void Eye::Update()
{
    if (isAnimating)
    {
        incrementTexture();
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
    double newIndex = textureAnimator->update(duration, useModulo) *(frameCount - 1);
    if (newIndex >= 1.0)
    {
        newIndex = 0.0;
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

void Eye::setUseModulo(bool yes)
{
    if (yes)
        useModulo = true;
    else
        useModulo = false;
}