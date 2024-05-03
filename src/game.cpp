#include "game.h"
#include <random>

Game::Game()
{
    grid = Grid();

    all_blocks = GetAllBlocks();
    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();

    currentRefBlockRowPos = 0;
    
    score = 0;
    highscore = 0;
    highscore_updated = true;

    // For maintaining the speed of the blocks
    last_up_time_BlockMovement = 0.0;
    // For maintaining the duration for message display
    last_up_time_MessageDisplay = 0.0;

    start = startWindow();
    button = Button();

    MessageTex1 = LoadTexture("resources/Images/Messages/Message1.png");
    MessageTex2 = LoadTexture("resources/Images/Messages/Message2.png");
    MessageTex3 = LoadTexture("resources/Images/Messages/Message3.png");
    MessageTex4 = LoadTexture("resources/Images/Messages/Message4.png");
    MessageTex5 = LoadTexture("resources/Images/Messages/Message5.png");
    MessageTex6 = LoadTexture("resources/Images/Messages/HighScoreMessage.png");
    gameOverTex = LoadTexture("resources/Images/Messages/GameOver.png");

    InitializeMessageTex();
    randomMessageIndex = GetRandomValue(0, MessageTex.size() - 2);
}

Game::~Game()
{
    UnloadTexture(start.BGtexture);
    UnloadTexture(start.MainLogoTexture);

    UnloadTexture(start.LBlockTex);
    UnloadTexture(start.JBlockTex);
    UnloadTexture(start.OBlockTex);
    UnloadTexture(start.IBlockTex);
    UnloadTexture(start.TBlockTex);
    UnloadTexture(start.SBlockTex);
    UnloadTexture(start.ZBlockTex);

    UnloadTexture(button.ButtonPlayTex);
    UnloadTexture(button.ButtonExitTex);
    UnloadTexture(button.ButtonLevelTex);
    UnloadTexture(button.imBlank);
    UnloadTexture(button.IconPlay);
    UnloadTexture(button.IconRestart);
    UnloadTexture(button.IconHome);
    UnloadTexture(button.IconMusic);

    UnloadTexture(MessageTex1);
    UnloadTexture(MessageTex2);
    UnloadTexture(MessageTex3);
    UnloadTexture(MessageTex4);
    UnloadTexture(MessageTex5);
    UnloadTexture(MessageTex6);
    UnloadTexture(gameOverTex);

    UnloadFont(button.font1);
    UnloadFont(button.font2);

    UnloadSound(button.sound.RowCleared);
    UnloadSound(button.sound.Hover);
    UnloadSound(button.sound.blockMovement);
    UnloadSound(button.sound.BlockPlaced);
    UnloadSound(button.sound.RotateBLock);
    UnloadSound(button.sound.GameOver);
    UnloadMusicStream(button.sound.OuterMusic);
    UnloadMusicStream(button.sound.InnerMusic);
}

void Game::DrawStart()
{
    start.Draw();
    button.DrawButton();
}

