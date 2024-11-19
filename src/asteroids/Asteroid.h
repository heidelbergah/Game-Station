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

    sf::Sprite sprite;
    float radius;
    float angle;
    sf::Vector2f pos;
    sf::Vector2f vel;
    int totalVelocity;
    // Level 1 is the largest of the asteroids, with each level higher being
    // smaller, and more splitting from them.
    int level;

    float radiansToAdjustedDegrees(float radians);

    void wrapAroundScreen();
public:
    Asteroid(int w, int h, int pi, int l);

    void updatePosition();

    void setPos(sf::Vector2f p);

    sf::Vector2f getPos() const;

    float getRadius() const;

    int getLevel() const;

    void setTexture(sf::Texture& text, sf::IntRect ir);
    
    sf::Sprite getSprite() const;
};

#endif
