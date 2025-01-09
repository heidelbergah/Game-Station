#include "GameGrid.h"

void GameGrid::initializeGrid()
{        
    gridSize.x = 10;
    gridSize.y = 20;

    for(int i = 0; i < gridSize.y; ++i)
    {
        std::vector<int> row;
        for(int j = 0; j < gridSize.x; ++j)
        {
            row.push_back(0);
        }
        tiles.push_back(row);
    }

    sf::Vector2f gameGridSize;
    gameGridSize.x = gridSize.x * tileSize;
    gameGridSize.y = gridSize.y * tileSize;
    
    grid.setPosition(0, 0);
    grid.setSize(gameGridSize);
    grid.setFillColor(sf::Color(50, 50, 50));

    texture.create(gameGridSize.x, gameGridSize.y);

    int totalLines = 2 * (gridSize.x + gridSize.y - 2);
    gridLines = sf::VertexArray(sf::Lines, totalLines);

    // Vertical lines
    int bottomYPos = gridSize.y * tileSize;
    int currX = 0;

    for(int i = 0; i < 2*(gridSize.x-1); i+=2)
    {
        if(i % 2 == 0) currX += tileSize;

        gridLines[i].position = sf::Vector2f(currX, 0);
        gridLines[i+1].position = sf::Vector2f(currX, bottomYPos);
    
        gridLines[i].color = sf::Color::Black;
        gridLines[i+1].color = sf::Color::Black;
    }

    // Horizontal lines
    int rightXPos = gridSize.x * tileSize;
    int currY = 0;

    for(int i = 2*(gridSize.x-1); i < (2*(gridSize.y-1) + 2*(gridSize.x-1)); i+=2)
    {
        if(i % 2 == 0) currY += tileSize;

        gridLines[i].position = sf::Vector2f(0, currY);
        gridLines[i+1].position = sf::Vector2f(rightXPos, currY);
    
        gridLines[i].color = sf::Color::Black;
        gridLines[i+1].color = sf::Color::Black;
    }
}

bool GameGrid::isPotentialMoveValid(int xDisplacement, int yDisplacement, Tetromino& t)
{
    std::vector<sf::Vector2i> tetrominoPositions;
    std::vector<std::vector<int>> tetrominoTiles = t.getTiles();
    sf::Vector2i pos = t.getTilePosition();
    pos.x += xDisplacement;
    pos.y += yDisplacement;
    for(int i = 0; i < tetrominoTiles.size(); ++i)
    {
        for(int j = 0; j < tetrominoTiles[0].size(); ++j)
        {
            if(tetrominoTiles[i][j] != 0)
            {
                tetrominoPositions.push_back(sf::Vector2i(j+pos.x, i+pos.y));
            }
        }
    }

    for(sf::Vector2i p : tetrominoPositions)
    {
        if(p.x > gridSize.x-1 || p.x < 0) return false;
        if(p.y > gridSize.y-1 || p.y < 0) return false;

        if(tiles[p.y][p.x] != 0) return false;
    }

    return true;
}

void GameGrid::placeCurrTetromino()
{
    std::vector<sf::Vector2i> tetrominoPositions;
    std::vector<std::vector<int>> tetrominoTiles = currTetromino.getTiles();
    sf::Vector2i pos = currTetromino.getTilePosition();
    for(int i = 0; i < tetrominoTiles.size(); ++i)
    {
        for(int j = 0; j < tetrominoTiles[0].size(); ++j)
        {
            if(tetrominoTiles[i][j] != 0)
            {
                tetrominoPositions.push_back(sf::Vector2i(j+pos.x, i+pos.y));
            }
        }
    }

    for(sf::Vector2i p : tetrominoPositions)
    {
        tiles[p.y][p.x] = currTetromino.getShape()+1;
    }

    clearRows();

    currTetromino.reset();
}

void GameGrid::placeGhostTetromino()
{
    while(isPotentialMoveValid(0, 1, ghostTetromino))
    {
        ghostTetromino.moveTilePosition(0, 1);
    }
}

void GameGrid::clearRows()
{
    int clearedRows = 0;
    for(int i = tiles.size()-1; i >= 0; --i)
    {
        bool discontinuity = false;
        for(int j = 0; j < tiles[0].size(); ++j)
        {
            if(tiles[i][j] == 0) discontinuity = true;
        }
        if(!discontinuity)
        {
            clearedRows++;
            for(int j = 0; j < tiles[0].size(); ++j)
            {
                tiles[i][j] = 0;
            }

            for(int k = i; k >= 1; --k)
            {
                for(int h = 0; h < tiles[0].size(); ++h)
                {
                    tiles[k][h] = tiles[k-1][h];
                }
            }
            for(int h = 0; h < tiles[0].size(); ++h)
            {
                tiles[0][h] = 0;
            }

            i++;
        }
    }

    fallSpeed -= clearedRows * clearedRows * 10;
    if(fallSpeed <= 0) fallSpeed = 1;
}

