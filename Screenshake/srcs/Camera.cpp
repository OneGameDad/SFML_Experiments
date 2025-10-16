#include "Camera.hpp"

Camera::Camera(sf::Clock *clock, sf::RenderWindow *window)
    : window_(window), clock_(clock)
{
    camera_ = window_->getView();
    perlinX = getRandomPerlinCoord();
    perlinY = getRandomPerlinCoord();
}

Camera::Camera(sf::Clock *clock, sf::RenderWindow *window, float x, float ym)
    : window_(window), clock_(clock), orig_center({x, y}), current_center({x, y}), orig_size({w, h})
{
    camera_ = window_->getView();
}

Camera::~Camera()
{
    clock_ = nullptr;
    window_ = nullptr;
}

 void Camera::Update()
{
    if (isShaking)
    {
        static auto start = clock_->restart().asMilliseconds();
        auto now = clock_->getElapsedTime().asMilliseconds();
        float currTime = now - start;
        if (currTime >= nextAnimationTime)
        {
            cameraShake();
            nextAnimationTime = currTime + MILLISECONDS_PER_FRAME;
        }
    }
    if (trauma != 0.0f)
    {
        trauma -= recoveryRate;
    }
}

void Camera::setPosition(float x, float y)
{
    orig_center = {x, y};
}

void Camera::setMaxFrames(size_t frames)
{
    max_frames = frames;
}

void Camera::setIsShaking()
{
    if (!isShaking)
        isShaking = true;
}

void Camera::cameraShake()
{
    current_frame++;
    if (current_frame >= max_frames)
    {
        isShaking = false;
        current_center = orig_center;
        current_rotation = orig_rotation;
        current_frame = 0;
    }
    else
    {
       
        float shake = trauma * trauma; // Currently trauma^2, could try trauma^3
        float angle = maxAngle * shake * BitmapReader::GetPerlinNoise();
        float offsetX = maxOffset * shake * BitmapReader::GetPerlinNoise(perlinX);
        float offsetY = maxOffset * shake * BitmapReader::GetPerlinNoise(perlinY);
        current_center =  {orig_center.x + offsetX, orig_center.y + offsetY};
        current_rotation = orig_rotation + angle;
        perlinX = iteratePerlinCoord(perlinX);
        perlinY = iteratePerlinCoord(perlinY);
    }
    camera_.move(current_center);
    camera_.setRotation(current_rotation);

    window_->setView(camera_);
}

void Camera::addTrauma(float amount)
{
    if ((trauma + amount) >= 1.0f)
        trauma = 1.0f;
    else if ((trauma + amount) < 0.0f)
        trauma = 0.0f;
    else
        trauma += amount;
}

void Camera::setRecoveryRate(float amount)
{
    if (amount > 0.0f)
        recoveryRate = amount;
}

sf::Vector2f Camera::getRandomPerlinCoord()
{
    unsigned int Width = BitmapReader::GetWidth();
    unsigned int Height = BitmapReader::GetHeight();
    float x = static_cast<float>(getRandomClamped(Width));
    float y = static_cast<float>(getRandomClamped(Height));
    return (sf::Vector2f{x, y});
}

sf::Vector2f iteratePerlinCoord(sf::Vector2f &perlinCoord)
{
    static unsigned int Width = BitmapReader::GetWidth() - 1;
    static unsigned int Height = BitmapReader::GetHeight() - 1;
    sf::Vector2f result = {0.0f, 0.0f};
    
    if (static_cast<unsigned int>(perlinCoord.x + pixelJumpValue) > Width)
    {
        if (static_cast<unsigned int>(perlinCoord.y + 1) > Height)
        {
            result.x = 0.0f;
            result.y = 0.0f;
        }
        else
        {
            result.x = 0.0f;
            result.y = perlinCoord.y + 1;
        }
    }
    else
    {
        result.x = perlinCoord.x + pixelJumpValue;
        result.y = perlinCoord.y;
    }
    return (result);
}