#include <iostream>
#include <raylib.h>
#include "grid.h"

Color darkBlue = {44, 44, 137, 255};
int screen_width = 540, screen_height = 660;

int main()
{

    InitWindow(300, 600, "Tetris");
    SetTargetFPS(60);

    Grid grid = Grid();
    grid.grid[0][0] = 1;
    grid.grid[3][5] = 2;
    grid.grid[17][8] = 3;

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(darkBlue);

        grid.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
