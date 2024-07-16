
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXTURE_FILE_PATH "/Users/donggeon/Documents/c-raylib/tutorial/resources/character.png"

#define NUM_WALKING_FRAME 6
#define NUM_STAND_FRAME 4
#define NUM_ATTACK_FRAME 4

#define GROUND_Y_POSITION 280.0f

bool attackState = false;
bool moveRightState = false;
bool moveLeftState = false;
bool jumpState = true;

void setAttackState()
{
    if (!attackState)
    {
        attackState = true;
        moveLeftState = false;
        moveRightState = false;
    }
}

void setJumpState()
{
    if (!jumpState && !attackState)
        jumpState = true;
}

void setMoveLeftState()
{
    moveLeftState = true;
    moveRightState = false;
}

void setMoveRightState()
{
    moveLeftState = false;
    moveRightState = true;
    ;
}

Image GenerateGrassTexture(int width, int height)
{
    Image image = GenImageColor(width, height, DARKGREEN);

    for (int y = 0; y < height; y += 2)
    {
        for (int x = 0; x < width; x += 2)
        {
            Color color = (GetRandomValue(0, 1) == 0) ? GREEN : DARKGREEN;
            ImageDrawPixel(&image, x, y, color);
        }
    }

    return image;
}

Image GenerateUnderGroundTexture(int width, int height)
{
    Image image = GenImageColor(width, height, DARKBROWN);

    for (int y = 0; y < height; y += 2)
    {
        for (int x = 0; x < width; x += 2)
        {
            Color color = (GetRandomValue(0, 1) == 0) ? DARKBROWN : BROWN;
            ImageDrawPixel(&image, x, y, color);
        }
    }

    return image;
}

// Game assets
// ----------------------------------------------------------------------------------
typedef struct Weapon
{
    char *name;
    Rectangle range;
} Weapon;

Weapon createSword()
{
    Weapon result;
    result.name = "sword";
    result.range = (Rectangle) {0, 0, 40, 30};
    return result;
};

typedef struct Slime
{
    Vector2 position;
    Rectangle frameRec;
    Color color;
} Slime;

Slime createSlime()
{
    Slime result;
    result.frameRec = (Rectangle){0, 0, 20, 20};
    result.position = (Vector2){700, GROUND_Y_POSITION - result.frameRec.height};
    result.color = VIOLET;
    return result;
}

typedef struct Player
{
    Vector2 position;
    Rectangle frameRec;
    float hMoveVector;
    float vMoveVector;
    int standingFrameCounter;
    int attackFrameCounter;
    int moveRightFrameCounter;
    int moveLeftFrameCounter;
} Player;

