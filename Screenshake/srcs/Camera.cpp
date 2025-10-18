#include "Camera.hpp"

Camera::Camera(sf::Clock *clock, sf::RenderWindow *window)
    : window_(window), clock_(clock)
{
    camera_ = window_->getView();
    orig_center = camera_.getCenter();
    orig_rotation = camera_.getRotation();
    xPosAnimator = new PropertyAnimator(speedMultiplierX);
    yPosAnimator = new PropertyAnimator(speedMultiplierY);
    angleAnimator = new PropertyAnimator(speedMultiplierAngle);
}

Camera::Camera(sf::Clock *clock, sf::RenderWindow *window, float x, float y)
    : window_(window), clock_(clock), orig_center({x, y}), current_center({x, y})
{
    camera_ = window_->getView();
    orig_center = camera_.getCenter();
    orig_rotation = camera_.getRotation();
    xPosAnimator = new PropertyAnimator(speedMultiplierX);
    yPosAnimator = new PropertyAnimator(speedMultiplierY);
    angleAnimator = new PropertyAnimator(speedMultiplierAngle);
}

Camera::~Camera()
{
    clock_ = nullptr;
    window_ = nullptr;
    delete angleAnimator;
    delete yPosAnimator;
    delete xPosAnimator;
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
        std::cout << "Trauma Level: " << trauma << std::endl;
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
        xPosAnimator->reset();
        yPosAnimator->reset();
        angleAnimator->reset();
    }
    addTrauma(moreTraumaPlease);
    std::cout << "Trauma Level: " << trauma << std::endl;
    if (!isShaking)
        isShaking = true;
}

void Camera::cameraShake()
{
    if (trauma <= traumaBuffer)
    {
        isShaking = false;
        current_center = orig_center;
        current_rotation = orig_rotation;
    }
    else
    {
        float shake = trauma * trauma; // Currently trauma^2, could try trauma^3
        float angle = maxAngleOffset * shake * angleAnimator->update(g_data.currentTime);
        float x = maxPixelOffset * shake * xPosAnimator->update(g_data.currentTime);
        float y = maxPixelOffset * shake * yPosAnimator->update(g_data.currentTime);
        
        current_center =  {orig_center.x + x, orig_center.y + y};
        current_rotation = orig_rotation + angle;
    }
    camera_.setCenter(current_center);
    camera_.setRotation(current_rotation);

    window_->setView(camera_);
}

void Camera::addTrauma(float amount)
{
    if ((trauma + amount) >= maxTrauma)
        trauma = maxTrauma;
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