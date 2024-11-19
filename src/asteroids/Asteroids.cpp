#include "Asteroids.h"

void Asteroids::spawnAsteroids(int additionalAsteroids)
{
    for(int i = 0; i < startingAsteroidsNum + additionalAsteroids; ++i)
    {
        Asteroid asteroid(WIDTH, HEIGHT, PI, 1);
        int ati = rand() % 6; // ati = asteroid texture index
        sf::IntRect ir((32 * ati), 0, 32, 32);
        asteroid.setTexture(asteroidsTexture, ir);
        asteroids.push_back(asteroid);
    }
}

void Asteroids::removeOutOfBoundsProjectiles()
{
    for(int i = 0; i < projectiles.size(); ++i)
    {
        sf::Vector2f pos = projectiles[i].getPos();
        bool outOfBounds = false;
        if (pos.x < 0)
            outOfBounds = true;
        else if (pos.x > WIDTH)
            outOfBounds = true;
        if (pos.y < 0)
            outOfBounds = true;
        else if (pos.y > HEIGHT)
            outOfBounds = true;
        
        if(outOfBounds)
            projectiles.erase(projectiles.begin() + i);
    }
}

void Asteroids::collisionResolutions()
{
    for(int i = 0; i < projectiles.size(); ++i)
    {
        for(int j = 0; j < asteroids.size(); ++j)
        {
            sf::Vector2f projPos = projectiles[i].getPos();
            sf::Vector2f astPos = asteroids[j].getPos();

            float xDiff = projPos.x - astPos.x;
            float yDiff = projPos.y - astPos.y;

            float projRadius = projectiles[i].getRadius();
            float astRadius = asteroids[j].getRadius();
        
            float distance = sqrt((xDiff * xDiff) + (yDiff * yDiff));

            if(distance < projRadius + astRadius)
            {
                int asteroidLevel = asteroids[j].getLevel();
                sf::Vector2f asteroidPos = asteroids[j].getPos();

                projectiles.erase(projectiles.begin() + i);
                asteroids.erase(asteroids.begin() + j);
                i--;
                j--;
                
                if(asteroidLevel < 3)
                {
                    int ati = rand() % 6; // ati = asteroid texture index
                    sf::IntRect ir((32 * ati), 0, 32, 32);
                    
                    Asteroid asteroid1(WIDTH, HEIGHT, PI, asteroidLevel + 1);
                    asteroid1.setPos(asteroidPos);
                    asteroid1.setTexture(asteroidsTexture, ir);
                    asteroids.push_back(asteroid1);
                    Asteroid asteroid2(WIDTH, HEIGHT, PI, asteroidLevel + 1);
                    asteroid2.setPos(asteroidPos);
                    asteroid2.setTexture(asteroidsTexture, ir);
                    asteroids.push_back(asteroid2);
                }
            }
        }
    }

    for(int i = 0; i < players.size(); ++i)
    {
        for(int j = 0; j < asteroids.size(); ++j)
        {
            sf::Vector2f playerPos = players[i].getPos();
            sf::Vector2f astPos = asteroids[j].getPos();

            float xDiff = playerPos.x - astPos.x;
            float yDiff = playerPos.y - astPos.y;

            float playerRadius = players[i].getRadius();
            float astRadius = asteroids[j].getRadius();
        
            float distance = sqrt((xDiff * xDiff) + (yDiff * yDiff));

            if(distance < playerRadius + astRadius)
            {
                players.erase(players.begin() + i);
                i--;
            }

        }
    }
}

Asteroids::Asteroids()
{
    startingAsteroidsNum = 4;
    currentWave = 1;
}

Asteroids::Asteroids(int w, int h, int fps) : Game(w, h, fps)
{
    startingAsteroidsNum = 4;
    currentWave = 1;
}

void Asteroids::initObjects()
{
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Asteroids");
    window.setFramerateLimit(60);

    asteroidsTexture.loadFromFile("asteroids/assets/asteroids.png");
    spaceshipsTexture.loadFromFile("asteroids/assets/spaceships.png");

    Spaceship player(WIDTH, HEIGHT, PI, sf::Color::Green);
    player.setTexture(spaceshipsTexture, sf::IntRect(0, 0, 32, 32));
    players.push_back(player);

    spawnAsteroids(0);
}

void Asteroids::processInput()
{
    sf::Time elapsedTime = clock.getElapsedTime();

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
    
    /** May want to enforce the user to click the space bar for each projectile... **/
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && elapsedTime.asMilliseconds() > 200)
    {
        Projectile p(players[0].getPos(), players[0].getAngle(), players[0].getColor());
        projectiles.push_back(p);
        clock.restart();
    }

}

void Asteroids::update()
{
    if(asteroids.size() == 0)
    {
        spawnAsteroids(currentWave);
        currentWave++;
    }

    players[0].updateVelocity();
    players[0].updatePosition();

    removeOutOfBoundsProjectiles();

    collisionResolutions();

    if(players.size() == 0)
    {
        gameRunning = false;
    }

    for(Projectile& p : projectiles)
    {
        p.updatePosition();
    }

    for(Asteroid& a : asteroids)
    {
        a.updatePosition();
    }

}

void Asteroids::render()
{
    window.clear(transparentColor);

    for(Spaceship& p : players)
        window.draw(p.getSprite());
    
    for(Asteroid& a : asteroids)
        window.draw(a.getSprite());

    for(Projectile& p : projectiles)
        window.draw(p.getShape());

    window.display();
}

