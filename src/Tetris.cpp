#include <raylib.h>
#include <iostream>

using namespace std;
int screen_width = 800, screen_height = 600;

int main (){

    InitWindow(screen_width, screen_height, "Pong Game");
    SetTargetFPS(60);

    while(WindowShouldClose() == false){
        BeginDrawing();

        ClearBackground(BLACK);

        EndDrawing();
    }

    return 0;
}
