#include "Snake.h"

void Snake::connectSegment(int i, float xDiff, float yDiff, float difference)
{
    float angle = std::atan2(-yDiff, xDiff);

    snakeBodyRotation[i] = angle;
    snakeBodyPos[i].x += cos(angle) * (difference);
    snakeBodyPos[i].y -= sin(angle) * (difference);
}

void Snake::addBodySegment(int radius)
{
    // Basic data setup
    sf::CircleShape bodySegment;
    bodySegment.setRadius(radius);
    bodySegment.setOutlineColor(snakeHeadColor);
    bodySegment.setOutlineThickness(1);
    bodySegment.setFillColor(transparentColor);
    bodySegment.setOrigin(radius, radius);

    // Place the new segment directly behind the head or body segment in the direction
    // they're going. For example, if the head is moving left, place the new segment to the right
    // of the snake head.
    sf::Vector2f pos;
    float rotation = 0;
    if(snakeBodyLength == 0)
    {
        rotation = snakeHeadRotation;
        pos = sf::Vector2f(snakeHeadPos.x - cos(rotation) * radius * 2, snakeHeadPos.y + sin(rotation) * radius * 2);
    }
    else
    {
        rotation = snakeBodyRotation[snakeBodyLength-1];
        pos = sf::Vector2f(snakeBodyPos[snakeBodyLength-1].x - cos(rotation) * radius * 2, snakeBodyPos[snakeBodyLength-1].y + sin(rotation) * radius * 2);
    }

    // Finish up data setup
    bodySegment.setRotation(rotation);
    bodySegment.setPosition(pos);

    snakeBodyPos.push_back(pos);
    snakeBodyRadii.push_back(radius);
    snakeBodyRotation.push_back(rotation);
    snakeBody.push_back(bodySegment);

    snakeBodyLength++;
}

void Snake::setFoodPosition()
{
    food.setPosition((rand() % WIDTH) - food.getRadius() * 2, (rand() % HEIGHT) - food.getRadius() * 2);
}

bool Snake::snakeHeadCollideWithFood()
{
    float diffX = snakeHeadPos.x - food.getPosition().x;
    float diffY = snakeHeadPos.y - food.getPosition().y;
    float distance = std::sqrt(diffX * diffX + diffY * diffY);

    if(distance < snakeHeadRadius + food.getRadius())
        return true;
    return false;
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

    food.setRadius(15);
    food.setFillColor(sf::Color::Red);
    food.setOrigin(15, 15);
    setFoodPosition();
        
    snakeHeadRadius = 20;
    snakeHeadColor = sf::Color::Green;
    transparentColor = sf::Color(0, 0, 0, 0);
    snakeHeadPos = sf::Vector2f(WIDTH / 2, HEIGHT / 2);
    snakeHeadVel = 2;
    snakeHeadRotation = 0;

    snakeHead.setRadius(snakeHeadRadius);
    snakeHead.setOutlineColor(snakeHeadColor);
    snakeHead.setOutlineThickness(1);
    snakeHead.setFillColor(transparentColor);
    snakeHead.setOrigin(snakeHeadRadius, snakeHeadRadius);
    snakeHead.setPosition(snakeHeadPos.x, snakeHeadPos.y);
    snakeHead.setRotation(snakeHeadRotation);

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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        snakeHeadRotation += 0.1;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        snakeHeadRotation -= 0.1;

    snakeHeadRotation -= joystick.getAxisPosition(0, sf::Joystick::X) / 1000;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        addBodySegment(10);
    }

}

void Snake::update()
{
    // Update head position with velocity
    snakeHeadPos.x += cos(snakeHeadRotation) * snakeHeadVel;
    snakeHeadPos.y -= sin(snakeHeadRotation) * snakeHeadVel;

    // Chain the snake segments together
    // The more iterations, the smaller the gap between segments the longer the snake grows
    float xFactor = snakeHeadPos.x - snakeBodyPos[0].x;
    float yFactor = snakeHeadPos.y - snakeBodyPos[0].y;
    float distance = std::sqrt(xFactor * xFactor + yFactor * yFactor);
    if(distance > snakeHeadRadius + snakeBodyRadii[0])
    {
        float difference = distance - (snakeHeadRadius + snakeBodyRadii[0]);
        connectSegment(0, xFactor, yFactor, difference);
    }

    for(int i = 0; i < snakeBodyLength-1; ++i)
    {
        float xFactor = snakeBodyPos[i].x - snakeBodyPos[i+1].x;
        float yFactor = snakeBodyPos[i].y - snakeBodyPos[i+1].y;
        float distance = std::sqrt(xFactor * xFactor + yFactor * yFactor);
        if(distance > snakeBodyRadii[i] + snakeBodyRadii[i+1])
        {
            float difference = distance - (snakeBodyRadii[i] + snakeBodyRadii[i+1]);
            connectSegment(i+1, xFactor, yFactor, difference);
        }
    }

    // Set official positions
    snakeHead.setPosition(snakeHeadPos.x, snakeHeadPos.y);
    for(int i = 0; i < snakeBodyLength; ++i)
    {
        snakeBody[i].setPosition(snakeBodyPos[i]);
        snakeBody[i].setRotation(snakeBodyRotation[i]);
    }
    
    if(snakeHeadCollideWithFood())
    {
        for(int i = 0; i < 3; ++i)
            addBodySegment(10);
        setFoodPosition();
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
    window.draw(food);
    window.display();
}
