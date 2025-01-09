#include "Tetris.h"

Tetris::Tetris()
{
    srand(time(NULL));
}


Tetris::Tetris(int h, int w, int fps) : Game(h, w, fps)
{
}

Tetris::~Tetris()
{
    for(GameGrid* gameGrid : gameGrids)
    {
        delete gameGrid;
    }
}

void Tetris::initObjects()
{
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Tetris");
    window.setFramerateLimit(FPS);

    for(int i = 0; i < 4; ++i)
    {
        bool connected = sf::Joystick::isConnected(i);
        if(connected)
        {
            gameGrids.push_back(new GameGrid(i));
        }
    }

    /* DEBUGGING PURPOSES. REMOVE WHEN ABSOLUTELY NECESARY */
    for(int i = 0; i < gameGrids.size(); ++i)
    {
        std::cout << static_cast<std::string>(sf::Joystick::getIdentification(i).name) << std::endl;
    }
}

void Tetris::processInput()
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

        for(int i = 0; i < gameGrids.size(); ++i)
        {
            int rotation = 0;
            bool drop = false;;
            int movement = 0;

            if(sf::Joystick::isButtonPressed(i, 0))
            {
                drop = true;
            }
            if(sf::Joystick::isButtonPressed(i, 8))
            {
                rotation = -1;
            }
            if(sf::Joystick::isButtonPressed(i, 9))
            {
                rotation = 1;
            }

            movement = sf::Joystick::getAxisPosition(i, sf::Joystick::PovX) / 100;
            int yMovement = sf::Joystick::getAxisPosition(i, sf::Joystick::PovY) / 100;
            if(yMovement == 1) movement = 2;

            // SHOULD GO IN UPDATE FUNCTION, NOT PROCESS INPUT. FIX ASAP.
            gameGrids[i]->update(rotation, drop, movement);
        }
    }
}

void Tetris::update()
{
    for(int i = 0; i < gameGrids.size(); ++i)
    {
        sf::Time time1 = gameTime.getElapsedTime();
        if(time1.asMilliseconds() >= gameGrids[i]->getFallSpeed())
        {
            gameTime.restart();
            gameGrids[i]->fallTetromino();
        }
    }
}

void Tetris::render()
{
    window.clear();

    for(GameGrid *gameGrid : gameGrids)
    {
        gameGrid->draw(window);
    }

    window.display();
}
