#include "Player.h"


Player::Player(Game* pGame, sf::Font& pFont) :
    Rectangle(sf::Vector2f(PlayerWidth, PlayerHeight)),
    m_pGame(pGame)
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
    currentEnergy = 5.0f;
    currentHealth = 100.0f;
    return true;
}

void Player::move(InputData inputData, float deltaTimeUnscaled)
{
    float xSpeed = 0.0f;
    float ySpeed = 0.0f;
    
    if (onGround)
    {
        ySpeed = 0.0f;
    }
    else
    {
        ySpeed += gravity * deltaTimeUnscaled;
        if (inputData.m_movingDown)
        {
            ySpeed += dropBoost * deltaTimeUnscaled;
        }
    }

    if (inputData.m_jumpKeyReleasedInThisFrame)
    {
        ySpeed = maxYSpeed;
    }

    sf::Transformable::move(sf::Vector2f(xSpeed, ySpeed));

    sf::Vector2u cameraSize = m_pGame->getCamera()->getSize();
    float xPos = std::clamp(getPosition().x, 0.0f, (float)cameraSize.x);
    float yPos = std::clamp(getPosition().y, 0.0f, (float)cameraSize.y);
    setPosition(xPos, yPos);
}

void Player::update(float deltaTimeUnscaled)
{
    setOffGround();
    updateCollisions();
    m_sprite.setPosition(getPosition());
    updateGun(deltaTimeUnscaled);
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
}

float Player::getNormalizedHealth() const
{
    float normalized = currentHealth / maxHealth;
    return (normalized);
}

sf::Sprite Player::getSprite() const { return (m_sprite); }

void Player::fire()
{
    if (firedProjectile || currentEnergy == 0)
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
    currentEnergy -= 1.0f;
    firedProjectile = true;
}

void Player::addEnergy(size_t num)
{
    if (currentEnergy < maxEnergy)
    {
        currentEnergy += num;
        std::cout << "Energy Added, Total: " << currentEnergy << std::endl;
    }
}

float Player::getNormalizedEnergy() const
{
    float normalized = currentEnergy / maxEnergy;
    return (normalized);
}

void Player::takeDamage(float num)
{
    currentHealth -= num;
    if (currentHealth <= 0.0f)
        setIsDead(true);
}

void Player::drainEnergy()
{
    float energyDelta = -slowMotionEnergyCostPerSecond * GameTime::getInstance().getDeltaTimeUnscaled();
    currentEnergy = std::max(0.0f, currentEnergy + energyDelta);
}

void Player:: heal(float num)
{
    if (currentHealth + num > maxHealth)
        currentHealth = maxHealth;
    else
        currentHealth += num;
}

void Player::updateCollisions()
{
    TerrainManager& terrPool = m_pGame->getTerrainManager();
    for (auto& terrain: terrPool.getPool())
    {
        if (collidesWith(terrain.get()))
        {
            setOnGround();
            return;
        }
        else
            setOffGround();       
    }
    for (auto& box: *m_pGame->getBoundingBoxes())
    {
        if (collidesWith(box.get()))
        {
            setIsDead(true);
        }
    }
}

void Player::setOnGround()
{
    if (!onGround)
        onGround = true;
}

void Player::setOffGround()
{
    if (onGround)
        onGround = false;
}