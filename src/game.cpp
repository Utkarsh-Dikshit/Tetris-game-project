#include "game.h"
#include <random>

Game::Game()
{
    grid = Grid();
    all_blocks = GetAllBlocks();
    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    // sound = sounds();
}

block Game::GetRandomBlock()
{
    /* In the original game, each block appears atleast once before reapeating the cycle*/
    /* here rand function return random number [0, 7)*/

    if (all_blocks.empty())
    {
        all_blocks = GetAllBlocks();
    }

    int randomIndex = rand() % all_blocks.size();
    block block = all_blocks[randomIndex];
    all_blocks.erase(all_blocks.begin() + randomIndex);
    return block;
}

vector<block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), ZBlock(), TBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currBlock.DrawBlock(10, 10);

    /* For Drawing Reference Block at appropriate location*/
    IsReferenceBlockOutside();
    currBlock.DrawReferenceBlock(10, 10);
    currBlock.row_offset_referenceBlock = 0;

    if (nextBlock.id == 3)
    {
        nextBlock.DrawBlock(305, 232);
    }
    else if (nextBlock.id == 4)
    {
        nextBlock.DrawBlock(305, 220);
    }
    else
    {
        nextBlock.DrawBlock(290, 220);
    }
}

void Game::moveLeft()
{
    if (!gameOver)
    {
        currBlock.Move(0, -1);
        

        if (IsBlockOutside())
        {
            currBlock.Move(0, 1);
        }
    }
}
void Game::moveRight()
{
    if (!gameOver)
    {
        currBlock.Move(0, 1);

        if (IsBlockOutside())
        {
            currBlock.Move(0, -1);
        }
    }
}
void Game::moveDown()
{
    if (!gameOver)
    {
        currBlock.Move(1, 0);

        if (IsBlockOutside())
        {
            currBlock.Move(-1, 0);
            FixBlock();
        }
    }
}

void Game::Rotate()
{
    if (!gameOver)
    {
        currBlock.Rotate();

        if (IsBlockOutside())
        {
            currBlock.UnDoRoatation();
        }
    }
}

bool Game::IsBlockOutside()
{
    if (IsCollision())
    {
        return true;
    }
    return false;
}

void Game::InputHandler()
{
    int keyPressed = GetKeyPressed();
    // if keyPressed = 0, means that no key is pressed
    if (gameOver && keyPressed != 0)
    {
        gameOver = false;
        reset();
    }
    switch (keyPressed)
    {
    case KEY_LEFT:
        moveLeft();
        break;

    case KEY_RIGHT:
        moveRight();
        break;

    case KEY_DOWN:
        moveDown();
        UpdateScore(0, 5);
        break;

    case KEY_UP:
        Rotate();
        break;
    }
}

void Game::FixBlock()
{
    vector<position> tiles = currBlock.GetcellPosition();

    for (position item : tiles)
    {
        grid.grid[item.row_index][item.column_index] = currBlock.id;
    }

    currBlock = nextBlock;
    if (IsCollision())
    {
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int CompletedRow = grid.ClearFullRow();
    UpdateScore(CompletedRow, 0);
}

void Game::MoveReferenceBlockUP()
{
    currBlock.MoveReferenceBlock(-1);
}

void Game::MoveReferenceBlockDOWN()
{
    currBlock.MoveReferenceBlock(1);
}

void Game::IsReferenceBlockOutside()
{
    for (; IsBelowRowEmpty() == true;)
    {
        MoveReferenceBlockDOWN();
    }
    for (; IsCurrentSpaceFree() == false;)
    {
        MoveReferenceBlockUP();
    }
}

bool Game::IsBelowRowEmpty()
{
    vector<position> tiles = currBlock.GetcellPositionForReferenceBLock();
    bool is_allCellEmpty = false;
    for (position item : tiles)
    {
        if (grid.grid[item.row_index + 1][item.column_index] == 0 && item.row_index + 1 <= 19)
        {
            is_allCellEmpty = true;
        }
        else
        {
            return false;
        }
    }
    return is_allCellEmpty;
}

bool Game::IsCurrentSpaceFree()
{
    vector<position> tiles = currBlock.GetcellPositionForReferenceBLock();
    bool is_allCellEmpty = true;
    for (position item : tiles)
    {
        if (grid.grid[item.row_index][item.column_index] != 0 || item.row_index > 19)
        {
            return false;
        }
    }
    return is_allCellEmpty;
}

bool Game::IsCollision()
{
    vector<position> tiles = currBlock.GetcellPosition();
    for (position item : tiles)
    {
        if (grid.IsCellOutside(item.row_index, item.column_index) || grid.grid[item.row_index][item.column_index] != 0)
        {
            return true;
        }
    }
    return false;
}

void Game::UpdateScore(int NumberOfCompletedRow, int BlockMoveDown)
{

    if (NumberOfCompletedRow == 1)
    {
        score += 100;
    }
    else if (NumberOfCompletedRow == 2)
    {
        score += 300;
    }
    else if (NumberOfCompletedRow == 3)
    {
        score += 500;
    }
    else if (NumberOfCompletedRow == 4)
    {
        score += 700;
    }
    score += BlockMoveDown;
}

void Game::reset()
{
    grid.Initialize();
    all_blocks = GetAllBlocks();
    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();

    score = 0;
}