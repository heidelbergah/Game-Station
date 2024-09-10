#ifndef ASTEROID_H
#define ASTEROID_H

#include "SFML/Graphics.hpp"
#include <cmath>
#include <random>

class Asteroid
{
private:
    float PI;
    int windowWidth;
    int windowHeight;

    sf::CircleShape shape;
    sf::Sprite sprite;
    float radius;
    float angle;
    sf::Vector2f pos;
    sf::Vector2f vel;
    int totalVelocity;

    float radiansToAdjustedDegrees(float radians);

    void wrapAroundScreen();
public:
    Asteroid(int w, int h, int pi);

    void updateVelocity();

    void updatePosition();

    sf::CircleShape getShape() const;
};

#endif
