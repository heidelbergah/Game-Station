#include "Projectile.h"

Projectile::Projectile(sf::Vector2f pos, float angle, sf::Color color)
{
    this->pos = pos;
    this->angle = angle;
    this->color = color;

    velocity = 7;
    radius = 2;

    shape.setFillColor(color);
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(pos);
}

void Projectile::updatePosition()
{
    pos.x += cos(angle) * velocity;
    pos.y += sin(angle) * velocity;

    shape.setPosition(pos);
}

sf::Vector2f Projectile::getPos() const
{
    return pos;
}

float Projectile::getRadius() const
{
    return radius;
}

sf::CircleShape Projectile::getShape() const
{
    return shape;
}

