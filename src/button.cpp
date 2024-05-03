#include "button.h"

Button::Button()
{
    
    ButtonPlayTex = LoadTexture("resources/Images/button/buttonPlay.png");
    ButtonExitTex = LoadTexture("resources/Images/button/buttonExit.png");
    ButtonLevelTex = LoadTexture("resources/Images/button/buttonLevel.png");
    IconPlay = LoadTexture("resources/Images/button/PlayPause.png");
    IconRestart = LoadTexture("resources/Images/button/Restart.png");
    IconHome = LoadTexture("resources/Images/button/Home.png");
    IconMusic = LoadTexture("resources/Images/button/Music.png");
    imBlank = LoadTexture("resources/Images/button/imBlank.png");

    font1 = LoadFontEx("resources/font/font.ttf", 64, 0, 0);
    font2 = LoadFontEx("resources/font/font(1).otf", 64, 0, 0);

    btnState = 0;
    icnState = 0;

    is_playPressed = false;
    is_exitPressed = false;
    is_levelPressed = false;

    gamePause = false;
    gameReset = false;
    gameMusic = false;
    gameOver = false;

    ImageSelection_Level_Button = 0;
    ImageSelection_Level_Icon_play = 3;
    ImageSelection_Level_Icon_music = 0;

    Interval = 1.0; /* in seconds*/

    /* Marking initial position out of the window for scrolling effect*/
    Initialize_scrolling_Var();
    sound = sounds();
    CreateMenu();

}

sounds:: sounds(){
    GameOver = LoadSound("resources/sounds/GameOver.wav");
    RotateBLock = LoadSound("resources/sounds/RotateSound.ogg");
    RowCleared = LoadSound("resources/sounds/LineCleared.ogg");
    BlockPlaced = LoadSound("resources/sounds/BlockPlaced.ogg");
    blockMovement = LoadSound("resources/sounds/blockMovement.ogg");
    Hover = LoadSound("resources/sounds/Button Hover.mp3");

    OuterMusic = LoadMusicStream("resources/sounds/OuterBG.mp3");
    InnerMusic = LoadMusicStream("resources/sounds/InnerBg.mp3");
}

struct Button::button
{
    Rectangle rec;
    Texture2D ButtonTex;
    Color color;
};

Button::button play, level, Exit, link, icon_play, icon_music, icon_home, icon_restart;

void Button::InitButton(button *button, Rectangle rec, Texture2D ButtonTex, Color color)
{
    button->rec = rec;
    button->ButtonTex = ButtonTex;
    button->color = color;
}

void Button::CreateMenu()
{
    InitButton(&play, Rectangle{197 + 32, 353.3, 176, 75}, ButtonPlayTex, WHITE);
    InitButton(&level, Rectangle{197 + 32, 353.3 + 75 + 18, 176, 75}, ButtonLevelTex, WHITE);
    InitButton(&Exit, Rectangle{197 + 32, 353.3 + 75 + 18 + 75 + 18, 176, 75}, ButtonExitTex, WHITE);
    InitButton(&link, Rectangle{5, 590 - 5, 170 + 10, 30}, imBlank, WHITE);

    InitButton(&icon_play, Rectangle{365 + 8.6, 558, 50, 50}, IconPlay, WHITE);
    InitButton(&icon_restart, Rectangle{
                                  365 + 50 + 2 * 8.6,
                                  558,
                                  50,
                                  50,
                              },
               IconRestart, WHITE);
    InitButton(&icon_home, Rectangle{365 + 2 * 50 + 3 * 8.6, 558, 50, 50}, IconHome, WHITE);
    InitButton(&icon_music, Rectangle{365 + 3 * 50 + 4 * 8.6, 558, 50, 50}, IconMusic, WHITE);
}

void Button::Initialize_scrolling_Var()
{
    scrolling_button_bg_Ver = 640;
    scrolling_buttons_Hor = 640;
    scrolling_icons_bg_Hor = 640;
    scrolling_icons_Ver = 670;
}

