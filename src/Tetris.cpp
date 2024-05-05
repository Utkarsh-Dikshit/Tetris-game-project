#include <iostream>
#include <fstream>
#include "game.h"

int screen_width = 330, screen_height = 620;
int sideWindow_width = 300;
double lastUpdateTime = 0.0;

/* Add system for High score to be stored in a file*/
int main()
{
    Image icon = LoadImage("resources/icon/tetris.png");

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    
    InitWindow(screen_width + sideWindow_width, screen_height, "Tetris");
    SetWindowIcon(icon);

    SetWindowMinSize(screen_width + sideWindow_width, screen_height);
    
    InitAudioDevice();
    SetTargetFPS(60);
    Game game = Game();

    ifstream file("resources/data.txt");
    if (file.is_open())
    {
        file >> game.highscore;
        file.close();
    }

    ofstream outfile("resources/data.txt");

    PlayMusicStream(game.button.sound.OuterMusic);
    while (WindowShouldClose() == false && game.button.is_exitPressed == false)
    {

        BeginDrawing();
        ClearBackground(BLANK);

        if (game.button.is_playPressed == false)
        {
            game.DrawStart();
            if (game.button.gameMusic)
            {
                UpdateMusicStream(game.button.sound.OuterMusic);
                SetMusicVolume(game.button.sound.OuterMusic, 0.85);
            }
        }

        else
        {
            if (game.button.gameMusic)
            {
                SetMusicVolume(game.button.sound.InnerMusic, 0.85);
                UpdateMusicStream(game.button.sound.InnerMusic);
            }

            DrawTexturePro(game.start.BGtexture2, {0, game.scrolling, (float)game.start.BGtexture2.width, (float)game.start.BGtexture2.height}, {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, {0, 0}, 0, WHITE);

            DrawTextEx(game.button.font1, "SCORE", { (float)((GetScreenWidth() - 630)/ 1.5) + 438, 15}, 30, 2, WHITE);
            DrawRectangleRounded({(float)((GetScreenWidth() - 630)/ 1.5) + 402, 50, 167, 40}, 0.3, 7, lightBlue);
            DrawTextEx(game.button.font2, TextFormat("%i", game.score), {(float)((float)((GetScreenWidth() - 630)/ 1.5) + 402 + 167 / 2 - MeasureText(TextFormat("%i", game.score), 30) / 2), (float)(50 + 40 / 2 - 28 / 2)}, 30, 2.2, WHITE);

            DrawTextEx(game.button.font1, "HIGH SCORE", {(float)((GetScreenWidth() - 630)/ 1.5) + 402, 105}, 30, 2, WHITE);
            DrawRectangleRounded({(float)((GetScreenWidth() - 630)/ 1.5) + 402, 140, 167, 40}, 0.3, 7, lightBlue);
            DrawTextEx(game.button.font2, TextFormat("%i", game.highscore), {(float)((float)((GetScreenWidth() - 630)/ 1.5) + 402 + 167 / 2 - MeasureText(TextFormat("%i", game.highscore), 30) / 2), (float)(140 + 40 / 2 - 28 / 2)}, 30, 2.2, WHITE);

            DrawTextEx(game.button.font1, "NEXT BLOCK", {(float)((GetScreenWidth() - 630)/ 1.5) + 400, (float)((GetScreenHeight() - 620)/ 2) + 195}, 30, 2, WHITE);
            DrawRectangleRounded({(float)((GetScreenWidth() - 630)/ 1.5 + 396.5), (float)((GetScreenHeight() - 620)/ 2) + 230, 180, 120}, 0.3, 7, lightBlue);

            game.DrawMain();

            if (game.button.gamePause == false && game.button.gameOver == false)
            {
                if (game.eventTriggered(game.button.Interval, &lastUpdateTime))
                {
                    game.moveDown();
                }
                game.InputHandler();
            }

            game.UpdateHighScore();
        }
        EndDrawing();
    }

    if (outfile.is_open())
    {
        outfile << game.highscore;
        outfile.close();
    }
    
    UnloadImage(icon);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
