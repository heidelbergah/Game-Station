#ifndef SNAKE_H
#define SNAKE_H

#include "../Game.h"
#include <vector>

class Snake : public Game
{
private:
    sf::CircleShape snakeHead;
    int snakeHeadRadius;
    sf::Color snakeHeadColor;
    sf::Vector2i snakeHeadPos;
    sf::Vector2f snakeHeadVel;

    std::vector<sf::CircleShape> snakeBody;
    std::vector<sf::Vector2i> snakeBodyPos;
    std::vector<sf::Vector2i> snakeBodyRadii;
    int snakeBodyLength;

public:
    Snake();

    Snake(int w, int h, int fps);

    void initObjects() override;

    void processInput() override;

    void update() override;

    void render() override;
};

#endif
