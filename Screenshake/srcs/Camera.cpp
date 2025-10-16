#include "Camera.hpp"

Camera::Camera(sf::Clock *clock, sf::RenderWindow *window)
    : window_(window), clock_(clock)
{
    camera_ = window_->getView();
}

Camera::Camera(sf::Clock *clock, sf::RenderWindow *window, float x, float y, float w, float h, float zoom)
    : window_(window), clock_(clock), orig_center({x, y}), current_center({x, y}), orig_size({w, h}), current_size({w, h}), orig_zoom(zoom), current_zoom(zoom)
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

void Camera::setPosition(float x, float y, float w, float h)
{
    orig_center = {x, y};
    orig_size = {w, h};
}

void Camera::setZoom(float zoom)
{
    orig_zoom = zoom;
    current_zoom = zoom;
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
        current_size = orig_size;
        current_zoom = orig_zoom;
        current_rotation = orig_rotation;
        current_frame = 0;
    }
    else
    {
        current_center = ;
        current_size = ;
        current_zoom = ;
        current_rotation = ;
    }
    camera_.move(current_center);
    camera_.setSize(current_size);
    camera_.zoom(current_zoom);
    window_->setView(camera_);
}
/*
angle = maxAngle * shake * GetPerlinNoise(seed, time, ...);
offsetX = maxOffset * shake * GetPerlinNoise(seed + 1, time, ...);
offsetY = maxOffset * shake * GetPerlinNoise(seed + 2, time, ...);

shakyCamera.angle = camera.angle + angle;
shakyCamera.center = camera.center + Vec2(offsetx, offsetY);
*/
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