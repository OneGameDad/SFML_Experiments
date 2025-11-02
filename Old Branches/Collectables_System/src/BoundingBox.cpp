#include "BoundingBox.h"

BoundingBox::BoundingBox(sf::Vector2f a_size, sf::Vector2f a_position)
    : Rectangle(a_size)
{
    setSize(a_size);
    setPosition(a_position);
}

BoundingBox::~BoundingBox() {}