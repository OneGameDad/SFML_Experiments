#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <functional>
#include "GameTime.h"

struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    float lifetime;
    float rotation;
    float rotationSpeed;
    float currentScale;
    sf::Color currentColor;
};

struct Emitter {
    sf::Vector2f localPosition;      // local offset relative to system or target
    sf::Vector2f velocity;           // optional local velocity
    std::function<sf::Vector2f()> targetFunc; // optional dynamic target

    Emitter(const sf::Vector2f& pos = {0.f, 0.f},
            const sf::Vector2f& vel = {0.f, 0.f},
            std::function<sf::Vector2f()> target = nullptr)
        : localPosition(pos), velocity(vel), targetFunc(target) {}

    // Update the local position (for velocity or target tracking)
    void update(float dt) {
        if (targetFunc) {
            // Track target; localPosition is set relative to target
            localPosition = targetFunc();
        } else {
            // Move by velocity (local space)
            localPosition += velocity * dt;
        }
    }

    // Return **world position**, combining systemTransform and localPosition
    sf::Vector2f getWorldPosition(const sf::Transform& systemTransform) const {
        return systemTransform.transformPoint(localPosition);
    }
};

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
protected:
    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    const sf::Texture& m_texture;
    float m_defaultLifetime;

    std::vector<Emitter> m_emitters; // multiple local emitter points

    void   applyGravity(Particle& p, float dt);
    void   applyRotation(Particle& p, float dt);
    void   applyScaling(Particle& p);
    void   applyColorVariation(Particle& p);
    void   updateQuad(std::size_t index, const sf::Vector2f& position, const sf::Color& color, float scale, float rotation);
    virtual void    resetParticle(Particle& p);
    virtual void    updateParticle(Particle& p) = 0;
    virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    ParticleSystem(size_t count, const sf::Texture& texture);
    virtual ~ParticleSystem() = default;

    void update();
    void addEmitter(const sf::Vector2f& localPosition);
    void clearEmitters();
    const std::vector<Emitter>& getEmitters() const;
    std::vector<Emitter>& getEmitters();

};
