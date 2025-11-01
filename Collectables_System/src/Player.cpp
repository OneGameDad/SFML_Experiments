#include "Player.h"


Player::Player(Game* pGame, sf::Font& pFont) :
    Rectangle(sf::Vector2f(PlayerWidth, PlayerHeight)),
    m_pGame(pGame),
    m_pWeapon(std::make_unique<Weapon>()),
    m_pWeaponEffect(std::make_unique<WeaponTextBox>(pFont, this))
{
    setOrigin(sf::Vector2f(0.0f, 0.0f));
}

Player::~Player() = default;

bool Player::initialise()
{
    m_sprite.setTexture(*m_pGame->getPlayerTexture());
    m_sprite.setScale(3.5f, 3.5f);
    setIsDead(false);
    setPosition(ScreenWidth / 2, ScreenHeight / 2);
    m_sprite.setPosition(getPosition());
    currentHealth = maxHealth;
    m_pWeaponEffect->initialize();
    m_pWeaponEffect->setDuration(WeaponActiveTime);
    m_pWeaponEffect->setString("*swish*");
    m_pWeaponEffect->setTextOffsets(0.0f, -15.0f);
    return true;
}

void Player::move(InputData inputData, float deltaTime)
{
    float xSpeed = 0.0f;
    float ySpeed = 0.0f;
    
    xSpeed -= inputData.m_movingLeft * PlayerSpeed;
    xSpeed += inputData.m_movingRight * PlayerSpeed;
    xSpeed *= deltaTime;

    ySpeed -= inputData.m_movingUp * PlayerSpeed;
    ySpeed += inputData.m_movingDown * PlayerSpeed;
    ySpeed *= deltaTime;
    
    sf::Transformable::move(sf::Vector2f(xSpeed, ySpeed));
    setPosition(std::clamp(getPosition().x, 0.0f, (float)ScreenWidth), getPosition().y);

    if (m_pWeapon->isActive() == false)
    {
        if (inputData.m_movingLeft == true && inputData.m_movingRight == false)
            m_direction = LEFT;
        else if (inputData.m_movingLeft == false && inputData.m_movingRight == true)
            m_direction = RIGHT;
    }
}

void Player::attack()
{
    m_pWeapon->setActive(true);
    m_pWeaponEffect->activate();
}

void Player::update(float deltaTime)
{
    sf::Vector2f weaponSize = m_pWeapon->getSize();

    m_sprite.setPosition(getPosition());
    m_pWeapon->setPosition(sf::Vector2f(
        getCenter().x - (m_direction == LEFT ? weaponSize.x : 0.0f),
        getCenter().y - weaponSize.y / 2.0f));
    m_pWeapon->update(deltaTime);
    m_pWeaponEffect->update(deltaTime);
    updateGun(deltaTime);
}    

void Player::updateGun(float deltaTime)
{
    if (firedProjectile)
    {
        elapsed += deltaTime;
        if (elapsed >= fireCooldown)
        {
            firedProjectile =  false;
            elapsed = 0.0f;
        }
    }
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    Rectangle::draw(target, states);
    m_pWeapon->draw(target, states);
    if (m_pWeapon->isActive())
        m_pWeaponEffect->draw(target, states);
}

float Player::getNormalizedHealth() const
{
    float normalized = currentHealth / maxHealth;
    return (normalized);
}

sf::Sprite Player::getSprite() const { return (m_sprite); }

void Player::fire()
{
    if (firedProjectile)
        return;
    float a_lifetime = 5.0f;
    float a_speed = 20.0f;
    float a_angle = 0.0f;
    sf::Vector2f a_position;
    if (m_direction == LEFT)
    {
        a_position.x = getPosition().x + -10;
        a_position.y = getPosition().y + 50;
        a_angle = 180.0f;
    }
    else
    {
        auto textureSize = m_sprite.getTexture()->getSize();
        sf::Vector2f spriteSize = {static_cast<float>(textureSize.x), static_cast<float>(textureSize.y)};
        a_position.x = getPosition().x + static_cast<float>(spriteSize.x) + 10;
        a_position.y = getPosition().y + 50;
    }
    m_pGame->getProjectileManager().spawn(a_position, a_lifetime, a_speed, a_angle);
    firedProjectile = true;
}

void Player::addXP(size_t num)
{
    experiencePoints += num;
    std::cout << "XP Total: " << experiencePoints << std::endl;
}