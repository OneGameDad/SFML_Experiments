#include "AProjectile.h"

AProjectile::AProjectile(sf:.Vector2f a_size sf::Vector2f a_position, sf::Font* pFont)
    : Rectangle(a_size, a_position), m_collisionEffect(std::make_unique<ProjectileTextBox>(pFont, this, END_EFFECT_DURATION))
{}

AProjectile::~AProjectile(){}

