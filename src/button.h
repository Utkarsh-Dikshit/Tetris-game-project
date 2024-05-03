#pragma once
#include "raylib.h"

class sounds{
public:
    sounds();
    Sound GameOver;
    Sound Hover;
    Sound blockMovement;
    Sound RotateBLock;
    Sound RowCleared;
    Sound BlockPlaced;
    Music OuterMusic, InnerMusic;
};

class Button
{
public:
    Button();

    Texture2D ButtonPlayTex, ButtonExitTex, ButtonLevelTex, imBlank;
    Texture2D IconPlay, IconRestart, IconHome, IconMusic;

    Font font1, font2;

    struct button;

    void DrawIcon();
    void DrawButton();

    bool gamePause, gameReset, gameMusic, gameOver;
    bool is_playPressed, is_exitPressed;
    
    float Interval;
    sounds sound;
    
private:
    int btnState, icnState;
    int ImageSelection_Level_Button, ImageSelection_Level_Icon_play, ImageSelection_Level_Icon_music;

    bool is_levelPressed;
    
    void ButtonPressed(button button, int button_No, float position_x);
    void IconPressed(button button, int button_No, float position_y);

    void linkButtonPressed(button *button);

    void CreateMenu();
    void InitButton(button *button, Rectangle rec, Texture2D ButtonTex, Color color);
    
    void Initialize_scrolling_Var();
    float scrolling_button_bg_Ver, scrolling_buttons_Hor, scrolling_icons_bg_Hor, scrolling_icons_Ver;
};
