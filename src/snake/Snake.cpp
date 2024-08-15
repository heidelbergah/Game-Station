#include "Snake.h"

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
    snakeHeadPos = sf::Vector2i(WIDTH / 2, HEIGHT / 2);
    snakeHeadVel = sf::Vector2f(0, 0);
    snakeBodyLength = 3;

    snakeHead.setRadius(snakeHeadRadius);
    snakeHead.setOutlineColor(snakeHeadColor);
    snakeHead.setOutlineThickness(2);
    snakeHead.setFillColor(sf::Color::Black);
    snakeHead.setOrigin(snakeHeadRadius, snakeHeadRadius);
    snakeHead.setPosition(snakeHeadPos.x, snakeHeadPos.y);

    for(int i = 0; i < snakeBodyLength; ++i)
    {
        sf::CircleShape bodySegment;
        bodySegment.setRadius(snakeHeadRadius);
        bodySegment.setOutlineColor(snakeHeadColor);
        bodySegment.setOutlineThickness(2);
        bodySegment.setFillColor(sf::Color::Black);
        bodySegment.setOrigin(snakeHeadRadius, snakeHeadRadius);
        
        snakeBodyPos.push_back(sf::Vector2i(snakeHeadPos.x - (snakeHeadRadius * i), snakeHeadPos.y - (snakeHeadRadius * i)));
        bodySegment.setPosition(snakeBodyPos[i].x, snakeBodyPos[i].y);
        snakeBody.push_back(bodySegment);
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

}

void Snake::update()
{
    snakeHeadPos.x += snakeHeadVel.x;
    snakeHeadPos.y += snakeHeadVel.y;
    snakeHead.setPosition(snakeHeadPos.x, snakeHeadPos.y);

    for(int i = 0; i < snakeBodyLength; ++i)
    {

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
