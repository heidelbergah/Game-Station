#include "Tetromino.h"

void Tetromino::initializeShape()
{
    int v = 0; // Value
    switch(shape)
    {
        case I:
            v = 1;
            tiles = {{v},
                     {v},
                     {v},
                     {v}};
            break;
        case L:
            v = 2;
            tiles = {{v, 0},
                     {v, 0},
                     {v, v}};
            break;
        case J:
            v = 3;
            tiles = {{0, v},
                     {0, v},
                     {v, v}};
            break;
        case O:
            v = 4;
            tiles = {{v, v},
                     {v, v}};
            break;
        case S:
            v = 5;
            tiles = {{0, v, v},
                     {v, v, 0}};
            break;
        case Z:
            v = 6;
            tiles = {{v, v, 0},
                     {0, v, v}};
            break;
        case T:
            v = 7;
            tiles = {{0, v, 0},
                     {v, v, v}};
            break;
    }
}

Tetromino::Tetromino(int x, int y)
{
    shape = static_cast<Shape>((rand() % 7));
    initializeShape();

    tilePosition.x = x;
    tilePosition.y = y;

    spawnPosition = tilePosition;
}

void Tetromino::rotate(bool clockwise)
{
    std::vector<std::vector<int>> newTiles;
    if(clockwise)
    {
        for(int i = 0; i < tiles[0].size(); ++i)
        {
            std::vector<int> row;
            for(int j = tiles.size()-1; j >= 0; --j)
            {
                row.push_back(tiles[j][i]);
            }
            newTiles.push_back(row);
        }
    }
    else
    {
        for(int i = tiles[0].size()-1; i >= 0; --i)
        {
            std::vector<int> row;
            for(int j = 0; j < tiles.size(); ++j)
            {
                row.push_back(tiles[j][i]);
            }
            newTiles.push_back(row);
        }
    }

    tiles = newTiles;
}

Shape Tetromino::getShape()
{
    return shape;
}

sf::Vector2i Tetromino::getTilePosition()
{
    return tilePosition;
}

std::vector<std::vector<int>>& Tetromino::getTiles()
{
    return tiles;
}

void Tetromino::moveTilePosition(int x, int y)
{
    tilePosition.x += x;
    tilePosition.y += y;
}

void Tetromino::reset()
{
    shape = static_cast<Shape>(rand() % 7);
    initializeShape();
    tilePosition = spawnPosition;
}
