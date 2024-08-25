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
    // Add on another two points for each body segment
    snakeOutline.setPointCount(snakeOutline.getPointCount() + 2);
    
    // Basic data setup
    sf::CircleShape bodySegment;
    bodySegment.setRadius(radius);
    bodySegment.setFillColor(snakeHeadColor);
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
    std::vector sides = {sf::Vector2f(pos.x + cos(rotation + PI/2) * radius, pos.y - sin(rotation + PI/2) * radius), sf::Vector2f(pos.x + cos(rotation + PI/2) * radius, pos.y - sin(rotation + PI/2) * radius)};
    snakeBodySides.push_back(sides);

    snakeBodyLength++;
}

void Snake::setFoodPosition()
{
    int offset = food.getRadius() * 2;
    food.setPosition(rand() % (WIDTH - offset) + (offset), rand() % (HEIGHT - offset) + (offset));
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

bool Snake::snakeHeadCollideWithBody()
{
    // Skip the first body segment because the snake head can never collide with it
    for(int i = 1; i < snakeBodyPos.size(); ++i)
    {
        float diffX = snakeHeadPos.x - snakeBodyPos[i].x;
        float diffY = snakeHeadPos.y - snakeBodyPos[i].y;
        float distance = std::sqrt(diffX * diffX + diffY * diffY);
        if(distance < snakeHeadRadius + snakeBodyRadii[i])
            return true;
    }
    return false;
}

bool Snake::snakeHeadCollideWithWall()
{
    if(snakeHeadPos.x + snakeHeadRadius > WIDTH)
        return true;
    else if(snakeHeadPos.x - snakeHeadRadius < 0)
        return true;
    else if(snakeHeadPos.y - snakeHeadRadius < 0)
        return true;
    else if(snakeHeadPos.y + snakeHeadRadius > HEIGHT)
        return true;
    return false;
}

void Snake::updateSnakeSides()
{
    snakeHeadSides[0] = sf::Vector2f(snakeHeadPos.x + cos(snakeHeadRotation + PI/2) * snakeHeadRadius, snakeHeadPos.y - sin(snakeHeadRotation + PI/2) * snakeHeadRadius);
    snakeHeadSides[1] = sf::Vector2f(snakeHeadPos.x + cos(snakeHeadRotation - PI/2) * snakeHeadRadius, snakeHeadPos.y - sin(snakeHeadRotation - PI/2) * snakeHeadRadius);
    for(int i = 0; i < snakeBodyLength; ++i)
    {
        snakeBodySides[i] = {sf::Vector2f(snakeBodyPos[i].x + cos(snakeBodyRotation[i] + PI/2) * snakeBodyRadii[i], snakeBodyPos[i].y - sin(snakeBodyRotation[i] + PI/2) * snakeBodyRadii[i]), sf::Vector2f(snakeBodyPos[i].x + cos(snakeBodyRotation[i] - 90) * snakeBodyRadii[i], snakeBodyPos[i].y - sin(snakeBodyRotation[i] - 90) * snakeBodyRadii[i])};
    }

    // Quickly update the snake eyes
    snakeHeadEyes[0].setPosition(snakeHeadSides[0]);
    snakeHeadEyes[1].setPosition(snakeHeadSides[1]);

    // Create the convex shape
    int pointCount = 1;
    snakeOutline.setPoint(pointCount-1, snakeHeadSides[0]);
    for(int i = 0; i < snakeBodyLength; ++i)
    {
        snakeOutline.setPoint(pointCount, snakeBodySides[i][0]);
        pointCount++;
    }
    for(int i = snakeBodyLength-1; i >= 0; --i)
    {
        snakeOutline.setPoint(pointCount, snakeBodySides[i][1]);
        pointCount++;
    }
    snakeOutline.setPoint(pointCount++, snakeHeadSides[1]);
    snakeOutline.setPoint(pointCount, snakeHeadSides[0]);
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

    // Create food
    food.setRadius(15);
    food.setFillColor(sf::Color::Red);
    food.setOrigin(15, 15);
    setFoodPosition();
        
    // Create snake head data
    snakeHeadRadius = 20;
    snakeHeadColor = sf::Color::Green;
    transparentColor = sf::Color(0, 0, 0, 0);
    snakeHeadPos = sf::Vector2f(WIDTH / 2, HEIGHT / 2);
    snakeHeadVel = 2;
    snakeHeadRotation = 0;
    snakeOutline.setPointCount(3); // One for both sides of the snake head, and one to wrap back around
    snakeOutline.setFillColor(snakeHeadColor);

    // Create snake head
    snakeHead.setRadius(snakeHeadRadius);
    snakeHead.setFillColor(snakeHeadColor);
    snakeHead.setOrigin(snakeHeadRadius, snakeHeadRadius);
    snakeHead.setPosition(snakeHeadPos.x, snakeHeadPos.y);
    snakeHead.setRotation(snakeHeadRotation);
    snakeHeadSides.push_back(sf::Vector2f(snakeHeadPos.x + cos(snakeHeadRotation + PI/2) * snakeHeadRadius, snakeHeadPos.y - sin(snakeHeadRotation + PI/2) * snakeHeadRadius));
    snakeHeadSides.push_back(sf::Vector2f(snakeHeadPos.x + cos(snakeHeadRotation - PI/2) * snakeHeadRadius, snakeHeadPos.y - sin(snakeHeadRotation - PI/2) * snakeHeadRadius));

    // Create snake eyes
    int eyeSize = 4;
    snakeHeadEyes.push_back(sf::CircleShape(eyeSize));
    snakeHeadEyes.push_back(sf::CircleShape(eyeSize));
    snakeHeadEyes[0].setOrigin(eyeSize, eyeSize);
    snakeHeadEyes[0].setPosition(snakeHeadSides[0]);
    snakeHeadEyes[0].setFillColor(sf::Color::Black);
    snakeHeadEyes[0].setOutlineThickness(2);
    snakeHeadEyes[0].setOutlineColor(sf::Color::White);
    snakeHeadEyes[1].setOrigin(eyeSize, eyeSize);
    snakeHeadEyes[1].setPosition(snakeHeadSides[1]);
    snakeHeadEyes[1].setFillColor(sf::Color::Black);
    snakeHeadEyes[1].setOutlineThickness(2);
    snakeHeadEyes[1].setOutlineColor(sf::Color::White);

    // Create snake body segments
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
        snakeHeadRotation += 0.05;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        snakeHeadRotation -= 0.05;

    snakeHeadRotation -= joystick.getAxisPosition(0, sf::Joystick::X) / 2000;

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

    if(snakeHeadCollideWithFood())
    {
        for(int i = 0; i < 3; ++i)
            addBodySegment(10);
        setFoodPosition();
    }

    if(snakeHeadCollideWithBody() || snakeHeadCollideWithWall())
    {
        gameRunning = false;
    }

    // Set official positions
    snakeHead.setPosition(snakeHeadPos.x, snakeHeadPos.y);
    for(int i = 0; i < snakeBodyLength; ++i)
    {
        snakeBody[i].setPosition(snakeBodyPos[i]);
        snakeBody[i].setRotation(snakeBodyRotation[i]);
    }

    updateSnakeSides();
}

void Snake::render()
{
    window.clear(sf::Color::Black);
    window.draw(snakeHead);
    for(int i = 0; i < snakeBodyLength; ++i)
    {
        window.draw(snakeBody[i]);
    }
    window.draw(snakeOutline);
    window.draw(snakeHeadEyes[0]);
    window.draw(snakeHeadEyes[1]);
    window.draw(food);
    window.display();
}
