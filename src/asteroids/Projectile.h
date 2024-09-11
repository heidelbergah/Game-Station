#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include <cmath>

class Projectile
{
private:
    sf::CircleShape shape;
    sf::Color color;

    sf::Vector2f pos;
    float radius;
    float angle;
    int velocity;

public:
    Projectile(sf::Vector2f pos, float angle, sf::Color color);

    void updatePosition();

    bool outOfBounds();

    sf::Vector2f getPos() const;

    float getRadius() const;

    sf::CircleShape getShape() const;
};

#endif
