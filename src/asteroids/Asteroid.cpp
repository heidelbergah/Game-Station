#include "Asteroid.h"

float Asteroid::radiansToAdjustedDegrees(float radians)
{
    return (radians * 180 / PI) + 90;
}

void Asteroid::wrapAroundScreen()
{
    if(pos.x > windowWidth)
    {
        pos.x = 0;
    }
    else if(pos.x < 0)
    {
        pos.x = windowWidth;
    }
    if(pos.y > windowHeight)
    {
        pos.y = 0;
    }
    else if(pos.y < 0)
    {
        pos.y = windowHeight;
    }
}

Asteroid::Asteroid(int w, int h, int pi)
{
    windowWidth = w;
    windowHeight = h;
    PI = pi;

    radius = 25;
    angle = (rand() / (RAND_MAX + 1.)) * 2 * PI;
    totalVelocity = 3;

    shape.setRadius(radius);
    shape.setRotation(radiansToAdjustedDegrees(angle));
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1);
    shape.setFillColor(sf::Color::Black);
    shape.setOrigin(radius, radius);
    
    // Update to cos and sin
    vel.x = cos(angle) * totalVelocity;
    vel.y = sin(angle) * totalVelocity;

    pos.x = rand() % windowWidth;
    pos.y = rand() % windowHeight;

    shape.setPosition(pos);
}

void Asteroid::updateVelocity()
{
    
}

void Asteroid::updatePosition()
{
    pos.x += vel.x;
    pos.y -= vel.y;
    wrapAroundScreen();
    shape.setPosition(pos);
}

sf::CircleShape Asteroid::getShape() const
{   
    return shape;
}