typedef struct EnvItem
{
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;
// ----------------------------------------------------------------------------------


int main(void)
{
    // Initialization
    //------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "animation tutorial");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D scarfy = LoadTexture(TEXTURE_FILE_PATH); // Texture loading

    if (scarfy.id == 0)
    {
        printf("Failed to load texture\n");
        return -1; // Or handle the error as appropriate
    }

    const float groundYPosition = 280.0f;
    Player player;
    player.position = (Vector2){550.0f, groundYPosition - 100};
    player.frameRec = (Rectangle){0.0f, 0.0f, (float)scarfy.width / 6, (float)scarfy.height / 8 * 1};
    player.standingFrameCounter = 0;
    player.attackFrameCounter = 0;
    player.moveRightFrameCounter = 0;
    player.moveLeftFrameCounter = 0;
    player.hMoveVector = 0;
    player.vMoveVector = 0;

    Slime slime = createSlime();

    EnvItem envItems[] = {
        {{0, 0, screenWidth, screenHeight}, 0, SKYBLUE},
        {{0, groundYPosition, 1000, 200}, 1, GRAY},
        {{screenWidth / 2, groundYPosition - 30, 100, 30}, 1, GRAY}};
    int envItemsLength = sizeof(envItems) / sizeof(EnvItem);

    int framesCounter = 0;

    Image grassImage = GenerateGrassTexture(100, 10);
    Texture2D grassTexture = LoadTextureFromImage(grassImage);
    UnloadImage(grassImage);

    Image underGroundImage = GenerateUnderGroundTexture(10, 10);
    Texture2D underGroundTexture = LoadTextureFromImage(underGroundImage);
    UnloadImage(underGroundImage);

    SetTargetFPS(60);
    //------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //--------------------------------------------------------------------------
        framesCounter++;

        bool hitObstacle = false;

        for (int i = 0; i < envItemsLength; i++)
        {
            EnvItem *ei = envItems + i;
            Player *p = &player;
            if (
                ei->blocking &&
                ei->rect.x <= p->position.x + abs((int)(p->frameRec.width)) - 30 &&
                ei->rect.x + ei->rect.width >= p->position.x + 30 &&
                ei->rect.y >= p->position.y + p->frameRec.height - 3 &&
                ei->rect.y <= p->position.y + p->frameRec.height - 3 + player.vMoveVector)
            {
                hitObstacle = true;
                if (hitObstacle)
                    break;
            }
        }
        if (hitObstacle)
        {
            player.vMoveVector = 0;
            jumpState = false;
        }
        else
        {
            player.vMoveVector += 1;
            jumpState = true;
        }

        player.position.x += player.hMoveVector;
        player.position.y += player.vMoveVector;

        if (IsKeyDown(KEY_A))
        {
            setAttackState();
        }
        if (IsKeyDown(KEY_D))
        {
            if (!jumpState && !attackState)
                player.vMoveVector = -10;
            setJumpState();
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            if (!attackState && !jumpState && !moveLeftState)
            {
                setMoveRightState();
                player.hMoveVector += 0.5;
            }
            if (!attackState && jumpState && !moveLeftState)
            {
                setMoveRightState();
                player.hMoveVector += 0.2;
            }
            if (player.hMoveVector > 2)
            {
                player.hMoveVector = 2;
            }
        }
        if (IsKeyUp(KEY_RIGHT))
        {
            moveRightState = false;
        }
        if (IsKeyDown(KEY_LEFT))
        {
            if (!attackState && !jumpState && !moveRightState)
            {
                setMoveLeftState();
                player.hMoveVector -= 0.5;
            }
            if (!attackState && jumpState && !moveRightState)
            {
                setMoveLeftState();
                player.hMoveVector -= 0.2;
            }
            if (player.hMoveVector < -2)
            {
                player.hMoveVector = -2;
            }
        }
        if (IsKeyUp(KEY_LEFT))
        {
            moveLeftState = false;
        }

        if (!moveLeftState && !moveRightState && !jumpState)
        {
            if (player.hMoveVector > 0)
            {
                player.hMoveVector -= 0.5;
                if (player.hMoveVector < 0)
                {
                    player.hMoveVector = 0;
                }
            }

            if (player.hMoveVector < 0)
            {
                player.hMoveVector += 0.5;
                if (player.hMoveVector > 0)
                {
                    player.hMoveVector = 0;
                }
            }
        }

        // Set animating frame
        //
        if (attackState && framesCounter >= (60 / 6))
        {
            // 공격하는 프레임 설정 ( 6 FPS )
            //
            framesCounter = 0;

            player.frameRec.x = (float)player.attackFrameCounter * (float)scarfy.width / 6;
            player.frameRec.y = scarfy.height / 8 * 3;

            player.attackFrameCounter++;

            if (!jumpState)
                player.hMoveVector = 0;

            if (player.attackFrameCounter >= NUM_ATTACK_FRAME)
            {
                player.attackFrameCounter = 0;
                framesCounter = 30;
                attackState = false;
            }
        }
        else if (moveRightState && framesCounter >= (60 / 8))
        {
            // 오른쪽으로 이동하는 프레임 설정 ( 8 FPS )
            //
            framesCounter = 0;

            player.frameRec.x = (float)player.moveRightFrameCounter * (float)scarfy.width / 6;
            player.frameRec.y = scarfy.height / 8 * 0;

            if (player.frameRec.width < 0)
            {
                // 캐릭터가 오른쪽을 보도록 지정
                //
                player.frameRec.width *= -1;
            }

            player.moveRightFrameCounter++;
            if (player.moveRightFrameCounter > 5)
            {
                player.moveRightFrameCounter = 0;
                framesCounter = 30;
            }
        }
        else if (moveLeftState && framesCounter >= (60 / 8))
        {
            // 왼쪽으로 이동하는 프레임임 설정 ( 8 FPS )
            //
            framesCounter = 0;
            player.frameRec.x = (float)player.moveLeftFrameCounter * (float)scarfy.width / 6;
            player.frameRec.y = scarfy.height / 8 * 0;
            if (player.frameRec.width > 0)
            {
                // 캐릭터가 왼쪽을 보도록 지정
                //
                player.frameRec.width *= -1;
            }
            player.moveLeftFrameCounter++;
            if (player.moveLeftFrameCounter > 5)
            {
                player.moveLeftFrameCounter = 0;
                framesCounter = 30;
            }
        }
        else if (framesCounter >= (60 / 2))
        {
            // 서있는 프레임 설정 ( 2FPS )
            //
            framesCounter = 0;

            player.frameRec.x = (float)player.standingFrameCounter * (float)scarfy.width / 6;
            player.frameRec.y = scarfy.height / 8 * 1;

            player.standingFrameCounter++;
            if (player.standingFrameCounter >= NUM_STAND_FRAME)
            {
                player.standingFrameCounter = 0;
            }
        }
        //--------------------------------------------------------------------------

        // Draw
        //--------------------------------------------------------------------------
        BeginDrawing();
        {
            ClearBackground(WHITE);

            // map
            //
            for (int i = 0; i < envItemsLength; i++) // 블럭
                DrawRectangleRec(envItems[i].rect, envItems[i].color);

            for ( // 땅 흙 텍스쳐
                int x = 0;
                x < screenWidth;
                x += underGroundTexture.width)
            {
                for (
                    int y = groundYPosition + grassTexture.height;
                    y < screenHeight;
                    y += underGroundTexture.height)
                {
                    DrawTexture(underGroundTexture, x, y, WHITE);
                }
            }
            for ( // 땅 잔디 텍스쳐
                int x = 0;
                x < screenWidth;
                x += grassTexture.width)
            {
                for (int y = groundYPosition; y < groundYPosition + 10; y += grassTexture.height)
                {
                    DrawTexture(grassTexture, x, y, WHITE);
                }
            }

            for ( // 언덕 흙 텍스쳐
                int x = envItems[2].rect.x;
                x < envItems[2].rect.x + envItems[2].rect.width;
                x += underGroundTexture.width)
            {
                for (
                    int y = envItems[2].rect.y + grassTexture.height;
                    y < envItems[2].rect.y + envItems[2].rect.height;
                    y += underGroundTexture.height)
                {
                    DrawTexture(underGroundTexture, x, y, WHITE);
                }
            }
            for ( // 언덕 잔지 텍스쳐
                int x = envItems[2].rect.x;
                x < envItems[2].rect.x + envItems[2].rect.width;
                x += grassTexture.width)
            {
                for (
                    int y = envItems[2].rect.y;
                    y < envItems[2].rect.y + 10;
                    y += grassTexture.height)
                {
                    DrawTexture(grassTexture, x, y, WHITE);
                }
            }
            //

            // 슬라임
            //
            DrawRectangle(slime.position.x, slime.position.y, slime.frameRec.width, slime.frameRec.height, slime.color);

            // 플레이어
            //
            DrawTextureRec(scarfy, player.frameRec, player.position, WHITE);
            DrawRectangleLines(
                player.position.x,
                player.position.y,
                abs((int)(player.frameRec.width)),
                player.frameRec.height,
                LIME);
            //
        }
        EndDrawing();
        //--------------------------------------------------------------------------
    }

    // De-Initialization
    //------------------------------------------------------------------------------
    UnloadTexture(scarfy);

    CloseWindow();
    //------------------------------------------------------------------------------

    return 0;
}