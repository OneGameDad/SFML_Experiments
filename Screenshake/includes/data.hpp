#pragma once

#include <SFML/System/Clock.hpp>

typedef struct s_data
{
    double startTime = 0.0;
    double currentTime = 0.0;
    double lastTime = 0.0;
    double deltaTime = 0.0;

    void    setTime(sf::Clock *clock)
    {
        startTime = static_cast<double>(clock->restart().asMicroseconds()) / 1000000.0;
        currentTime = startTime;
        lastTime = startTime;
    };

    void   updateTime(sf::Clock *clock)
    {
        currentTime = static_cast<double>(clock->getElapsedTime().asMicroseconds()) / 1000000.0;
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
    };
}   t_data;

extern t_data g_data;