#pragma once

#include <SFML/System/Clock.hpp>

class GameTime
{
private:
    sf::Clock frameClock;
    sf::Clock realTimeClock;
    double startTime = 0.0;
    double currentTime = 0.0;
    double currentTimeUnscaled = 0.0;
    double deltaTime = 0.0;
    double deltaTimeUnscaled = 0.0f;
    double timeScale = 0.0;

    GameTime() = default;
public:
    GameTime(const GameTime &copy) = delete;
    GameTime &operator=(const GameTime &copy) = delete;
    static GameTime &getInstance();

    void   setTime();
    void   updateTime();
    void    setTimeScale(double t);

    double getStartTime() const;
    double getCurrentTime() const;
    double getCurrrentTimeUnscaled() const;
    double getDeltaTime() const;
    double getDeltaTimeUnscaled() const;
    double getTimeScale() const;
    sf::Clock* getFrameClock() const;
    float getRealTime();
};