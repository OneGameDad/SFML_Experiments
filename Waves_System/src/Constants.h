#pragma once

const int ScreenWidth = 800;
const int ScreenHeight = 600;

const float PlayerHeight = 55.0f;
const float PlayerWidth = 55.0f;
const float PlayerSpeed = 155.0f;

const float VampireHeight = 32.0f;
const float VampireWidth = 32.0f;
const float VampireSpeed = 100.0f;

const float WeaponHeight = 10.0f;
const float WeaponWidth = 100.0f;
const float WeaponActiveTime = 0.25f;

const float WorldScrollingSpeed = 155.0f;
const float END_EFFECT_DURATION = 0.25f;
const float  PI = 3.14159265f;
const float  AFTER_TIME = 3.5f;
const float DYING_TIME = 3.5f;

const float COOLDOWN = 3.5f;

enum e_coll_states
{
    WAITING,
    PLACED,
    COLLECTED
};

enum e_coll_types
{
    HEALING,
    ENERGIZING
};

enum e_enem_states
{
    DISABLED,
    INITIATING,
    ENABLED,
    DEAD,
    BEYOND
};

enum e_proj_states
{
    INACTIVE,
    SPAWNING,
    FLYING,
    RICHOCETING,
    DYING,
};

enum e_terr_states
{
    INVIS,
    VISIBLE
};

enum eDirection
{
    LEFT,
    RIGHT
};

enum e_collidable
{
    RECT,
    PLAYER,
    ENEMY,
    PROJECTILE,
    COLLECTIBLE,
    TERRAIN,
    OTHER
};