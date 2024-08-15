#include "Snake.h"

void Snake::connectSegments(int i, int j, float xDiff, float yDiff, float difference)
{
    float angle = std::atan2(-yDiff, xDiff);

    snakeBodyPos[i].x -= cos(angle) * (difference / 2);
    snakeBodyPos[i].y += sin(angle) * (difference / 2);
    
    snakeBodyPos[j].x += cos(angle) * (difference / 2);
    snakeBodyPos[j].y -= sin(angle) * (difference / 2);
}

void Snake::connectSegments(int i, float xDiff, float yDiff, float difference)
{
    float angle = std::atan2(-yDiff, xDiff);

    snakeBodyPos[i].x += cos(angle) * (difference);
    snakeBodyPos[i].y -= sin(angle) * (difference);
}

void Snake::addBodySegment(int radius)
{
    sf::CircleShape bodySegment;
    bodySegment.setRadius(radius);
    bodySegment.setOutlineColor(snakeHeadColor);
    bodySegment.setOutlineThickness(2);
    bodySegment.setFillColor(transparentColor);
    bodySegment.setOrigin(radius, radius);

    sf::Vector2f pos;
    if(snakeBodyLength == 0)
        pos = sf::Vector2f(snakeHeadPos.x + radius, snakeHeadPos.y + radius);
    else
        pos = sf::Vector2f(snakeBodyPos[snakeBodyLength-1].x + radius, snakeBodyPos[snakeBodyLength-1].y + radius);
    bodySegment.setPosition(pos);

    snakeBodyPos.push_back(pos);
    snakeBodyRadii.push_back(radius);
    snakeBody.push_back(bodySegment);
    
    snakeBodyLength++;
}

Snake::Snake() : Game()
{

}

Snake::Snake(int w, int h, int fps) : Game(w, h, fps)
{

}

void Snake::initObjects()
{
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Snake");
    window.setFramerateLimit(60);

    snakeHeadRadius = 20;
    snakeHeadColor = sf::Color::Green;
    transparentColor = sf::Color(0, 0, 0, 0);
    snakeHeadPos = sf::Vector2f(WIDTH / 2, HEIGHT / 2);
    snakeHeadVel = sf::Vector2f(0, 0);

    snakeHeadVel.x = 2; // Create an inital velocity for snake

    snakeHead.setRadius(snakeHeadRadius);
    snakeHead.setOutlineColor(snakeHeadColor);
    snakeHead.setOutlineThickness(2);
    snakeHead.setFillColor(transparentColor);
    snakeHead.setOrigin(snakeHeadRadius, snakeHeadRadius);
    snakeHead.setPosition(snakeHeadPos.x, snakeHeadPos.y);

    for(int i = 0; i < 3; ++i)
    {
        addBodySegment(snakeHeadRadius - (i+1) * 3);
    }
}

void Snake::processInput()
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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        snakeHeadVel.y = -2;
        snakeHeadVel.x = 0;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        snakeHeadVel.y = 2;
        snakeHeadVel.x = 0;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        snakeHeadVel.x = -2;
        snakeHeadVel.y = 0;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        snakeHeadVel.x = 2;
        snakeHeadVel.y = 0;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        addBodySegment(10);
    }

}

void Snake::update()
{
    // Update head position with velocity
    snakeHeadPos.x += snakeHeadVel.x;
    snakeHeadPos.y += snakeHeadVel.y;

    // Chain the snake segments together
    // The more iterations, the smaller the gap between segments the longer the snake grows
    int iterations = 5; 
    for(int i = 0; i < iterations; ++i)
    {
        float xFactor = snakeHeadPos.x - snakeBodyPos[0].x;
        float yFactor = snakeHeadPos.y - snakeBodyPos[0].y;
        float distance = std::sqrt(xFactor * xFactor + yFactor * yFactor);
        if(distance > snakeHeadRadius + snakeBodyRadii[0])
        {
            float difference = distance - (snakeHeadRadius + snakeBodyRadii[0]);
            connectSegments(0, xFactor, yFactor, difference);
        }

        for(int i = 0; i < snakeBodyLength-1; ++i)
        {
            float xFactor = snakeBodyPos[i].x - snakeBodyPos[i+1].x;
            float yFactor = snakeBodyPos[i].y - snakeBodyPos[i+1].y;
            float distance = std::sqrt(xFactor * xFactor + yFactor * yFactor);
            if(distance > snakeBodyRadii[i] + snakeBodyRadii[i+1])
            {
                float difference = distance - (snakeBodyRadii[i] + snakeBodyRadii[i+1]);
                connectSegments(i, i+1, xFactor, yFactor, difference);
            }
        }
    }

    // Set official positions
    snakeHead.setPosition(snakeHeadPos.x, snakeHeadPos.y);
    for(int i = 0; i < snakeBodyLength; ++i)
    {
        snakeBody[i].setPosition(snakeBodyPos[i]);
    }

}

void Snake::render()
{
    window.clear(sf::Color::Black);
    window.draw(snakeHead);
    for(int i = 0; i < snakeBodyLength; ++i)
    {
        window.draw(snakeBody[i]);
    }
    window.display();
}
