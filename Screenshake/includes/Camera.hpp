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
#include "data.hpp"

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
    float traumaBuffer = 0.1f;
    float recoveryRate = 0.05f;
    float tNoiseOffsetX = 0.0f;
    float tNoiseOffsetY = 0.0f;
    float tNoiseOffsetAngle = 0.0f;
    float noiseImgWidth = 0.0f;
    float noiseImgHeight = 0.0f;

    bool isShaking = false;
    float maxAngleOffset = 20.0f;
    float maxPixelOffset = 30.0f;

    sf::Vector2f perlinX = {0.0f, 0.0f};
    sf::Vector2f perlinY = {0.0f, 0.0f};
    double speedMultiplierX = 1.0;
    double speedMultiplierY = 1.5;
    double speedMultiplierAngle = 2.0;

    void cameraShake();
    void animateScreenShake();
    sf::Vector2f getRandomPerlinCoord();
    void savePerlinImageSize();
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