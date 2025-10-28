#include "AProjectile.h"

AProjectile::AProjectile(Game* pGame)
    : Rectangle(sf::Vector2f{projWidth, projHeight}, startPos), m_pGame(pGame), m_collisionEffect(std::make_unique<ProjectileTextBox>(m_pGame->getFont(), this, END_EFFECT_DURATION))
{}

AProjectile::~AProjectile(){}

