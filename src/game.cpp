#include "game.h"
#include <random>

Game::Game()
{
    grid = Grid();
    all_blocks = GetAllBlocks();
    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
}

block Game::GetRandomBlock()
{
    /* In the origin game, each block appears atleast once before reapeating the cycle*/
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

void Game:: Draw(){
    grid.Draw();
    currBlock.Draw();
}

void Game:: moveLeft(){
    currBlock.Move(0,-1); /* Move the block to the left column */
    
    if (IsBlockOutside()){
        currBlock.Move(0,1);
    }
}
void Game:: moveRight(){
    currBlock.Move(0,1); /* Move the block to the right column */
    if (IsBlockOutside()){
        currBlock.Move(0,-1);
    }
}
void Game:: moveDown(){
    currBlock.Move(1,0); /* Move the block to the left column */
    if (IsBlockOutside()){
        currBlock.Move(-1,0);
    }
}

bool Game::IsBlockOutside()
{
    vector <position> tiles = currBlock.GetcellPosition();
    for (position item : tiles){
        if (grid.IsCellOutside(item.row_index, item.column_index)){
            return true;
        }
        return false;
    }
}

void Game::InputHandler()
{
    int keyPressed = GetKeyPressed();
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
        break;
    }
}
