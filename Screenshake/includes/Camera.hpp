#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <cstdlib>
#include <iostream>
#include "PerlinNoiseGenerator.hpp"
#include "data.hpp"
#include "PropertyAnimator.hpp"

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
    float maxTrauma = 10.0f;
    float moreTraumaPlease = 1.0f;
    float traumaBuffer = 0.1f;
    float recoveryRate = 0.1f;

    bool isShaking = false;
    float maxAngleOffset = 90.0f;
    float maxPixelOffset = 100.0f;
    double speedMultiplierX = 10.0;
    double speedMultiplierY = 15.0;
    double speedMultiplierAngle = 20.0;

    PropertyAnimator *xPosAnimator;
    PropertyAnimator *yPosAnimator;
    PropertyAnimator *angleAnimator;

    void cameraShake();
    void animateScreenShake();

public:
    Camera(sf::Clock *clock, sf::RenderWindow *window);
    Camera(sf::Clock *clock, sf::RenderWindow *window, float x, float y);
    ~Camera();

    void Update();
    void setPosition(float x, float y);
    void beginCameraShake();
    void addTrauma(float amount);
    void setRecoveryRate(float amount);
    
};