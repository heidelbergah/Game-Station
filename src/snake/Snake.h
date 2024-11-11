#ifndef SNAKE_H
#define SNAKE_H

#include "../Game.h"
#include "UserSnake.h"

class Snake : public Game
{
private:
    const float PI = 3.141592654;

    std::vector<UserSnake> snakes;

    sf::CircleShape food;

    void setFoodPosition();

    void handleCollisionsWithFood();
    
    void handleCollisionsWithWall();

public:
    Snake();

    Snake(int w, int h, int fps);

    void initObjects() override;

    void processInput() override;

    void update() override;

    void render() override;
};

#endif
