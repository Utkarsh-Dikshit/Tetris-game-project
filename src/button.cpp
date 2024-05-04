#include "button.h"

Button::Button()
{
    ButtonPlayTex = LoadTexture("resources/Images/button/buttonPlay.png");
    ButtonExitTex = LoadTexture("resources/Images/button/buttonExit.png");
    ButtonLevelTex = LoadTexture("resources/Images/button/buttonLevel.png");
    IconShowControls = LoadTexture("resources/Images/button/ShowControl.png");

    IconPlay = LoadTexture("resources/Images/button/PlayPause.png");
    IconReset = LoadTexture("resources/Images/button/Restart.png");
    IconHome = LoadTexture("resources/Images/button/Home.png");
    IconMusic = LoadTexture("resources/Images/button/Music.png");
    imBlank = LoadTexture("resources/Images/button/imBlank.png");

    font1 = LoadFontEx("resources/font/font.ttf", 64, 0, 0);
    font2 = LoadFontEx("resources/font/font(1).otf", 64, 0, 0);

    btnState = 0;
    icnState = 0;

    is_playPressed = false;
    is_levelPressed = false;
    is_exitPressed = false;
    is_controlShown = false;

    gamePause = false;
    gameReset = false;
    gameMusic = true;

    gameOver = false;

    ImageSelection_Level_Button = 0;
    ImageSelection_Level_Icon_play = 3;
    ImageSelection_Level_Icon_music = 0;

    ImageSelection_Level_Icon_ShowControl = 0;

    Interval = 1.0; /* in seconds*/

    /* Marking initial position out of the window for scrolling effect*/
    Initialize_scrolling_Var();

    sound = sounds();

    CreateMenu();
}

struct Button::button
{
    Rectangle rec;
    Texture2D ButtonTex;
    Color color;
};

Button::button play, level, Exit, link, icon_play, icon_music, icon_home, icon_reset, icon_show_control;

void Button::InitButton(button *button, Rectangle rec, Texture2D ButtonTex, Color color)
{
    button->rec = rec;
    button->ButtonTex = ButtonTex;
    button->color = color;
}

void Button::CreateMenu()
{
    InitButton(&play, Rectangle{(float)(GetScreenWidth() - 176) / 2, 353.3, 176, 75}, ButtonPlayTex, WHITE);
    InitButton(&level, Rectangle{(float)(GetScreenWidth() - 176) / 2, 353.3 + 75 + 18, 176, 75}, ButtonLevelTex, WHITE);
    InitButton(&Exit, Rectangle{(float)(GetScreenWidth() - 176) / 2, 353.3 + 75 + 18 + 75 + 18, 176, 75}, ButtonExitTex, WHITE);
    InitButton(&icon_show_control, Rectangle{(float)GetScreenWidth() - 75, (float)(GetScreenHeight() - 67), 50, 50}, IconShowControls, WHITE);
    InitButton(&link, Rectangle{5, (float)(GetScreenHeight() - 35), 170 + 10, 30}, imBlank, ORANGE);

    InitButton(&icon_play, Rectangle{(float)((GetScreenWidth() - 630)/ 1.5 + (373.6)), (float)(GetScreenHeight() - 72.5), 50, 50}, IconPlay, WHITE);
    InitButton(&icon_reset, Rectangle{(float)((GetScreenWidth() - 630)/ 1.5 + (432.2)), (float)(GetScreenHeight() - 72.5), 50, 50}, IconReset, WHITE);
    InitButton(&icon_home, Rectangle{(float)((GetScreenWidth() - 630)/ 1.5 + (490.8)), (float)(GetScreenHeight() - 72.5), 50, 50}, IconHome, WHITE);
    InitButton(&icon_music, Rectangle{(float)((GetScreenWidth() - 630)/ 1.5 + (549.4)), (float)(GetScreenHeight() - 72.5), 50, 50}, IconMusic, WHITE);
}

