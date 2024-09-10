#ifndef SNAKE_H
#define SNAKE_H

#include "../Game.h"

class Snake : public Game
{
private:
    const float PI = 3.141592654;

    sf::CircleShape food;

    sf::VertexArray snakeOutline;
    sf::CircleShape snakeHead;
    int snakeHeadRadius;
    sf::Color snakeHeadColor;
    std::vector<sf::Vector2f> snakeHeadSides;
    std::vector<sf::CircleShape> snakeHeadEyes;
    sf::Color transparentColor;
    sf::Vector2f snakeHeadPos;
    sf::Vector2f joystickAxis;
    float snakeHeadVel;
    float snakeHeadRotation;

    std::vector<sf::CircleShape> snakeBody;
    std::vector<sf::Vector2f> snakeBodyPos;
    std::vector<int> snakeBodyRadii;
    std::vector<float> snakeBodyRotation;
    std::vector<std::vector<sf::Vector2f>> snakeBodySides;
    int snakeBodyLength;

    void connectSegment(int i, float xDiff, float yDiff, float difference);

    void addBodySegment(int radius);

    void setFoodPosition();

    bool snakeHeadCollideWithFood();
    
    bool snakeHeadCollideWithBody();
    
    bool snakeHeadCollideWithWall();

    void updateSnakeSides();
public:
    Snake();

    Snake(int w, int h, int fps);

    void initObjects() override;

    void processInput() override;

    void update() override;

    void render() override;
};

#endif
