#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "SFML/Graphics.hpp"
#include <cmath>

class Spaceship
{
private:
    float PI;
    int windowWidth;
    int windowHeight;
        
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
    
    float radiansToAdjustedDegrees(float radians);

    void wrapAroundScreen();

public:
    Spaceship(int w, int h, float pi, sf::Color color);

    /**
     * Adds angle to the current value of spaceships angle
     */
    void addToAngle(float angle);

    /**
     * Set the value of thrusting
     */
    void setThrusting(bool thrusting);

    /**
     * Update the velocity of the spaceship
     */
    void updateVelocity();

    /**
     * Update the position of the spaceship
     */
    void updatePosition();

    sf::Vector2f getPos() const;

    float getRadius() const;

    float getAngle() const;

    sf::Color getColor() const;

    void setTexture(sf::Texture& text, sf::IntRect ir);

    sf::Sprite getSprite() const;
};

#endif
