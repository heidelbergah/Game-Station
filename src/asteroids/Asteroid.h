#ifndef ASTEROID_H
#define ASTEROID_H

#include "SFML/Graphics.hpp"

struct Asteroid
{
    sf::CircleShape shape;
    sf::Sprite sprite;
    float radius;
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::Vector2f acc;
};

#endif
