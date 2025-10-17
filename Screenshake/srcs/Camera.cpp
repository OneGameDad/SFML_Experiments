#include "Camera.hpp"

Camera::Camera(sf::Clock *clock, sf::RenderWindow *window)
    : window_(window), clock_(clock)
{
    camera_ = window_->getView();
    savePerlinImageSize();
}

Camera::Camera(sf::Clock *clock, sf::RenderWindow *window, float x, float y)
    : window_(window), clock_(clock), orig_center({x, y}), current_center({x, y})
{
    camera_ = window_->getView();
    savePerlinImageSize();
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
       cameraShake();
    }
    if (trauma > 0.0f)
    {
        trauma -= recoveryRate;
        if (trauma < 0.0f)
            trauma = 0.0f;
    }
}

void Camera::setPosition(float x, float y)
{
    orig_center = {x, y};
}

void Camera::beginCameraShake()
{
    if (!isShaking)
    {
        tNoiseOffsetX = rand(); //time offset for animating X position
        tNoiseOffsetY = 1.0 + rand(); // time offset for animating Y position
        tNoiseOffsetAngle = 2.0 + rand(); // time offset for animating Angle
    }
    addTrauma(0.25f);
    if (!isShaking)
        isShaking = true;
}

void Camera::cameraShake()
{
    if (trauma < traumaBuffer)
    {
        isShaking = false;
        current_center = orig_center;
        current_rotation = orig_rotation;
    }
    else
    {
        float shake = trauma * trauma; // Currently trauma^2, could try trauma^3
        float angle = maxAngleOffset * shake * (getPerlinNoiseValue(tNoiseOffsetAngle, speedMultiplierX) * 2.0f - 1.0f);
        float x = maxPixelOffset * shake * (getPerlinNoiseValue(tNoiseOffsetX, speedMultiplierY) * 2.0f - 1.0f);
        float y = maxPixelOffset * shake * (getPerlinNoiseValue(tNoiseOffsetY, speedMultiplierAngle) * 2.0f - 1.0f);
        
        current_center =  {orig_center.x + x, orig_center.y + y};
        current_rotation = orig_rotation + angle;
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

void Camera::savePerlinImageSize()
{
    noiseImgWidth = static_cast<float>(BitmapReader::Instance.GetWidth());
    noiseImgHeight = static_cast<float>(BitmapReader::Instance.GetHeight());
}