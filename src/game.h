#pragma once

#include "grid.h"
#include "blocks.cpp"
// #include "sounds.h"

class Game
{
public:
    Game();
    void Draw();
    void InputHandler();
    void moveDown();
    bool gameOver;
    int score;
    // sounds sound;

private:
    vector<block> all_blocks;
    block GetRandomBlock();
    vector<block> GetAllBlocks();
    block currBlock;
    block nextBlock;
    Grid grid;
    void moveLeft();
    void moveRight();
    void Rotate();
    bool IsBlockOutside();
    bool IsCollision();

    void FixBlock();
    void UpdateScore(int NumberOfCompletedRow, int BlockMoveDown);
    void reset();

    void MoveReferenceBlockUP();
    void MoveReferenceBlockDOWN();
    void IsReferenceBlockOutside();
    bool IsBelowRowEmpty();
    bool IsCurrentSpaceFree();
};