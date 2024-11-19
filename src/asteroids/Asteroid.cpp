#include "Asteroid.h"
#include <iostream>

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

    float scale = 4 - level;
    radius = 16 * scale;
    angle = (rand() / (RAND_MAX + 1.)) * 2 * PI;
    totalVelocity = 3;

    sprite.setOrigin(16, 16);
    sprite.setScale(scale, scale);
    sprite.setRotation(radiansToAdjustedDegrees(angle));
    
    // Update to cos and sin
    vel.x = cos(angle) * totalVelocity;
    vel.y = sin(angle) * totalVelocity;

    pos.x = rand() % windowWidth;
    pos.y = rand() % windowHeight;

    sprite.setPosition(pos);
}

void Asteroid::updatePosition()
{
    pos.x += vel.x;
    pos.y -= vel.y;
    wrapAroundScreen();
    sprite.setPosition(pos);
}

void Asteroid::setPos(sf::Vector2f p)
{
    pos = p;
    sprite.setPosition(pos);
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

void Asteroid::setTexture(sf::Texture& text, sf::IntRect ir)
{
    sprite.setTexture(text);
    sprite.setTextureRect(ir);
}

sf::Sprite Asteroid::getSprite() const
{
    return sprite;
}
