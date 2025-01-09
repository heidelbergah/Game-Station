#ifndef TETROMINO_H
#define TETROMINO_H

#include "SFML/Graphics.hpp"
#include <iostream>

enum Shape
{
    I,
    L,
    J,
    O,
    S,
    Z,
    T
};

class Tetromino
{
private:
    Shape shape;
    std::vector<std::vector<int>> tiles;
    sf::Vector2i tilePosition;
    sf::Vector2i spawnPosition;

    void initializeShape();

public:

    Tetromino(int x, int y);

    void rotate(bool clockwise);

    Shape getShape();

    sf::Vector2i getTilePosition();

    std::vector<std::vector<int>>& getTiles();

    void moveTilePosition(int x, int y);

    void reset();
};

#endif
