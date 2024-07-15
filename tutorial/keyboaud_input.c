#include <stdio.h>
#include "raylib.h"

#define MAX_BUILDINGS 100
#define MAP_POSITION_X -6000.0f
#define GROUND_POSITION_Y  300.0f

int main(void)
{
    SetRandomSeed((int)GetTime());
    const int screenWidth = 1024;
    const int screenHeight = screenWidth * 9 / 16;

    Rectangle player = {screenWidth / 2 - 20, GROUND_POSITION_Y - 40, 40, 40};
    Rectangle buildings[MAX_BUILDINGS] = {0};
    Color buildingColors[MAX_BUILDINGS] = {0};

    int spacing = 0;

    for (int i = 0; i < MAX_BUILDINGS; i++)
    {
        buildings[i].width = (float)GetRandomValue(50, 200);
        buildings[i].height = (float)GetRandomValue(100, 800);
        buildings[i].y = GROUND_POSITION_Y - buildings[i].height;
        buildings[i].x = MAP_POSITION_X + spacing;

        spacing += (int)buildings[i].width;

        buildingColors[i] = (Color){GetRandomValue(100, 200), GetRandomValue(100, 200), GetRandomValue(100, 200), 255};
    }

    printf("\n %d %d \n", buildingColors[1].r, buildingColors[2].r);

    Camera2D camera = {0};
    camera.target = (Vector2){player.x + 20.f, player.y + 20.0f};
    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    InitWindow(screenWidth, screenHeight, "raylib ex_03");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // update
        // --------------------------------------------------------------
        // player movement
        if (IsKeyDown(KEY_LEFT)) player.x -= 20;
        if (IsKeyDown(KEY_RIGHT)) player.x += 20;

        // camera target follows player
        camera.target = (Vector2){player.x + player.width / 2, player.y + player.height / 2};

        // camera zoom controls
        camera.zoom += ((float)GetMouseWheelMove() * 0.05f);
        if (camera.zoom > 10.0f) camera.zoom = 10.0f;
        if (camera.zoom < 0.1f) camera.zoom = 0.1f;
        // --------------------------------------------------------------


        // draw
        // --------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        BeginMode2D(camera);
        DrawRectangleGradientV(MAP_POSITION_X, -1000, 20000, 1000 + GROUND_POSITION_Y, BLACK, ORANGE);
        DrawRectangle(MAP_POSITION_X, GROUND_POSITION_Y, 13000, 8000, DARKGRAY);

        for (int i = 0; i < MAX_BUILDINGS; i++)
        {
            DrawRectangleRec(buildings[i], buildingColors[i]);
        }

        DrawRectangleRec(player, RED);

        DrawLine((int)camera.target.x, -screenHeight * 10, (int)camera.target.x, screenHeight * 10, GREEN);
        DrawLine(-screenWidth * 10, (int)camera.target.y, screenWidth * 10, (int)camera.target.y, GREEN);
        EndMode2D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}