#include "Spaceship.h"

float Spaceship::radiansToAdjustedDegrees(float radians)
{
    return (radians * 180 / PI) + 90;
}

void Spaceship::wrapAroundScreen()
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

Spaceship::Spaceship(int w, int h, float pi)
{
    PI = pi;
    windowWidth = w;
    windowHeight = h;

    radius = 10;
    angle = 0;
    acceleration = 0.1;
    shape.setRadius(radius);
    shape.setRotation(radiansToAdjustedDegrees(angle));
    shape.setPointCount(3);
    color = sf::Color::Red;
    shape.setOutlineColor(color);
    shape.setOutlineThickness(1);
    shape.setFillColor(sf::Color::Black);

    shape.setOrigin(radius, radius);
    pos.x = windowWidth / 2;
    pos.y = windowHeight / 2;
    shape.setScale(1, 2);
    shape.setPosition(pos);

    thrusting = false;
}

void Spaceship::addToAngle(float angle)
{
    this->angle += angle;
}

void Spaceship::setThrusting(bool thrusting)
{
    this->thrusting = thrusting;
}

void Spaceship::updateVelocity()
{
    if(thrusting)
    {
        vel.x += cos(angle) * acceleration;
        vel.y -= sin(angle) * acceleration;
    }
    else
    {
        vel.x *= 0.99;
        vel.y *= 0.99;
    }
}

void Spaceship::updatePosition()
{
    wrapAroundScreen();

    pos.x += vel.x;
    pos.y -= vel.y;

    shape.setRotation(radiansToAdjustedDegrees(angle));
    shape.setPosition(pos);
}

sf::CircleShape Spaceship::getShape() const
{
    return shape;
}
