#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(size_t count, const sf::Texture& texture)
    : m_particles(count), m_vertices(sf::Quads, count * 4), m_texture(texture), m_defaultLifetime(2.0f)
{
    // Add one default emitter at (0, 0)
    m_emitters.push_back(Emitter({0.f, 0.f}));
    for (auto& p : m_particles)
        resetParticle(p);
}

void ParticleSystem::update()
{
    float dt = GameTime::getInstance().getDeltaTime();

    // --- Update all emitters ---
    for (auto& emitter : m_emitters)
        emitter.update(dt);

    // --- Update all particles ---
    for (std::size_t i = 0; i < m_particles.size(); ++i) {
        Particle& p = m_particles[i];
        p.lifetime -= dt;

        if (p.lifetime <= 0.f)
            resetParticle(p);

        applyGravity(p, dt);
        applyRotation(p, dt);
        applyScaling(p);
        applyColorVariation(p);
        p.position += p.velocity * dt;

        updateQuad(i, p.position, p.currentColor, p.currentScale, p.rotation);
    }
}

void ParticleSystem::resetParticle(Particle& p)
{
    if (m_emitters.empty())
        m_emitters.emplace_back(sf::Vector2f{0.f, 0.f});

    // Choose a random emitter
    std::size_t i = std::rand() % m_emitters.size();
    sf::Vector2f emitterWorld = m_emitters[i].getWorldPosition(getTransform());

    float angle = (std::rand() % 360) * 3.14159f / 180.f;
    float speed = 50.f + (std::rand() % 100);

    p.position = emitterWorld;
    p.velocity = {std::cos(angle) * speed, std::sin(angle) * speed};
    p.lifetime = m_defaultLifetime;
    p.rotation = static_cast<float>(std::rand() % 360);
    p.rotationSpeed = (std::rand() % 200 - 100);
    p.currentScale = 1.f;
    p.currentColor = sf::Color::White;
}

void ParticleSystem::updateQuad(std::size_t index, const sf::Vector2f& position, const sf::Color& color, float scale, float rotation)
{
    // Each particle has 4 vertices (quad)
    sf::Vertex* quad = &m_vertices[index * 4];

    // Get the texture size (assumes full texture for particle)
    sf::Vector2u texSize = m_texture.getSize();
    float halfWidth = (texSize.x * scale) / 2.f;
    float halfHeight = (texSize.y * scale) / 2.f;

    // Define corners relative to particle center
    sf::Vector2f topLeft(-halfWidth, -halfHeight);
    sf::Vector2f topRight(halfWidth, -halfHeight);
    sf::Vector2f bottomRight(halfWidth, halfHeight);
    sf::Vector2f bottomLeft(-halfWidth, halfHeight);

    // Precompute rotation
    float rad = rotation * 3.14159265f / 180.f;
    float cosR = std::cos(rad);
    float sinR = std::sin(rad);

    auto rotate = [&](const sf::Vector2f& v) {
        return sf::Vector2f(v.x * cosR - v.y * sinR,
                            v.x * sinR + v.y * cosR);
    };

    // Assign transformed positions to the quad
    quad[0].position = position + rotate(topLeft);
    quad[1].position = position + rotate(topRight);
    quad[2].position = position + rotate(bottomRight);
    quad[3].position = position + rotate(bottomLeft);

    // Assign texture coordinates
    quad[0].texCoords = sf::Vector2f(0.f, 0.f);
    quad[1].texCoords = sf::Vector2f(static_cast<float>(texSize.x), 0.f);
    quad[2].texCoords = sf::Vector2f(static_cast<float>(texSize.x), static_cast<float>(texSize.y));
    quad[3].texCoords = sf::Vector2f(0.f, static_cast<float>(texSize.y));

    // Assign colors
    quad[0].color = color;
    quad[1].color = color;
    quad[2].color = color;
    quad[3].color = color;
}


void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_vertices, states);
}

void ParticleSystem::applyGravity(Particle& p, float dt) {
    // gravity constant (pixels per second squared)
    const float gravity = 200.f;
    // apply gravity to the y-component of velocity
    p.velocity.y += gravity * dt;
}

void ParticleSystem::applyRotation(Particle& p, float dt) {
    // rotationSpeed is in degrees per second
    p.rotation += p.rotationSpeed * dt;

    // Optional: keep rotation in [0,360) for readability
    if (p.rotation >= 360.f) p.rotation -= 360.f;
    else if (p.rotation < 0.f) p.rotation += 360.f;
}

void ParticleSystem::applyScaling(Particle& p)
{
    float lifeRatio = p.lifetime / m_defaultLifetime;
    lifeRatio = std::clamp(lifeRatio, 0.f, 1.f);
    p.currentScale = 0.5f + 0.5f * lifeRatio; // shrink to 50%
}

void ParticleSystem::applyColorVariation(Particle& p)
{
    float lifeRatio = p.lifetime / m_defaultLifetime;
    lifeRatio = std::clamp(lifeRatio, 0.f, 1.f);

    sf::Uint8 alpha = static_cast<sf::Uint8>(255 * lifeRatio);
    sf::Uint8 red   = static_cast<sf::Uint8>(200 + 55 * (1 - lifeRatio));
    sf::Uint8 green = static_cast<sf::Uint8>(100 + 155 * lifeRatio);
    sf::Uint8 blue  = 255;

    p.currentColor = sf::Color(red, green, blue, alpha);
}

void ParticleSystem::addEmitter(const sf::Vector2f& localPosition)
{
    m_emitters.push_back(localPosition);
}

void ParticleSystem::clearEmitters()
{
    m_emitters.clear();
}

const std::vector<Emitter>& ParticleSystem::getEmitters() const { return (m_emitters); }
std::vector<Emitter>& ParticleSystem::getEmitters() { return (m_emitters); }