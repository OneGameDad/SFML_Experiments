#include "Player.hpp"

Player::Player(Game* pGame) 
    : m_pGame(pGame), Rectangle({250.0f, 250.0f})
{
    setOrigin({0.0f, 0.0f});
}

bool Player::initialize()
{
    texture.loadFromFile("images/player.png");
    m_sprite.setTexture(texture);
    m_sprite.setScale(3.5f, 3.5f);
    setPosition(ScreenWidth / 2, ScreenHeight / 2);
    m_sprite.setPosition(getPosition());
    std::cout << "Player Position: " << getPosition().x << ", " << getPosition().y << std::endl;
    return true;
}

void Player::update(float deltaTime)
{
    (void)deltaTime;
    m_sprite.setPosition(getPosition());
//    std::cout << "Player Position: " << getPosition().x << ", " << getPosition().y << std::endl;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    (void)states;
    target.draw(m_sprite);
}

float Player::getNormalizedHealth() const
{
    float normalized = currentHealth / maxHealth;
    return (normalized);
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
//    std::cout << "Player Position: " << getPosition().x << ", " << getPosition().y << std::endl;
/*    if (m_pWeapon->isActive() == false)
    {
        if (inputData.m_movingLeft == true && inputData.m_movingRight == false)
            m_direction = LEFT;
        else if (inputData.m_movingLeft == false && inputData.m_movingRight == true)
            m_direction = RIGHT;
    }*/
}

sf::Sprite Player::getSprite() const { return (m_sprite); }