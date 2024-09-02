#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "../Game.h"
#include "Asteroid.h"
#include "Spaceship.h"

class Asteroids : public Game
{
private:
    const float PI = 3.141592654;

    sf::Color transparentColor = sf::Color::Black;
    Spaceship player;

    float radiansToAdjustedDegrees(float radians);

    void wrapAroundScreen(Spaceship &spaceship);

public:

    Asteroids();

    Asteroids(int w, int h, int fps);

    void initObjects() override;

    void processInput() override;

    void update() override;

    void render() override;
};

#endif
