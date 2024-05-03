#pragma once
#include "sound.h"

class Button
{
public:
    Button();

    Texture2D ButtonPlayTex, ButtonExitTex, ButtonLevelTex, imBlank;
    Texture2D IconPlay, IconReset, IconHome, IconMusic, IconShowControls;

    Font font1, font2;

    struct button;

    void DrawIcon();
    void DrawButton();

    bool gamePause, gameReset, gameMusic, gameOver;
    bool is_playPressed, is_exitPressed, is_controlShown;
    
    float Interval;
    sounds sound;
    
private:
    int btnState, icnState;
    int ImageSelection_Level_Button, ImageSelection_Level_Icon_play, ImageSelection_Level_Icon_music, ImageSelection_Level_Icon_ShowControl;

    bool is_levelPressed;
    
    void ButtonPressed(button button, int button_No, float position_x);
    void IconPressed(button button, int button_No, float position_y);

    void linkButtonPressed(button *button);

    void CreateMenu();
    void InitButton(button *button, Rectangle rec, Texture2D ButtonTex, Color color);
    
    void Initialize_scrolling_Var();
    float scrolling_button_Ver, scrolling_buttons_Hor, scrolling_icons_Hor, scrolling_icons_Ver;
};
