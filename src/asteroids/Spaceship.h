#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "SFML/Graphics.hpp"

struct Spaceship
{
    sf::CircleShape shape;
    sf::Sprite sprite;
    sf::Color color;
    float radius;

    float angle;
    float acceleration;
    float max_velocity;
    sf::Vector2f vel;
    sf::Vector2f pos;

    bool thrusting;
    bool canShoot;
};

#endif
