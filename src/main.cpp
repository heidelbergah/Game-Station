#include "snake/Snake.h"
#include "asteroids/Asteroids.h"
#include <iostream>

/* Main menu will be created in here. User can select game, and the currGame pointer
 * will be updated to the game of their choice.
 * 1. Set currGame to a game. When the run() loop ends, set currGame to nullptr.
 * 2. When run() loop ends, spit user back out to menu. Don't terminate the entire program until
 * this menu is terminated. Ideally, this will be when the user turns the device off, so no need
 * to implement any window termination, just make sure all data for games is saved when they terminate.
 */

int main()
{
    Game* currGame = nullptr;

    currGame = new Snake(800, 800, 60);

    while(currGame->isGameRunning())
    {
        currGame->run();
    }
 
    delete currGame;
    currGame = nullptr;
}
