#include <iostream>
#include <fstream>
#include "game.h"

int screen_width = 330, screen_height = 620;
int sideWindow_width = 300;
double lastUpdateTime = 0.0;

/* Add system for High score to be stored in a file*/
int main()
{
    InitWindow(screen_width + sideWindow_width, screen_height, "Tetris");
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
        ClearBackground(darkBlue);

        if (game.button.is_playPressed == false)
        {
            game.DrawStart();
            if (game.button.gameMusic)
            {
                UpdateMusicStream(game.button.sound.OuterMusic);
                SetMusicVolume(game.button.sound.OuterMusic, 0.75);
            }
        }

        else
        {
            if (game.button.gameMusic)
            {
                SetMusicVolume(game.button.sound.InnerMusic, 0.75);
                UpdateMusicStream(game.button.sound.InnerMusic);
            }
            
            DrawTextEx(game.button.font1, "SCORE", {438, 15}, 30, 2, WHITE);
            DrawRectangleRounded({402, 50, 167, 40}, 0.3, 7, lightBlue);
            DrawTextEx(game.button.font2, TextFormat("%i", game.score), {(float)(402 + 167 / 2 - MeasureText(TextFormat("%i", game.score), 30) / 2), (float)(50 + 40 / 2 - 28 / 2)}, 30, 2.2, WHITE);

            DrawTextEx(game.button.font1, "HIGH SCORE", {402, 105}, 30, 2, WHITE);
            DrawRectangleRounded({402, 140, 167, 40}, 0.3, 7, lightBlue);
            DrawTextEx(game.button.font2, TextFormat("%i", game.highscore), {(float)(402 + 167 / 2 - MeasureText(TextFormat("%i", game.highscore), 30) / 2), (float)(140 + 40 / 2 - 28 / 2)}, 30, 2.2, WHITE);

            DrawTextEx(game.button.font1, "NEXT BLOCK", {400, 195}, 30, 2, WHITE);
            DrawRectangleRounded({396.5, 230, 180, 120}, 0.3, 7, lightBlue);

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
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
