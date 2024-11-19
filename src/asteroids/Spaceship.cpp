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

Spaceship::Spaceship(int w, int h, float pi, sf::Color c)
{
    PI = pi;
    windowWidth = w;
    windowHeight = h;

    radius = 16;
    angle = 0;
    acceleration = 0.1;
    sprite.setRotation(radiansToAdjustedDegrees(angle));

    color = c;
    sprite.setColor(color);

    sprite.setOrigin(radius, radius);
    pos.x = windowWidth / 2;
    pos.y = windowHeight / 2;
    sprite.setPosition(pos);

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

    sprite.setRotation(radiansToAdjustedDegrees(angle));
    sprite.setPosition(pos);
}

sf::Vector2f Spaceship::getPos() const
{
    return pos;
}

float Spaceship::getRadius() const
{
    return radius;
}

float Spaceship::getAngle() const
{
    return angle;
}

sf::Color Spaceship::getColor() const
{
    return color;
}

    
void Spaceship::setTexture(sf::Texture& text, sf::IntRect ir)
{
    sprite.setTexture(text);
    sprite.setTextureRect(ir);
}

sf::Sprite Spaceship::getSprite() const
{
    return sprite;
}
