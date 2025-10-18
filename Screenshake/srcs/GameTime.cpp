#include "GameTime.hpp"

static GameTime &GameTime::getInstance()
{
    static GameTime instance;
    return (instance); 
}

void    GameTime::setTime()
{
    startTime = static_cast<double>(frameClock->restart().asSeconds());
    currentTimeUnscaled = startTime;
    deltaTimeUnscaled = startTime;
    deltaTime = startTime;
    currentTime = startTime;
};

void   GameTime::updateTime()
{
    deltaTimeUnscaled = static_cast<double>(frameClock->restart().asSeconds());
    currentTimeUnscaled += deltaTimeUnscaled;
    deltaTime = deltaTimeUnscaled * timeScale;
    currentTime += deltaTime;
};

//Setters
void GameTime::setTimeScale(double t)
{
    timeScale = t;
}

//Getters
double GameTime::getCurrentTime() const { return (currentTime); }
double GameTime::getCurrrentTimeUnscaled() const { return (currentTimeUnscaled); }
double GameTime::getDeltaTime() const { return (deltaTime); }
double GameTime::getDeltaTimeUnscaled() const { return (deltaTimeUnscaled); }
double GameTime::getStartTime() const { return (startTime); }
double GameTime::getTimeScale() const { return (timeScale); }
sf::Clock* GameTime::getFrameClock() const { return (frameClock); }
float GameTime::getRealTime() { return (realTimeClock.getElapsedTime().asSeconds()); }