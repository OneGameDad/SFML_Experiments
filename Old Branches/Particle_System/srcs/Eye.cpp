#include "Eye.hpp"

Eye::Eye()
{
    tweener = new Tweener(0.0f, 5.0f, (float)duration, new LinearAnimator(duration, false));
}
    
Eye::~Eye()
{
    delete tweener;
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
    if (googlyRequested /*|| sf::Keyboard::Tab*/)
    {
        beginAnimating();
        googlyRequested = false;
    }
    float frame = std::fmod((tweener->update() * frameCount), frameCount);
    currentTextureIndex = (size_t)std::floor(frame);
    sprite_.setTexture(textures_[currentTextureIndex]);
}

void Eye::setPosition(float x, float y)
{
    sprite_.setPosition({x, y});
}

sf::Sprite Eye::getSprite() const { return (sprite_); }
std::vector<sf::Texture> Eye::getTextures() const { return (textures_); }

void    Eye::beginAnimating()
{
    tweener->reset();
    tweener->play();
}

void    Eye::requestGoogly()
{
    if (!googlyRequested)
        googlyRequested = true;
}