void Button::ButtonPressed(button button, int button_No, float position_x)
{
    // Check button state
    if (CheckCollisionPointRec(GetMousePosition(), {position_x + 13, button.rec.y + 12, button.rec.width - (2 * 13.5f), button.rec.height - (2 * 12)}))
    {
        PlaySound(sound.Hover);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if (button_No == 2)
            {
                btnState = 2 + ImageSelection_Level_Button;
            }
            else
            {
                btnState = 2;
            }
        }
        else
        {
            if (button_No == 2)
            {
                btnState = 1 + ImageSelection_Level_Button;
            }
            else
            {
                btnState = 1;
            }
        }

        // Button Action
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            if (button_No == 1)
            {
                StopMusicStream(sound.OuterMusic);
                PlayMusicStream(sound.InnerMusic);
                is_playPressed = true;
                gameOver = false;
                gameReset = true;
                gamePause = false;
                ImageSelection_Level_Icon_play = 3;
                Initialize_scrolling_Var();
            }
            else if (button_No == 2)
            {
                ImageSelection_Level_Button += 3;
                Interval -= 0.45;

                if (ImageSelection_Level_Button >= 9)
                {
                    ImageSelection_Level_Button = 0;
                    Interval = 1.0;
                }
            }
            else if (button_No == 3)
            {
                is_exitPressed = true;
            }
        }
    }
    else
    {
        if (button_No == 2)
        {
            btnState = ImageSelection_Level_Button;
        }
        else
        {
            btnState = 0;
        }
    }
}

void Button::IconPressed(button icon, int Icon_No, float position_y)
{
    // Check icon state
    if (CheckCollisionPointRec(GetMousePosition(), {icon.rec.x + 3, position_y + 2, icon.rec.width - 7, icon.rec.height - 5}))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if (Icon_No == 1)
            {
                icnState = 2 + ImageSelection_Level_Icon_play;
            }
            else if (Icon_No == 4)
            {
                icnState = 2 + ImageSelection_Level_Icon_music;
            }
            else
            {
                icnState = 2;
            }
        }
        else
        {
            if (Icon_No == 1)
            {
                icnState = 1 + ImageSelection_Level_Icon_play;
            }
            else if (Icon_No == 4)
            {
                icnState = 1 + ImageSelection_Level_Icon_music;
            }
            else
            {
                icnState = 1;
            }
        }

        // Icon Action
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            if (Icon_No == 1)
            {
                ImageSelection_Level_Icon_play += 3;
                if (ImageSelection_Level_Icon_play >= 6)
                {
                    ImageSelection_Level_Icon_play = 0;
                }
                gamePause = !gamePause;
            }
            else if (Icon_No == 2)
            {
                if (gameOver == true)
                {
                    PlayMusicStream(sound.InnerMusic);
                }
                gameReset = true;
                gameOver = false;
            }
            else if (Icon_No == 3)
            {
                is_playPressed = false;
                Initialize_scrolling_Var();
                StopMusicStream(sound.InnerMusic);
                PlayMusicStream(sound.OuterMusic);
            }
            else if (Icon_No == 4)
            {
                ImageSelection_Level_Icon_music += 3;
                if (ImageSelection_Level_Icon_music >= 6)
                {
                    ImageSelection_Level_Icon_music = 0;
                }
            }
        }
    }
    else
    {
        if (Icon_No == 1)
        {
            icnState = ImageSelection_Level_Icon_play;
        }
        else if (Icon_No == 4)
        {
            icnState = ImageSelection_Level_Icon_music;
        }
        else
        {
            icnState = 0;
        }
    }
}

void Button::linkButtonPressed(button *button)
{
    if (CheckCollisionPointRec(GetMousePosition(), button->rec))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            button->color = YELLOW;
        }
        else
        {
            button->color = RED;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            OpenURL("https://github.com/Utkarsh-Dikshit");
        }
    }
    else
    {
        button->color = ORANGE;
    }
}