void Game::DrawMain()
{

    grid.Draw();
    currBlock.DrawBlock(11, 11);

    /* For Drawing Reference Block at appropriate location*/
    SetReferenceBlockPosition();
    currBlock.DrawReferenceBlock(11, 11);
    currentRefBlockRowPos = currBlock.row_offset_referenceBlock;
    currBlock.row_offset_referenceBlock = 0;

    if (nextBlock.id == 3)
    {
        nextBlock.DrawBlock(335, 272);
    }
    else if (nextBlock.id == 4)
    {
        nextBlock.DrawBlock(335, 260);
    }
    else
    {
        nextBlock.DrawBlock(320, 260);
    }

    if (isMessageDisplay == true)
    {
        DrawRandomMessage();
        if (eventTriggered(6.00, &last_up_time_MessageDisplay))
        {
            randomMessageIndex = GetRandomValue(0, MessageTex.size() - 2);
            isMessageDisplay = false;
        }
    }

    button.DrawIcon();

    if (button.gameOver == true)
    {
        DrawTexturePro(gameOverTex, {0, 0, 163, 163}, {394 - 14 + 22.5, 380, 163, 163}, {0, 0}, 0, WHITE);
    }

    if (button.gameReset == true)
    {
        reset();
    }
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

void Game::InitializeMessageTex()
{
    MessageTex = {MessageTex1, MessageTex2, MessageTex3, MessageTex4, MessageTex5, MessageTex6};
    isMessageDisplay = false;
}

void Game::DrawRandomMessage()
{
    DrawTexturePro(MessageTex[randomMessageIndex], {0, 0, 135, 135}, {394 + 22.5, 380, 135, 135}, {0, 0}, 0, WHITE);
}

void Game::moveLeft()
{
    currBlock.Move(0, -1);
    if (IsBlockOutside() || !IsCurrBlockSpaceFree())
    {
        currBlock.Move(0, 1);
    }
    else
    {
        PlaySound(button.sound.blockMovement);
    }
}
void Game::moveRight()
{
    currBlock.Move(0, 1);
    if (IsBlockOutside() || (IsCurrBlockSpaceFree() == false))
    {
        currBlock.Move(0, -1);
    }
    else
    {
        PlaySound(button.sound.blockMovement);
    }
}
void Game::moveDown()
{
    currBlock.Move(1, 0);
    if (IsBlockOutside() || (IsCurrBlockSpaceFree() == false))
    {
        currBlock.Move(-1, 0);
        FixBlock();
    }
    else
    {
        PlaySound(button.sound.blockMovement);
    }
}


void Game::Rotate()
{
    currBlock.Rotate();
    if (IsBlockOutside() || (IsCurrBlockSpaceFree() == false))
    {
        currBlock.UnDoRoatation();
    }
    else
    {
        PlaySound(button.sound.RotateBLock);
    }
}

bool Game::IsBlockOutside()
{
    vector<position> tiles = currBlock.GetcellPosition();
    for (position item : tiles)
    {
        if (grid.IsCellOutside(item.row_index, item.column_index))
        {
            return true;
        }
    }
    return false;
}

bool Game::eventTriggered(double Interval, double *lastUpdateTime)
{
    double currentTime = GetTime();
    if (currentTime - *lastUpdateTime >= Interval)
    {
        *lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

void Game::InputHandler()
{
    if (IsKeyDown(KEY_LEFT))
    {
        if (eventTriggered(0.07, &last_up_time_BlockMovement))
        {
            moveLeft();
        }
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        if (eventTriggered(0.07, &last_up_time_BlockMovement))
        {
            moveRight();
        }
    }
    if (IsKeyDown(KEY_DOWN))
    {
        if (eventTriggered(0.07, &last_up_time_BlockMovement))
        {
            moveDown();
            UpdateScore(0, 1);
        }
    }
    if (IsKeyPressed(KEY_UP))
    {
        Rotate();
    }
    if (IsKeyPressed(KEY_SPACE))
    {
        currBlock.Move(currentRefBlockRowPos, 0);
    }
}

void Game::MoveReferenceBlockUP()
{
    currBlock.MoveReferenceBlock(-1);
}

void Game::MoveReferenceBlockDOWN()
{
    currBlock.MoveReferenceBlock(1);
}

void Game::SetReferenceBlockPosition()
{
    for (; IsBelowRowEmpty() == true;)
    {
        MoveReferenceBlockDOWN();
    }
    for (; IsRefBlockSpaceFree() == false;)
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

bool Game::IsRefBlockSpaceFree()
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

void Game::FixBlock()
{
    vector<position> tiles = currBlock.GetcellPosition();

    PlaySound(button.sound.BlockPlaced);
    for (position item : tiles)
    {
        grid.grid[item.row_index][item.column_index] = currBlock.id;
    }

    currBlock = nextBlock;

    if (IsCurrBlockSpaceFree() == false)
    {
        StopMusicStream(button.sound.InnerMusic);
        PlaySound(button.sound.GameOver);
        button.gameOver = true;
    }

    nextBlock = GetRandomBlock();

    int CompletedRow = grid.ClearFullRow();
    if (CompletedRow > 0)
    {
        PlaySound(button.sound.RowCleared);
        UpdateScore(CompletedRow, 0);
        isMessageDisplay = true;
        last_up_time_MessageDisplay = GetTime();
    }
}

bool Game::IsCurrBlockSpaceFree()
{
    vector<position> tiles = currBlock.GetcellPosition();
    for (position item : tiles)
    {
        if (grid.grid[item.row_index][item.column_index] != 0)
        {
            return false;
        }
    }
    return true;
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

void Game::UpdateHighScore()
{
    if (highscore < score)
    {
        if(highscore_updated == true)
        {
            randomMessageIndex = 5;
            highscore_updated = false;
            last_up_time_MessageDisplay = GetTime();
        }
        highscore = score;
    }
}

void Game::reset()
{
    grid.Initialize();
    all_blocks = GetAllBlocks();
    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
    button.gameReset = false;
    highscore_updated = true;
}
