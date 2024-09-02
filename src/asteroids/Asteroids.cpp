#include "Asteroids.h"
#include <cmath>

float Asteroids::radiansToAdjustedDegrees(float radians)
{
    return (radians * 180 / PI) + 90;
}

void Asteroids::wrapAroundScreen(Spaceship &spaceship)
{
    if(player.pos.x > WIDTH)
    {
        player.pos.x = 0;
    }
    else if(player.pos.x < 0)
    {
        player.pos.x = WIDTH;
    }
    if(player.pos.y > HEIGHT)
    {
        player.pos.y = 0;
    }
    else if(player.pos.y < 0)
    {
        player.pos.y = HEIGHT;
    }
}

Asteroids::Asteroids()
{

}

Asteroids::Asteroids(int w, int h, int fps) : Game(w, h, fps)
{

}

void Asteroids::initObjects()
{
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Asteroids");
    window.setFramerateLimit(60);
    
    player.radius = 10;
    player.angle = 0;
    player.acceleration = 0.1;
    player.shape.setRadius(player.radius);
    player.shape.setRotation(radiansToAdjustedDegrees(player.angle));
    player.shape.setPointCount(3);
    player.color = sf::Color::Red;
    player.shape.setOutlineColor(player.color);
    player.shape.setOutlineThickness(1);
    player.shape.setFillColor(transparentColor);

    player.shape.setOrigin(player.radius, player.radius);
    player.pos.x = WIDTH / 2;
    player.pos.y = HEIGHT / 2;
    player.shape.setScale(1, 2);
    player.shape.setPosition(player.pos);
}

void Asteroids::processInput()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            gameRunning = false;
        }
    }

}

void Asteroids::update()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player.angle -= 0.1;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player.angle += 0.1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        player.thrusting = true;
    }
    else
    {
        player.thrusting = false;
    }

    if(player.thrusting)
    {
        player.vel.x += cos(player.angle) * player.acceleration;
        player.vel.y -= sin(player.angle) * player.acceleration;
    }
    else
    {
        player.vel.x *= 0.99;
        player.vel.y *= 0.99;
    }

    wrapAroundScreen(player);

    player.pos.x += player.vel.x;
    player.pos.y -= player.vel.y;

    player.shape.setRotation(radiansToAdjustedDegrees(player.angle));
    player.shape.setPosition(player.pos);
}

void Asteroids::render()
{
    window.clear(transparentColor);
    window.draw(player.shape);
    window.display();
}

