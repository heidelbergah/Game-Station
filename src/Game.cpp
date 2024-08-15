#include "Game.h"

Game::Game()
{
    WIDTH = 1080;
    HEIGHT = 1920;
    FPS = 60;
    gameRunning = true;
}

Game::Game(int w, int h, int fps)
{
    WIDTH = w;
    HEIGHT = h;
    FPS = fps;
    gameRunning = true;
}

void Game::initObjects()
{
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Game Engine");
    window.setFramerateLimit(FPS);
}

void Game::processInput()
{

}

void Game::update()
{

}

void Game::render()
{

}

void Game::run()
{
    initObjects();
    while(gameRunning)
    {
        processInput();
        update();
        render();
    }
}

bool Game::isGameRunning() const
{
    return gameRunning;
}
