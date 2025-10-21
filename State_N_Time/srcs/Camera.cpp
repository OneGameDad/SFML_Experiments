#include "Camera.hpp"

Camera::Camera(sf::RenderWindow *window)
    : window_(window), shakeRequested(false)
{
    camera_ = window_->getView();
    orig_center = camera_.getCenter();
    orig_rotation = camera_.getRotation();
    xPosAnimator = new PerlinAnimator(speedMultiplierX, false);
    yPosAnimator = new PerlinAnimator(speedMultiplierY, false);
    angleAnimator = new PerlinAnimator(speedMultiplierAngle, false);
}

Camera::Camera(sf::RenderWindow *window, float x, float y)
    : window_(window), orig_center({x, y}), current_center({x, y}), shakeRequested(false)
{
    camera_ = window_->getView();
    orig_center = camera_.getCenter();
    orig_rotation = camera_.getRotation();
    xPosAnimator = new PerlinAnimator(speedMultiplierX, false);
    yPosAnimator = new PerlinAnimator(speedMultiplierY, false);
    angleAnimator = new PerlinAnimator(speedMultiplierAngle, false);
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
    if (shakeRequested /*|| sf::Keyboard::Space*/)
    {
       beginCameraShake();
       shakeRequested =  false;
    }
    if (isShaking)
    {
        cameraShake();
    }
    recover();
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
    {
        isShaking = true;
        std::cout << "Camera is Shaking\n";
    }
}

void Camera::requestShake()
{
    if (!shakeRequested)
    {
        shakeRequested = true;
        std::cout << "Camera Shake Requested\n";
    }
}

void Camera::cameraShake()
{
    if (trauma <= traumaBuffer)
    {
        isShaking = false;
        std::cout << "Camera is NOT shaking\n";
        current_center = orig_center;
        current_rotation = orig_rotation;
    }
    else
    {
        float shake = trauma * trauma; // Currently trauma^2, could try trauma^3
        float angle = maxAngleOffset * shake * angleAnimator->update();
        float x = maxPixelOffset * shake * xPosAnimator->update();
        float y = maxPixelOffset * shake * yPosAnimator->update();
        
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

void Camera::setSpeedMultiplierY(double amount)
{
    if (amount < 0.1)
        speedMultiplierY = 0.1;
    else
        speedMultiplierY = amount;
}

void Camera::setSpeedMultiplierAngle(double amount)
{
    if (amount < 0.1)
        speedMultiplierAngle = 0.1;
    else
        speedMultiplierAngle = amount;
}

void Camera::recover()
{
    if (trauma > traumaBuffer)
    {
        trauma -= recoveryRate * (GameTime::getInstance().getCurrentTime() / DEFAULT_FRAME_DURATION);
        if (trauma < 0.0f)
            trauma = 0.0f;
        std::cout << "Trauma Level: " << trauma << std::endl;
    }
    if (trauma <= traumaBuffer)
        trauma = 0.0f;
}