void Button::DrawButton()
{
    scrolling_button_bg_Ver -= 15;
    if (scrolling_button_bg_Ver <= 315)
    {
        scrolling_button_bg_Ver = 315;
    }
    DrawRectangleRounded({197, /*315*/ scrolling_button_bg_Ver, 176 + 64, Exit.rec.y + 100}, 1.5, 7, {255, 255, 255, 150});

    scrolling_buttons_Hor -= 15;
    if (scrolling_buttons_Hor <= play.rec.x)
    {
        scrolling_buttons_Hor = play.rec.x;
    }

    float frameHeight = (float)play.ButtonTex.height / 3;
    ButtonPressed(play, 1, scrolling_buttons_Hor);
    DrawTexturePro(play.ButtonTex, {0, btnState * frameHeight, (float)(play.ButtonTex.width), frameHeight}, {scrolling_buttons_Hor, play.rec.y, play.rec.width, play.rec.height}, {0, 0}, 0, play.color);

    ButtonPressed(level, 2, scrolling_buttons_Hor);
    frameHeight = (float)level.ButtonTex.height / 9;
    DrawTexturePro(level.ButtonTex, {0, btnState * frameHeight, (float)(level.ButtonTex.width), frameHeight}, {scrolling_buttons_Hor, level.rec.y, level.rec.width, level.rec.height}, {0, 0}, 0, level.color);

    ButtonPressed(Exit, 3, scrolling_buttons_Hor);
    frameHeight = (float)Exit.ButtonTex.height / 3;
    DrawTexturePro(Exit.ButtonTex, {0, btnState * frameHeight, (float)(Exit.ButtonTex.width), frameHeight}, {scrolling_buttons_Hor, Exit.rec.y, Exit.rec.width, Exit.rec.height}, {0, 0}, 0, Exit.color);

    linkButtonPressed(&link);
    DrawRectangleRounded({5 + (315) - scrolling_button_bg_Ver, link.rec.y, link.rec.width, link.rec.height}, 1.5, 6, {0, 0, 0, 150});
    DrawTextEx(font2, "@Utkarsh-Dikshit", {10 + (315) - scrolling_button_bg_Ver, link.rec.y + 5}, 20, 2, link.color);
}

void Button::DrawIcon()
{
    scrolling_icons_bg_Hor -= 10;
    if (scrolling_icons_bg_Hor <= 365)
    {
        scrolling_icons_bg_Hor = 365;
    }
    DrawRectangleRounded({scrolling_icons_bg_Hor, 380 + 163 + 10, 163 + 80, 60}, 0.5, 7, {255, 255, 255, 150});

    float frameHeight = 50.0;

    scrolling_icons_Ver -= 4;
    if (scrolling_icons_Ver <= icon_play.rec.y)
    {
        scrolling_icons_Ver = icon_play.rec.y;
    }

    IconPressed(icon_play, 1, scrolling_icons_Ver);
    DrawTexturePro(icon_play.ButtonTex, {0, icnState * frameHeight, (float)(icon_play.ButtonTex.width), frameHeight}, {icon_play.rec.x, scrolling_icons_Ver, icon_play.rec.width, icon_play.rec.height}, {0, 0}, 0, WHITE);

    IconPressed(icon_restart, 2, scrolling_icons_Ver);
    DrawTexturePro(icon_restart.ButtonTex, {0, icnState * frameHeight, (float)(icon_restart.ButtonTex.width), frameHeight}, {icon_restart.rec.x, scrolling_icons_Ver, icon_restart.rec.width, icon_restart.rec.height}, {0, 0}, 0, WHITE);

    IconPressed(icon_home, 3, scrolling_icons_Ver);
    DrawTexturePro(icon_home.ButtonTex, {0, icnState * frameHeight, (float)(icon_home.ButtonTex.width), frameHeight}, {icon_home.rec.x, scrolling_icons_Ver, icon_home.rec.width, icon_home.rec.height}, {0, 0}, 0, WHITE);

    IconPressed(icon_music, 4, scrolling_icons_Ver);
    DrawTexturePro(icon_music.ButtonTex, {0, icnState * frameHeight, (float)(icon_music.ButtonTex.width), frameHeight}, {icon_music.rec.x, scrolling_icons_Ver, icon_music.rec.width, icon_music.rec.height}, {0, 0}, 0, WHITE);
}