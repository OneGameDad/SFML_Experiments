#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <cstdlib>
#include <iostream>
#include "PerlinNoiseGenerator.h"
#include "APropertyAnimator.h"
#include "PerlinAnimator.h"
#include "Tweener.h"
#include "LinearAnimator.h"
#include <cmath>
#include <vector>
#include <memory>
#include "Game.h"
#include "InputHandler.h"

#define DECAY_POWER             2.0
#define DEFAULT_FRAME_DURATION  1.0/60.0

class Game;

class Camera
{
private:
    Game*   m_pGame;
    sf::RenderWindow    *window_;
    sf::View    camera_;
    sf::Vector2f    orig_center = {0.0f, 0.0f};
    sf::Vector2f    current_center = {0.0f, 0.0f};
    sf::Vector2f    orig_size = {100.0f, 100.0f};
    sf::Vector2f    current_size = {100.0f, 100.0f};
    float   orig_rotation = 0.0f;
    float   current_rotation = 0.0f;

    float   trauma = 0.0f;
    float   maxTrauma = 10.0f;
    float   moreTraumaPlease = 1.5f;
    float   traumaBuffer = 0.1f;
    float   recoveryDuration =  (DEFAULT_FRAME_DURATION / 0.6f);

    bool    isShaking = false;
    float   maxAngleOffset = 90.0f;
    float   maxPixelOffset = 100.0f;
    double  speedMultiplierX = 100.0;
    double  speedMultiplierY = 100.0;
    double  speedMultiplierAngle = 100.0;

    std::unique_ptr<APropertyAnimator>  xPosAnimator;
    std::unique_ptr<APropertyAnimator>  yPosAnimator;
    std::unique_ptr<APropertyAnimator>   angleAnimator;
    std::unique_ptr<Tweener> tweener;

    bool    shakeRequested = false;

    void    cameraShake();
    void    animateScreenShake();
    void    recover();
    void    updateTweener();

public:
    Camera(Game* pGame);
    ~Camera();

    void initialize(sf::RenderWindow& window);
    void update();
    void setPosition(float x, float y);
    void beginCameraShake();
    void requestShake();
    void addTrauma(float amount);
    void setRecoveryDuration(float amount);
    void setSpeedMulitplierX(double amount);
    void setSpeedMultiplierY(double amount);
    void setSpeedMultiplierAngle(double amount);
};