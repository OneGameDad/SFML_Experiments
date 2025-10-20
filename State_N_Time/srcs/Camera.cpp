#include "Camera.hpp"

Camera::Camera(sf::RenderWindow *window)
    : window_(window)
{
    camera_ = window_->getView();
    orig_center = camera_.getCenter();
    orig_rotation = camera_.getRotation();
    xPosAnimator = new PerlinAnimator(speedMultiplierX);
    yPosAnimator = new PerlinAnimator(speedMultiplierY);
    angleAnimator = new PerlinAnimator(speedMultiplierAngle);
}

Camera::Camera(sf::RenderWindow *window, float x, float y)
    : window_(window), orig_center({x, y}), current_center({x, y})
{
    camera_ = window_->getView();
    orig_center = camera_.getCenter();
    orig_rotation = camera_.getRotation();
    xPosAnimator = new PerlinAnimator(speedMultiplierX);
    yPosAnimator = new PerlinAnimator(speedMultiplierY);
    angleAnimator = new PerlinAnimator(speedMultiplierAngle);
}

Camera::~Camera()
{
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
        trauma = trauma - recoveryRate * (GameTime::getInstance().getDeltaTime() / DEFAULT_FRAME_DURATION);
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
        float angle = maxAngleOffset * shake * angleAnimator->update(false);
        float x = maxPixelOffset * shake * xPosAnimator->update(false);
        float y = maxPixelOffset * shake * yPosAnimator->update(false);
        
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
    if (amount < 0.01f)
        recoveryRate = 0.01f;
    else
        recoveryRate = amount;
}

void Camera::setSpeedMulitplierX(double amount)
{
    if (amount < 0.1)
        speedMultiplierX = 0.1;
    else
        speedMultiplierX = amount;
}

void setSpeedMultiplierY(double amount)
{
    if (amount < 0.1)
        speedMultiplierY = 0.1;
    else
        speedMultiplierY = amount;
}

void setSpeedMultiplierAngle(double amount)
{
    if (amount < 0.1)
        speedMultiplierAngle = 0.1;
    else
        speedMultiplierAngle = amount;
}