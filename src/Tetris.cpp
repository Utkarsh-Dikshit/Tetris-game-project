#include <iostream>
#include <raylib.h>
#include "game.h"

Color darkBlue = {44, 44, 137, 255};
int screen_width = 330, screen_height = 600;

int main()
{
    InitWindow(screen_width, screen_height, "Tetris");
    SetTargetFPS(60);

    Game game = Game();

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(darkBlue);
        game.Draw();
        game.InputHandler();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
