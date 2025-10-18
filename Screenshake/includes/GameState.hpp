#pragma once


class GameState
{
private:
    
    GameState() = default;
public:
    GameState(const GameState &copy) = delete;
    GameState &operator=(const GameState &copy) = delete;
    static GameState &getInstance();

};