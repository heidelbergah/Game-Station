#ifndef USER_SNAKE_H
#define USER_SNAKE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

struct Segment
{
    int radius;
    sf::Vector2f pos;
    float rotation;
    sf::Vector2f lSide;
    sf::Vector2f rSide;
    sf::Color color;
    sf::CircleShape shape;
};

class UserSnake
{
private:
    const float PI = 3.141592654;
    Segment head;
    std::vector<Segment> body;
    sf::VertexArray outline;
    sf::Color color;
    float velocity;

    sf::CircleShape lEye;
    sf::CircleShape rEye;

    bool alive = true;

public:
    UserSnake(Segment head);

    void connectSegments(int i, float xDiff, float yDiff, float difference);

    void addSegment(int radius);

    bool collisionWithBody();

    Segment getHead();

    std::vector<Segment> getBody();

    Segment getLastSegment();
    
    sf::VertexArray getOutline();

    sf::CircleShape getLeftEye();
    
    sf::CircleShape getRightEye();

    bool isAlive();

    void kill();

    void updateRotation(float rotationAdjustment);

    void update();
};

#endif