void Button::Initialize_scrolling_Var()
{
    scrolling_button_Ver = GetScreenHeight() + 50;
    scrolling_buttons_Hor = GetScreenWidth() + 50;
    scrolling_icons_Hor = GetScreenWidth() + 50;
    scrolling_icons_Ver = GetScreenHeight() + 50;
}

void Button::ButtonPressed(button button, int button_No, float position_x)
{
    // Check button state
    if (CheckCollisionPointRec(GetMousePosition(), {position_x + 13, button.rec.y + 12, button.rec.width - (2 * 13.5f), button.rec.height - (2 * 12)}))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameMusic == true)
        {
            PlaySound(sound.ButtonSound1);
        }

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
            if (gameMusic)
            {
                PlaySound(sound.ButtonSound2);
            }

            if (button_No == 1)
            {
                StopMusicStream(sound.OuterMusic);
                if (gameMusic)
                {
                    PlayMusicStream(sound.InnerMusic);
                }
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
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameMusic == true)
        {
            PlaySound(sound.iconSound1);
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if (Icon_No == 0)
            {
                icnState = 2 + ImageSelection_Level_Icon_ShowControl;
            }
            else if (Icon_No == 1)
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
            if (Icon_No == 0)
            {
                icnState = 1 + ImageSelection_Level_Icon_ShowControl;
            }
            else if (Icon_No == 1)
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
            if (gameMusic)
            {
                PlaySound(sound.iconSound2);
            }

            if (Icon_No == 0)
            {
                ImageSelection_Level_Icon_ShowControl += 3;
                if (ImageSelection_Level_Icon_ShowControl >= 6)
                {
                    ImageSelection_Level_Icon_ShowControl = 0;
                }
                is_controlShown = !is_controlShown;
            }
            else if (Icon_No == 1)
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
                if (gameOver == true && gameMusic)
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
                if (gameMusic)
                {
                    StopMusicStream(sound.InnerMusic);
                    PlayMusicStream(sound.OuterMusic);
                }
            }
            else if (Icon_No == 4)
            {
                ImageSelection_Level_Icon_music += 3;
                if (ImageSelection_Level_Icon_music >= 6)
                {
                    ImageSelection_Level_Icon_music = 0;
                }
                gameMusic = !gameMusic;
            }
        }
    }
    else
    {
        if (Icon_No == 0)
        {
            icnState = ImageSelection_Level_Icon_ShowControl;
        }
        else if (Icon_No == 1)
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
            button->color = RED;
        }
        else
        {
            button->color = YELLOW;
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
    if (IsWindowResized()) 
    {
        Initialize_scrolling_Var();
        CreateMenu();
    }

    scrolling_button_Ver -= 15;
    if (scrolling_button_Ver <= 315)
    {
        scrolling_button_Ver = 315;
    }

    scrolling_buttons_Hor -= 15;
    if (scrolling_buttons_Hor <= play.rec.x)
    {
        scrolling_buttons_Hor = play.rec.x;
    }

    if (is_controlShown == false)
    {        
        DrawRectangleRounded({(float)(GetScreenWidth() - (176 + 64))/2, scrolling_button_Ver, 176 + 64, (float)GetScreenHeight()}, 1.5, 7, {255, 255, 255, 150});


        float frameHeight = (float)play.ButtonTex.height / 3;
        ButtonPressed(play, 1, scrolling_buttons_Hor);
        DrawTexturePro(play.ButtonTex, {0, btnState * frameHeight, (float)(play.ButtonTex.width), frameHeight}, {scrolling_buttons_Hor, play.rec.y, play.rec.width, play.rec.height}, {0, 0}, 0, play.color);

        ButtonPressed(level, 2, scrolling_buttons_Hor);
        frameHeight = (float)level.ButtonTex.height / 9;
        DrawTexturePro(level.ButtonTex, {0, btnState * frameHeight, (float)(level.ButtonTex.width), frameHeight}, {scrolling_buttons_Hor, level.rec.y, level.rec.width, level.rec.height}, {0, 0}, 0, level.color);

        ButtonPressed(Exit, 3, scrolling_buttons_Hor);
        frameHeight = (float)Exit.ButtonTex.height / 3;
        DrawTexturePro(Exit.ButtonTex, {0, btnState * frameHeight, (float)(Exit.ButtonTex.width), frameHeight}, {scrolling_buttons_Hor, Exit.rec.y, Exit.rec.width, Exit.rec.height}, {0, 0}, 0, Exit.color);
    }
    
    DrawRectangleRounded({icon_show_control.rec.x - 5 - (play.rec.x) + scrolling_buttons_Hor, icon_show_control.rec.y - 5, icon_show_control.rec.width + 10, icon_show_control.rec.height + 10}, 0.5, 7, {0, 0, 0, 200});
    IconPressed(icon_show_control, 0, 5 + icon_show_control.rec.y - 315 + scrolling_button_Ver);
    DrawTexturePro(icon_show_control.ButtonTex, {0, (float)(icnState * 50), 50, 50}, {icon_show_control.rec.x, icon_show_control.rec.y - 315 + scrolling_button_Ver, icon_show_control.rec.width, icon_show_control.rec.height}, {0, 0}, 0, WHITE);

    linkButtonPressed(&link);
    DrawRectangleRounded({link.rec.x + (play.rec.x) - scrolling_buttons_Hor, link.rec.y, link.rec.width, link.rec.height}, 1.5, 6, {0, 0, 0, 150});
    DrawTextEx(font2, "@Utkarsh-Dikshit", {5 + link.rec.x, 5 + link.rec.y - (315) + scrolling_button_Ver}, 20, 2, link.color);
}

