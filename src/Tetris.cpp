#include <iostream>
#include <raylib.h>
#include "game.h"

int screen_width = 330, screen_height = 620;
int sideWindow_width = 240;

double lastUpdateTime = 0.0;

bool eventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

/* Add system for High score to be stored in a file*/
int main()
{
    InitWindow(screen_width + sideWindow_width, screen_height, "Tetris");
    
    SetTargetFPS(60);

    Font font = LoadFontEx("font/font.otf", 64, 0, 0);
    
    Game game = Game();

    while (WindowShouldClose() == false)
    {
        // UpdateMusicStream(game.sound.music);

        BeginDrawing();
        ClearBackground(darkBlue);

        DrawTextEx(font, "SCORE", {410, 30}, 40, 2, WHITE);
        DrawTextEx(font, "NEXT", {420, 150}, 40, 2, WHITE);

        DrawRectangleRounded({372, 70, 167, 50}, 0.3, 7, lightBlue);
        DrawTextEx(font, TextFormat("%i", game.score), {(float)(372 + 167 / 2 - MeasureText(TextFormat("%i", game.score), 30) / 2), (float)(70 + 50 / 2 - 28 / 2)}, 30, 2, WHITE);

        DrawRectangleRounded({364, 190, 180, 120}, 0.3, 7, lightBlue);
        
        if (game.gameOver)
        {
            DrawTextEx(font, "GAME OVER", {365, 450}, 42, 3, WHITE);
        }
        
        game.InputHandler();
        if (eventTriggered(0.5))
        {
            game.moveDown();
        }
        game.Draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
