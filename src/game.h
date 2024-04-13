#pragma once

#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
    Game();
    block GetRandomBlock();
    vector<block> GetAllBlocks();
    void Draw();
    void InputHandler();

    void moveLeft();
    void moveRight();
    void moveDown();

    Grid grid;

private:
    /* We need to include all the block classes */
    vector<block> all_blocks;
    block currBlock;
    block nextBlock;
    bool IsBlockOutside();
};