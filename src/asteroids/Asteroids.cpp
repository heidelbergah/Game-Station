#include "Asteroids.h"

Asteroids::Asteroids()
{
    startingAsteroidsNum = 4;
}

Asteroids::Asteroids(int w, int h, int fps) : Game(w, h, fps)
{
    startingAsteroidsNum = 4;
}

void Asteroids::initObjects()
{
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Asteroids");
    window.setFramerateLimit(60);

    Spaceship player(WIDTH, HEIGHT, PI);
    players.push_back(player);

    for(int i = 0; i < startingAsteroidsNum; ++i)
    {
        Asteroid asteroid(WIDTH, HEIGHT, PI);
        asteroids.push_back(asteroid);
    }
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
        players[0].addToAngle(-0.1);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        players[0].addToAngle(0.1);

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        players[0].setThrusting(true);
    }
    else
    {
        players[0].setThrusting(false);
    }

    players[0].updateVelocity();
    players[0].updatePosition();
    
    for(Asteroid& a : asteroids)
    {
        a.updatePosition();
    }

}

void Asteroids::render()
{
    window.clear(transparentColor);

    for(Spaceship& p : players)
        window.draw(p.getShape());
    
    for(Asteroid& a : asteroids)
        window.draw(a.getShape());

    window.display();
}

