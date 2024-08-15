#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>

class Game
{
protected:
    sf::RenderWindow window;
    int WIDTH, HEIGHT, FPS;
    bool gameRunning;

public:
    /**
     * Base constructor. Sets base values for member variables
     */
    Game();

    /**
     * Sets members variables to specified values
     */
    Game(int w, int h, int fps);

    /**
     * Initializes all member objects. Meant to be run one time at the start
     * of the program (called inside the run method)
     */
    virtual void initObjects();

    /**
     * Processes all user input
     */
    virtual void processInput();

    /**
     * Updates all logic of the program
     */
    virtual void update();

    /**
     * Renders all renderable objects to the screen(s)
     */
    virtual void render();

    /**
     * Runs the entire program. Calls all the above methods in a while loop.
     * Meant to be called once in the main.cpp file
     */
    void run();

    /**
     * Returns the status of gameRunning
     */
    bool isGameRunning() const;
};

#endif

