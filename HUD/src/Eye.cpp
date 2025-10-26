#include "Eye.h"

Eye::Eye(Game* pGame)
    : Rectangle(sf::Vector2f(100.0f, 100.0f)), m_pGame(pGame)
{
    tweener = std::make_unique<Tweener>(0.0f, 5.0f, (float)duration, std::make_unique<LinearAnimator>(duration, false));
    textures = m_pGame->getEyeTextures();
    frameCount = textures->size();
}
    
Eye::~Eye() = default;

void Eye::setDuration(double amount)
{
    if (amount < 0.1)
        duration = 0.1;
    else
        duration = amount;
}

void Eye::update()
{
    if (googlyRequested)
    {
        beginAnimating();
        googlyRequested = false;
    }
    float frame = std::fmod((tweener->update() * frameCount), frameCount);
    currentTextureIndex = (size_t)std::floor(frame);
    m_sprite.setTexture(*(*textures)[currentTextureIndex]);
}

void Eye::initialize()
{
    m_sprite.setTexture(*(*textures)[0]);
    m_sprite.setPosition({100.0f, 100.0f});
    sf::Vector2u texSize = (*textures)[0]->getSize();
    float targetWidth = 25.0f;
    float scale = targetWidth / texSize.x;
    m_sprite.setScale({scale, scale});
    frameCount = textures->size();
}

void Eye::setPosition(float x, float y)
{
    m_sprite.setPosition({x, y});
}

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