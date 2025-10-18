#include "GameState.hpp"

static GameState &GameState::getInstance()
{
    static GameState instance;
    return (instance);
}
