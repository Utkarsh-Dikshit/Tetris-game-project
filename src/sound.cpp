#include "sound.h"

sounds::sounds()
{
    GameOver = LoadSound("resources/sounds/GameOver.wav");
    RotateBLock = LoadSound("resources/sounds/RotateSound.ogg");
    RowCleared = LoadSound("resources/sounds/LineCleared.ogg");
    BlockPlaced = LoadSound("resources/sounds/BlockPlaced.ogg");
    blockMovement = LoadSound("resources/sounds/blockMovement.ogg");
    HighScore = LoadSound("resources/sounds/HighScore.ogg");

    ButtonSound1 = LoadSound("resources/sounds/buttonSound1.ogg");
    ButtonSound2 = LoadSound("resources/sounds/buttonSound2.ogg");
    iconSound1 = LoadSound("resources/sounds/iconSound1.ogg");
    iconSound2 = LoadSound("resources/sounds/iconSound2.ogg");

    OuterMusic = LoadMusicStream("resources/sounds/OuterBG.mp3");
    InnerMusic = LoadMusicStream("resources/sounds/InnerBg.mp3");
}
