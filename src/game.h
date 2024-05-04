#pragma once

#include "grid.h"
#include "blocks.cpp"
#include "startWindow.h"
#include "button.h"

class Game
{
public:
    Game();
    ~Game();

    bool eventTriggered(double interval, double *lastUpdateTime);

    void DrawMain();
    void DrawStart();
    
    void InputHandler();
    void moveDown();
    void UpdateHighScore();

    Texture2D gameOverTex;

    startWindow start;
    Button button;

    float scrolling;
    int score, highscore;

private:
    vector<block> all_blocks;
    block GetRandomBlock();
    vector<block> GetAllBlocks();

    block currBlock;
    block nextBlock;
    Grid grid;


    bool highscore_updated;

    void moveLeft();
    void moveRight();
    void Rotate();
    bool IsBlockOutside();
    bool IsCurrBlockSpaceFree();
    double last_up_time_BlockMovement, last_up_time_MessageDisplay;

    void FixBlock();
    void UpdateScore(int NumberOfCompletedRow, int BlockMoveDown);
    void reset();

    int currentRefBlockRowPos;
    void MoveReferenceBlockUP();
    void MoveReferenceBlockDOWN();
    void SetReferenceBlockPosition();
    bool IsBelowRowEmpty();
    bool IsRefBlockSpaceFree();

    int randomMessageIndex;
    bool isMessageDisplay;
    vector<Texture2D> MessageTex;
    Texture2D MessageTex1, MessageTex2, MessageTex3, MessageTex4, MessageTex5, MessageTex6;
    void InitializeMessageTex();
    void DrawRandomMessage();
};
