#include "Camera.hpp"

Camera::Camera(sf::Clock *clock, sf::RenderWindow *window)
    : window_(window), clock_(clock)
{
    camera_ = window_->getView();
}

Camera::Camera(sf::Clock *clock, sf::RenderWindow *window, float x, float y)
    : window_(window), clock_(clock), orig_center({x, y}), current_center({x, y})
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
        tNoiseOffsetXX = rand() * 10; //time offset for animating X position
        tNoiseOffsetXY = rand();
        tNoiseOffsetYX = 1.0 + rand() * 10; // time offset for animating Y position
        tNoiseOffsetYY = rand();
        tNoiseOffsetAngleX = 2.0 + rand() * 10 ; // time offset for animating Angle
        tNoiseOffsetAngleY = rand();
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
        float angle = maxAngleOffset * shake * (PerlinNoiseGenerator::Instance().getPerlinXValue(tNoiseOffsetXX, tNoiseOffsetXY, speedMultiplierX));
        float x = maxPixelOffset * shake * (PerlinNoiseGenerator::Instance().getPerlinYValue(tNoiseOffsetYX, tNoiseOffsetYY, speedMultiplierY));
        float y = maxPixelOffset * shake * (PerlinNoiseGenerator::Instance().getPerlinAngleValue(tNoiseOffsetAngleX, tNoiseOffsetAngleY, speedMultiplierAngle));
        
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