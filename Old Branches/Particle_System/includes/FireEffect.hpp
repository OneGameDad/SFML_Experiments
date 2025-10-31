#pragma once

#include "ParticleSystem.hpp"
#include "GameTime.hpp"
#include <cstdint>
#include <SFML/Graphics.hpp>

class FireEffect : public ParticleSystem
{
protected:
    void resetParticle(Particle& p) override;
    void updateParticle(Particle& p);
public:
    FireEffect(size_t count, const sf::Texture& texture);
};