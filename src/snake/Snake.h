#ifndef SNAKE_H
#define SNAKE_H

#include "../Game.h"
#include <vector>
#include <cmath>
#include <iostream>

class Snake : public Game
{
private:
    const float PI = 3.141592654;

    sf::CircleShape snakeHead;
    int snakeHeadRadius;
    sf::Color snakeHeadColor;
    sf::Color transparentColor;
    sf::Vector2f snakeHeadPos;
    sf::Vector2f snakeHeadVel;

    std::vector<sf::CircleShape> snakeBody;
    std::vector<sf::Vector2f> snakeBodyPos;
    std::vector<int> snakeBodyRadii;
    int snakeBodyLength;

    void connectSegments(int i, int j, float xDiff, float yDiff, float difference);
    void connectSegments(int i, float xDiff, float yDiff, float difference);

    void addBodySegment(int radius);
public:
    Snake();

    Snake(int w, int h, int fps);

    void initObjects() override;

    void processInput() override;

    void update() override;

    void render() override;
};

#endif