GameGrid::GameGrid(int player) : currTetromino(0, 0), ghostTetromino(0, 0)
{
    initializeGrid();

    Tetromino t(gridSize.x/2, 0);
    currTetromino = t;
    
    sprite.setPosition((gridSize.x * tileSize) * player, 0);

    colors.push_back(sf::Color(0, 0, 0, 0)); // Empty
    colors.push_back(sf::Color::Cyan); // I
    colors.push_back(sf::Color(255, 165, 0)); // L
    colors.push_back(sf::Color::Blue); // J
    colors.push_back(sf::Color::Yellow); // O
    colors.push_back(sf::Color::Green); // S
    colors.push_back(sf::Color::Red); // Z
    colors.push_back(sf::Color(138, 43, 226)); // T
}

void GameGrid::draw(sf::RenderWindow& window)
{
    texture.clear();
    texture.draw(grid);

    // Draw currently controlled tetromino
    sf::Vector2i currPos = currTetromino.getTilePosition();

    std::vector<std::vector<int>> tetrominoTiles = currTetromino.getTiles();
    sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
    for(int i = 0; i < tetrominoTiles.size(); ++i)
    {
        for(int j = 0; j < tetrominoTiles[0].size(); ++j)
        {
            tile.setFillColor(colors[tetrominoTiles[i][j]]);
            tile.setPosition(sf::Vector2f((j + currPos.x) * tileSize, (i + currPos.y) * tileSize));
            texture.draw(tile);
        }
    }
    
    // Draw laid tiles
    for(int i = 0; i < tiles.size(); ++i) // Y axis
    {
        for(int j = 0; j < tiles[0].size(); ++j) // X axis
        {
            tile.setFillColor(colors[tiles[i][j]]);
            tile.setPosition(sf::Vector2f(j * tileSize, i * tileSize));
            texture.draw(tile);
        }
    }

    // Draw Grid Lines
    texture.draw(gridLines);
    
    // Draw ghost tetromino
    ghostTetromino = currTetromino;
    placeGhostTetromino();
    tetrominoTiles = ghostTetromino.getTiles();

    sf::Vector2i ghostPos = ghostTetromino.getTilePosition();

    tile.setSize(sf::Vector2f(tileSize-1, tileSize-1));
    for(int i = 0; i < tetrominoTiles.size(); ++i)
    {
        for(int j = 0; j < tetrominoTiles[0].size(); ++j)
        {
            tile.setFillColor(colors[0]);
            tile.setOutlineThickness(1);
            tile.setOutlineColor(colors[tetrominoTiles[i][j]]);
            tile.setPosition(sf::Vector2f((j + ghostPos.x) * tileSize, (i + ghostPos.y) * tileSize));
            texture.draw(tile);
        }
    }

    texture.display();

    sprite.setTexture(texture.getTexture());
    window.draw(sprite);
}

void GameGrid::setPosition(sf::Vector2f pos)
{
    sprite.setPosition(pos);
}

/**
 * turnDirection: -1 = counter-clockwise
 *                 1 = clockwise
 *                 0 = no rotation
 *
 * drop: true = hard drop
 *       false = no drop
 *
 * moveDirection: -1 = move left
 *                 1 = move right
 *                 2 = move down
 *                 0 = dont move
 */
void GameGrid::update(int turnDirection, bool drop, int moveDirection)
{
    if(drop)
    {
        while(isPotentialMoveValid(0, 1, currTetromino))
            currTetromino.moveTilePosition(0, 1);
        
        placeCurrTetromino();
    }

    if(turnDirection == -1) currTetromino.rotate(false);
    else if(turnDirection == 1) currTetromino.rotate(true);

    if(moveDirection == -1)
    {
        if(isPotentialMoveValid(-1, 0, currTetromino))
            currTetromino.moveTilePosition(-1, 0);
    }
    else if(moveDirection == 1)
    {
        if(isPotentialMoveValid(1, 0, currTetromino))
            currTetromino.moveTilePosition(1, 0);
    }
    else if(moveDirection == 2)
    {
        if(isPotentialMoveValid(0, 1, currTetromino))
            currTetromino.moveTilePosition(0, 1);
        else
            placeCurrTetromino();
    }
}

void GameGrid::fallTetromino()
{
    if(isPotentialMoveValid(0, 1, currTetromino))
        currTetromino.moveTilePosition(0, 1);
    else
        placeCurrTetromino();
}

float GameGrid::getFallSpeed()
{
    return fallSpeed;
}
