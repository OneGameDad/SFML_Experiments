#pragma once

#include "Rectangle.h"

class BoundingBox: public Rectangle
{
private:
    e_collidable collidable_type = RECT;
    
public:
    BoundingBox(sf::Vector2f a_size, sf::Vector2f a_position);
    ~BoundingBox();
};