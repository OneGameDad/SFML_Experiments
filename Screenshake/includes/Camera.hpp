#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <cstdlib>
#include <iostream>
#include "MathUtils.hpp"
#include "BitmapReader.hpp"

class Camera
{
private:
    sf::RenderWindow *window_;
    sf::Clock *clock_;
    sf::View camera_;
    sf::Vector2f orig_center = {0.0f, 0.0f};
    sf::Vector2f current_center = {0.0f, 0.0f};
    sf::Vector2f orig_size = {100.0f, 100.0f};
    sf::Vector2f current_size = {100.0f, 100.0f};
    float orig_rotation = 0.0f;
    float current_rotation = 0.0f;

    float trauma = 0.0f;
    float recoveryRate = 0.1f;

    bool isShaking = false;
    constexpr static int32_t MILLISECONDS_PER_FRAME = 333;
    int32_t nextAnimationTime = 0;
    size_t max_frames = 120;
    size_t current_frame = 0;
    float maxAngle = 20.0f;
    float maxOffset = 30.0f;

    sf::Vector2f perlinX = {0.0f, 0.0f};
    sf::Vector2f perlinY = {0.0f, 0.0f};
    float pixelJumpValue = 4.0f;

    void cameraShake();
    sf::Vector2f getRandomPerlinCoord();
    sf::Vector2f iteratePerlinCoord();
public:
    Camera(sf::Clock *clock, sf::RenderWindow *window);
    Camera(sf::Clock *clock, sf::RenderWindow *window, float x, float y);
    ~Camera();

    void Update();
    void setPosition(float x, float y);
    void setMaxFrames(size_t frames);
    void setIsShaking();
    void addTrauma(float amount);
    void setRecoveryRate(float amount);
};