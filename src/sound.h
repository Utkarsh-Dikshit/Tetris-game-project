#pragma once

#include "raylib.h"

class sounds{
public:
    sounds();
    Sound GameOver;
    Sound ButtonSound1, ButtonSound2;
    Sound iconSound1, iconSound2;
    Sound blockMovement;
    Sound RotateBLock;
    Sound RowCleared;
    Sound BlockPlaced;
    Sound HighScore;
    Music OuterMusic, InnerMusic;
};