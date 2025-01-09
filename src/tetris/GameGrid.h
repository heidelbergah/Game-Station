#ifndef GAME_GRID_H
#define GAME_GRID_H

#include "Tetromino.h"
#include <iostream>

class GameGrid
{
private:
    sf::RenderTexture texture;
    sf::Sprite sprite;

    sf::Joystick controller;
    sf::RectangleShape grid;
    sf::VertexArray gridLines;

    float fallSpeed = 1000; // As milliseconds

    int tileSize = 35;
    sf::Vector2i gridSize;

    std::vector<std::vector<int>> tiles;
    std::vector<sf::Color> colors;

    Tetromino currTetromino;
    Tetromino ghostTetromino;

    void initializeGrid();

    bool isPotentialMoveValid(int x, int y, Tetromino& t);

    void placeCurrTetromino();

    void placeGhostTetromino();

    void clearRows();

public:

    GameGrid(int player);

    void draw(sf::RenderWindow& window);

    void setPosition(sf::Vector2f pos);

    void update(int turnDirection, bool drop, int moveDirection);

    void fallTetromino();

    float getFallSpeed();
};

#endif
