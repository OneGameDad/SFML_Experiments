#include "Terrain.h"

Terrain::Terrain(Game* pGame, sf::Texture *a_texture)
    : Rectangle(sf::Vector2f{terrainWidth, terrainHeight}, startPos), m_pGame(pGame)
{
    m_sprite.setTexture(*a_texture);
    m_sprite.setScale({2.5f, 0.5f});
    m_sprite.setColor(sf::Color::Green);
}

Terrain::~Terrain(){}

void    Terrain::update(float deltaTime)
{
    if (state == INVIS)
        return;
    else if (state == VISIBLE)
    {
        lifetime -= deltaTime;
        updateCollisions();
        updateMovement(deltaTime);
        if (lifetime <= 0.0f)
        {
            deactivate();
        }
    }
}


void    Terrain::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (state == VISIBLE)
    {
        target.draw(m_sprite, states);   
    }
}

void    Terrain::activate(sf::Vector2f a_position, float a_lifetime, float a_speed, float a_angle)
{
    reset();
    setPosition(a_position);
    m_sprite.setPosition(getPosition());
    lifetime = a_lifetime;
    speed = a_speed;
    angle = a_angle;
    state = VISIBLE;
}

void    Terrain::deactivate()
{
    state = INVIS;
}

void    Terrain::reset()
{
    state = INVIS;
    lifetime = 0.0f;
    health = 0.0f;
    speed = 0.0f;
    angle = 0.0f;
    sf::Vector2f startPos = {0.0f, 0.0f};
}

void    Terrain::updateMovement(float deltaTime)
{
    float radians = angle * PI / 180.f;
    float dx = speed * std::cos(radians) * deltaTime;
    float dy = speed * std::sin(radians) * deltaTime;
    Rectangle::move(sf::Vector2f(dx, dy));
    m_sprite.setPosition(getPosition().x, getPosition().y);
}

void    Terrain::updateCollisions()
{
    for (auto& box: *m_pGame->getBoundingBoxes())
    {
        if (collidesWith(box.get()))
        {
            deactivate();
            return;
        }
    }
}