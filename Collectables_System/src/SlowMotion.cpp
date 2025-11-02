#include "SlowMotion.h"

SlowMotion::SlowMotion(Game* pGame)
    : m_pGame(pGame), clock(*GameTime::getInstance())
{}

SlowMotion::~SlowMotion(){}

void    SlowMotion::reset()
{
    if (clock->getTimeScale() != regularTime || isActive == true)
    {    
        clock->setTimeScale(regularTime);
        isActive = false;
    }
}

void    SlowMotion::activate()
{
    if (clock->getTimeScale() != slowTime || isActive == false)
    {
        clock->setTimeScale(slowTime);
        isActive = true;
    }
}

void    SlowMotion::deactivate()
{
    reset();
}

void    SlowMotion::update()
{
    if (isActive)
    {
        elapsed += clock->getDeltaTimeUnscaled();
        if (elapsed >= duration)
        {
            reset();
            elapsed = 0.0f;
        }
    }
}