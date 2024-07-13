#include <stdio.h>
#include <raylib.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib example");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congratuate!, you just start raylib!", screenWidth * 0.2, screenHeight / 2, 22, BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}