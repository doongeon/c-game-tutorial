#include <stdio.h>
#include <raylib.h>

typedef enum GameScreen
{
    LOGO = 0,
    TITLE,
    GAMEPLAY,
    ENDING
} GameScreen;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib ex_02");
    GameScreen currentScreen = LOGO;

    int framesCounter = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        framesCounter = (++framesCounter) % (120 * 4);

        /* Update condition */
        switch (currentScreen)
        {
        case LOGO:
        {
            if (framesCounter > 120)
            {
                currentScreen = TITLE;
            }
        }
        break;
        case TITLE:
        {
            if (framesCounter > 120 * 2)
            {
                currentScreen = GAMEPLAY;
            }
        }
        break;
        case GAMEPLAY:
        {
            if (framesCounter > 120 * 3)
            {
                currentScreen = ENDING;
            }
        }
        break;
        case ENDING:
        {
            if (framesCounter < 120)
            {
                currentScreen = LOGO;
            }
        }
        break;
        default:
        {
            break;
        }
        }

        /* Draw */
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentScreen)
        {
        case LOGO:
            DrawText("LOGO screen", 20, 20, 40, LIGHTGRAY);
            DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);
            break;
        case TITLE:
            DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
            DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
            DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
            break;
        case GAMEPLAY:
            DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
            DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
            DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 120, 220, 20, DARKGREEN);
            break;
        case ENDING:
            DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
            DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
            DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
        default:
            break;
        };

        EndDrawing();
    }

    CloseWindow();

    return 0;
}