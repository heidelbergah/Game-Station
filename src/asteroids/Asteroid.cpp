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

Asteroid::Asteroid(int w, int h, int pi, int l)
{
    windowWidth = w;
    windowHeight = h;
    PI = pi;
    level = l;

    radius = 32.f / level;
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

void Asteroid::updatePosition()
{
    pos.x += vel.x;
    pos.y -= vel.y;
    wrapAroundScreen();
    shape.setPosition(pos);
}

void Asteroid::setPos(sf::Vector2f p)
{
    pos = p;
    shape.setPosition(pos);
}

sf::Vector2f Asteroid::getPos() const
{
    return pos;
}

float Asteroid::getRadius() const
{
    return radius;
}

int Asteroid::getLevel() const
{
    return level;
}

sf::CircleShape Asteroid::getShape() const
{   
    return shape;
}
