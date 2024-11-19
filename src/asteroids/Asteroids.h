#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "../Game.h"
#include "Asteroid.h"
#include "Spaceship.h"
#include "Projectile.h"

class Asteroids : public Game
{
private:
    const float PI = 3.141592654;

    sf::Color transparentColor = sf::Color::Black;
 
    sf::Clock clock;

    sf::Texture asteroidsTexture;
    sf::Texture spaceshipsTexture;

    std::vector<Spaceship> players;
    std::vector<Asteroid> asteroids;
    std::vector<Projectile> projectiles;

    int startingAsteroidsNum;
    int currentWave;

    void spawnAsteroids(int additionalAsteroids);

    void removeOutOfBoundsProjectiles();

    void collisionResolutions();

public:

    Asteroids();

    Asteroids(int w, int h, int fps);

    void initObjects() override;

    void processInput() override;

    void update() override;

    void render() override;
};

#endif
