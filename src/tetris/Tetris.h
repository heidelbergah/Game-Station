#ifndef TETRIS_H
#define TETRIS_H

#include "../Game.h"
#include "GameGrid.h"

class Tetris : public Game
{
private:
    std::vector<GameGrid*> gameGrids;

    sf::Clock gameTime;

public:

    Tetris();
    
    ~Tetris();

    Tetris(int h, int w, int fps);

    void initObjects() override;

    void processInput() override;

    void update() override;

    void render() override;
};

#endif
