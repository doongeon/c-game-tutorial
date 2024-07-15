
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>




#define FRAME_SPEED  8
#define NUM_WALKING_FRAME 6
#define NUM_STAND_FRAME 4
#define NUM_ATTACK_FRAME 4

bool attackState = false;
bool moveRightState = false;
bool moveLeftState = false;
bool jumpState = false;

void setAttackState()
{
    if(!attackState) attackState = true;
}

void setJumpState()
{
    if(!jumpState) jumpState = true;
}

typedef struct Player {
    Vector2 position; // player start position
    Rectangle frameRec;
    float hMoveVector;
    float vMoveVector;
    int standingFrameCounter;
    int attackFrameCounter;
    int moveRightFrameCounter;
    int moveLeftFrameCounter;
} Player;

int main(void)
{
    // Initialization
    //------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "animation tutorial");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D scarfy = LoadTexture("/Users/donggeon/Documents/c-raylib/tutorial/resources/character.png"); // Texture loading

    if (scarfy.id == 0) 
    {
        printf("Failed to load texture\n");
        return -1;  // Or handle the error as appropriate
    }

    const float initialPlayerYPosition = 280.0f;

    Player player;
    player.position = (Vector2){550.0f, initialPlayerYPosition};
    player.frameRec = (Rectangle){0.0f, 0.0f, (float)scarfy.width / 6, (float)scarfy.height / 8 * 1};
    player.standingFrameCounter = 0;
    player.attackFrameCounter = 0;
    player.moveRightFrameCounter = 0;
    player.moveLeftFrameCounter = 0;
    player.hMoveVector = 0;
    player.vMoveVector = 0;



    int framesCounter = 0;
    // float playerVMoveVector = 0;

    SetTargetFPS(60);
    //------------------------------------------------------------------------------


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //--------------------------------------------------------------------------
        framesCounter++;

        player.position.x += player.hMoveVector;

        if(player.position.y + player.vMoveVector < initialPlayerYPosition)
        {
            player.position.y += player.vMoveVector;
            player.vMoveVector += 1; // 플레이어에게 중력 작용
        }
        else
        {
            player.position.y = initialPlayerYPosition;
            player.vMoveVector = 0;
            jumpState = false;
        }
        

        

        if(IsKeyDown(KEY_A)) 
        {
            setAttackState();
        }
        if(IsKeyDown(KEY_D))
        {
            if(!jumpState) player.vMoveVector = -10;
            setJumpState();
        }
        if(IsKeyDown(KEY_RIGHT))
        {   
            if(!attackState) 
            {
                moveRightState = true;
                player.hMoveVector += 0.5;
                if(player.hMoveVector > 2)
                {
                    player.hMoveVector = 2;
                }
            }
        }
        if(IsKeyUp(KEY_RIGHT))
        {
            moveRightState = false;
        }
        if(IsKeyDown(KEY_LEFT))
        {   
            if(!attackState) 
            {
                moveLeftState = true;
                player.hMoveVector -= 0.5;
                if(player.hMoveVector < -2)
                {
                    player.hMoveVector = -2;
                }
            }
        }
        if(IsKeyUp(KEY_LEFT))
        {
            moveLeftState = false;
        }

        if(!moveLeftState && !moveRightState && !jumpState)
        {
            if(player.hMoveVector > 0)
            {
                player.hMoveVector -= 0.5;
                if(player.hMoveVector < 0)
                {
                    player.hMoveVector = 0;
                }
            }

            if(player.hMoveVector < 0)
            {
                player.hMoveVector += 0.5;
                if(player.hMoveVector > 0)
                {
                    player.hMoveVector = 0;
                }
            }
        }



        // Set animating frame
        //
        if(attackState && framesCounter >= (60 / 8)) 
        {
            // 공격하는 프레임 설정 ( 8 FPS )
            //           
            framesCounter = 0;

            player.frameRec.x = (float)player.attackFrameCounter * (float)scarfy.width / 6;
            player.frameRec.y = scarfy.height / 8 * 3;

            player.attackFrameCounter++;
            if(player.attackFrameCounter > NUM_ATTACK_FRAME - 1)
            {
                player.attackFrameCounter = 0;
                framesCounter = 22;
                attackState = false;
            }
        } else if(moveRightState && framesCounter >= (60 / 8)) 
        {
            // 오른쪽으로 이동하는 프레임 설정 ( 8 FPS )
            //
            framesCounter = 0;

            player.frameRec.x = (float)player.moveRightFrameCounter * (float)scarfy.width / 6;
            player.frameRec.y = scarfy.height / 8 * 0;

            if(player.frameRec.width < 0)
            {
                // 캐릭터가 오른쪽을 보도록 지정
                //
                player.frameRec.width *= -1;
            }

            player.moveRightFrameCounter++;
            if(player.moveRightFrameCounter > 5)
            {
                player.moveRightFrameCounter = 0;
                framesCounter = 30;
            }
        }
        else if(moveLeftState && framesCounter >= (60 / 8)) 
        {
            // 왼쪽으로 이동하는 프레임임 설정 ( 8 FPS )
            //
            framesCounter = 0;
            player.frameRec.x = (float)player.moveLeftFrameCounter * (float)scarfy.width / 6;
            player.frameRec.y = scarfy.height / 8 * 0;
            if(player.frameRec.width > 0)
            {
                // 캐릭터가 왼쪽을 보도록 지정
                //
                player.frameRec.width *= -1;
            }
            player.moveLeftFrameCounter++;
            if(player.moveLeftFrameCounter > 5)
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
            ClearBackground(RAYWHITE);
            
            DrawTexture(scarfy, 15, 40, WHITE);
            DrawRectangleLines(15, 40, scarfy.width, scarfy.height, LIME);
            DrawRectangleLines(
                15 + (int)player.frameRec.x,
                40 + (int)player.frameRec.y,
                abs((int)player.frameRec.width),
                abs((int)player.frameRec.height),
                RED
            );

            DrawTextureRec(scarfy, player.frameRec, player.position, WHITE);
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
