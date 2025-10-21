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
    float frame = tweener->update() * (frameCount - 1);
    if (/*frame >= frameCount ||*/ !tweener->getIsPlaying())
    {
        frame = 0.0f;
        isAnimating = false;
        std::cout << "Eye isAnimating = False\n";
    }
    currentTextureIndex = (size_t)std::floor(frame);
    std::cout << "CurrentTextureIndex: " << currentTextureIndex << std::endl;
    sprite_.setTexture(textures_[currentTextureIndex]);
}

void Eye::setIsAnimating()
{
    if (!isAnimating)
    {
        isAnimating = true;
        std::cout << "Eye isAnimating = true\n";
        beginAnimating();
    }
}

void    Eye::beginAnimating()
{
    tweener->reset();
    tweener->play();
}