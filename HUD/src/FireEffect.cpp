#include "FireEffect.h"

FireEffect::FireEffect(size_t count, const sf::Texture& texture) : ParticleSystem(count, texture){}

void FireEffect::resetParticle(Particle& p)
{
    // p.position is already at emitter’s world position
    sf::Vector2f emitterPos = p.position;

    // Randomize around the emitter
    float offsetX = (rand() % 20 - 10) / 10.f;
    float offsetY = (rand() % 10) / 10.f;

    p.position = emitterPos + sf::Vector2f(offsetX, offsetY);

    // Velocity
    float vx = (rand() % 20 - 10) / 10.f;
    float vy = -(rand() % 50) / 10.f;

    p.velocity = sf::Vector2f(vx, vy);

    // Lifetime, scale, rotation
    p.lifetime = 1.f + static_cast<float>(rand() % 50) / 50.f;
    p.currentScale = 0.5f + static_cast<float>(rand() % 50) / 100.f;
    p.rotation = static_cast<float>(rand() % 360);
    p.rotationSpeed = rand() % 100 - 50;
    p.currentColor = sf::Color::Yellow;
}


// Update particle behavior per frame
void FireEffect::updateParticle(Particle& p)
{
    float dt = GameTime::getInstance().getDeltaTime();
    // Rising effect
    p.velocity.y -= 20.f * dt; // accelerate upward

    // Fade out based on lifetime
    float alpha = std::max(0.f, p.lifetime); // simple fade
    p.currentColor.a = static_cast<sf::Uint8>(255.f * alpha);

    // Slight expansion over lifetime
    p.currentScale += dt * 0.2f;

    // Rotation
    p.rotation += p.rotationSpeed * dt;
}

