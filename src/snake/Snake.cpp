#include "Snake.h"

void Snake::setFoodPosition()
{
    int offset = food.getRadius() * 2;
    sf::Vector2f foodPosition;
    bool positionFound = false;

    while(!positionFound)
    {
        foodPosition = sf::Vector2f(rand() % (WIDTH - offset) + (offset), rand() % (HEIGHT - offset) + (offset));
        positionFound = true;

        for(int i = 0; i < snakes.size(); ++i)
        {
            for(int j = 0; j < snakes[i].getBody().size(); ++j)
            {
                float diffX = foodPosition.x - snakes[i].getBody()[j].pos.x;
                float diffY = foodPosition.y - snakes[i].getBody()[j].pos.y;
                float distance = std::sqrt(diffX * diffX + diffY * diffY);
                if(distance < food.getRadius() + snakes[i].getBody()[j].radius)
                {
                    positionFound = false;
                    i = snakes.size();
                    break;
                }
            }
        }
    }

    food.setPosition(foodPosition);
}

void Snake::handleCollisionsWithFood()
{
    for(UserSnake& us : snakes)
    {
        float diffX = us.getHead().pos.x - food.getPosition().x;
        float diffY = us.getHead().pos.y - food.getPosition().y;
        float distance = std::sqrt(diffX * diffX + diffY * diffY);

        if(distance < us.getHead().radius + food.getRadius())
        {
            setFoodPosition();
            for(int i = 0; i < 5; ++i)
                us.addSegment(us.getLastSegment().radius);
        }
    }
}


void Snake::handleCollisionsWithWall()
{
    for(UserSnake& us : snakes)
    {
        bool collision = false;
        if(us.getHead().pos.x + us.getHead().radius > WIDTH)
            collision = true;
        else if(us.getHead().pos.x - us.getHead().radius < 0)
            collision = true;
        else if(us.getHead().pos.y - us.getHead().radius < 0)
            collision = true;
        else if(us.getHead().pos.y + us.getHead().radius > HEIGHT)
            collision = true;

        if(collision)
            window.close();
    }
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
 
    // Snake data
    Segment head;
    head.radius = 25;
    head.color = sf::Color::Cyan;
    head.pos = sf::Vector2f(WIDTH / 2, HEIGHT / 2);
    head.rotation = 0;
    UserSnake newSnake(head);
    snakes.push_back(newSnake);

    // Create snake body segments
    for(int i = 0; i < 5; ++i)
        for(UserSnake& s : snakes)
            s.addSegment(head.radius - (i+1) * 2);
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
        for(UserSnake& us : snakes)
            us.updateRotation(0.03);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        for(UserSnake& us : snakes)
            us.updateRotation(-0.03);

    for(int i = 0; i < snakes.size(); ++i)
    {
        snakes[i].updateRotation(-joystick.getAxisPosition(i, sf::Joystick::X) / 2000);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        for(UserSnake& us : snakes)
            us.addSegment(10);
    }
}

void Snake::update()
{
    handleCollisionsWithFood();
    handleCollisionsWithWall();
    for(UserSnake& us : snakes)
    {
        us.update();
        if(us.collisionWithBody())
        {
            us.kill();
            window.close();
        }
    }
}

void Snake::render()
{
    window.clear(sf::Color::Black);

    for(UserSnake& us : snakes)
    {
        window.draw(us.getHead().shape);
        window.draw(us.getLastSegment().shape);
        window.draw(us.getLeftEye());
        window.draw(us.getRightEye());
        window.draw(us.getOutline());
    }

    window.draw(food);
    window.display();
}