void Button::DrawIcon()
{
    if (IsWindowResized()) 
    {
        Initialize_scrolling_Var();
        CreateMenu();
    }
    scrolling_icons_Hor -= 10;
    if (scrolling_icons_Hor <= ((float)((GetScreenWidth() - 630)/ 1.5) + 365))
    {
        scrolling_icons_Hor = ((float)((GetScreenWidth() - 630)/ 1.5) + 365);
    }
    DrawRectangleRounded({scrolling_icons_Hor, (float)GetScreenHeight() - 77, 163 + 80, 60}, 0.5, 7, {255, 255, 255, 150});

    float frameHeight = 50.0;

    scrolling_icons_Ver -= 5;
    if (scrolling_icons_Ver <= icon_play.rec.y)
    {
        scrolling_icons_Ver = icon_play.rec.y;
    }

    IconPressed(icon_play, 1, scrolling_icons_Ver);
    DrawTexturePro(icon_play.ButtonTex, {0, icnState * frameHeight, (float)(icon_play.ButtonTex.width), frameHeight}, {icon_play.rec.x, scrolling_icons_Ver, icon_play.rec.width, icon_play.rec.height}, {0, 0}, 0, WHITE);

    IconPressed(icon_reset, 2, scrolling_icons_Ver);
    DrawTexturePro(icon_reset.ButtonTex, {0, icnState * frameHeight, (float)(icon_reset.ButtonTex.width), frameHeight}, {icon_reset.rec.x, scrolling_icons_Ver, icon_reset.rec.width, icon_reset.rec.height}, {0, 0}, 0, WHITE);

    IconPressed(icon_home, 3, scrolling_icons_Ver);
    DrawTexturePro(icon_home.ButtonTex, {0, icnState * frameHeight, (float)(icon_home.ButtonTex.width), frameHeight}, {icon_home.rec.x, scrolling_icons_Ver, icon_home.rec.width, icon_home.rec.height}, {0, 0}, 0, WHITE);

    IconPressed(icon_music, 4, scrolling_icons_Ver);
    DrawTexturePro(icon_music.ButtonTex, {0, icnState * frameHeight, (float)(icon_music.ButtonTex.width), frameHeight}, {icon_music.rec.x, scrolling_icons_Ver, icon_music.rec.width, icon_music.rec.height}, {0, 0}, 0, WHITE);
}