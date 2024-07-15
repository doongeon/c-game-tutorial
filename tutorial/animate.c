
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

void setAttackState()
{
    if(!attackState) attackState = true;
}

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

    Vector2 playerPosition = {550.0f, 280.0f}; // player start position
    Rectangle frameRec = {0.0f, 0.0f, (float)scarfy.width / 6, (float)scarfy.height / 8 * 1}; 


    int framesCounter = 0;
    int standingFrameCounter = 0;
    int attackFrameCounter = 0;
    int moveRightFrameCounter = 0;
    int moveLeftFrameCounter = 0;
    double playerHMoveVector = 0;
    double playerVMoveVector = 0;

    SetTargetFPS(60);
    //------------------------------------------------------------------------------


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //--------------------------------------------------------------------------
        framesCounter++;

        playerPosition.x += playerHMoveVector;

        if(IsKeyDown(KEY_A)) 
        {
            setAttackState();
            playerHMoveVector = 0;
        }

        if(IsKeyDown(KEY_RIGHT))
        {   
            if(!attackState) 
            {
                moveRightState = true;
                playerHMoveVector += 0.5;
                if(playerHMoveVector > 2)
                {
                    playerHMoveVector = 2;
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
                playerHMoveVector -= 0.5;
                if(playerHMoveVector < -2)
                {
                    playerHMoveVector = -2;
                }
            }
        }
        if(IsKeyUp(KEY_LEFT))
        {
            moveLeftState = false;
        }

        if(!moveLeftState && !moveRightState && !attackState)
        {
            if(playerHMoveVector > 0)
            {
                playerHMoveVector -= 0.5;
                if(playerHMoveVector < 0)
                {
                    playerHMoveVector = 0;
                }
            }

            if(playerHMoveVector < 0)
            {
                playerHMoveVector += 0.5;
                if(playerHMoveVector > 0)
                {
                    playerHMoveVector = 0;
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

            frameRec.x = (float)attackFrameCounter * (float)scarfy.width / 6;
            frameRec.y = scarfy.height / 8 * 3;

            attackFrameCounter++;
            if(attackFrameCounter > NUM_ATTACK_FRAME - 1)
            {
                attackFrameCounter = 0;
                framesCounter = 22;
                attackState = false;
            }
        } else if(moveRightState && framesCounter >= (60 / 8)) 
        {
            // 오른쪽으로 이동하는 프레임 설정 ( 8 FPS )
            //
            framesCounter = 0;

            frameRec.x = (float)moveRightFrameCounter * (float)scarfy.width / 6;
            frameRec.y = scarfy.height / 8 * 0;

            if(frameRec.width < 0)
            {
                // 캐릭터가 오른쪽을 보도록 지정
                //
                frameRec.width *= -1;
            }

            moveRightFrameCounter++;
            if(moveRightFrameCounter > 5)
            {
                moveRightFrameCounter = 0;
                framesCounter = 30;
            }
        }
        else if(moveLeftState && framesCounter >= (60 / 8)) 
        {
            // 왼쪽으로 이동하는 프레임임 설정 ( 8 FPS )
            //
            framesCounter = 0;

            frameRec.x = (float)moveLeftFrameCounter * (float)scarfy.width / 6;
            frameRec.y = scarfy.height / 8 * 0;

            if(frameRec.width > 0)
            {
                // 캐릭터가 왼쪽을 보도록 지정
                //
                frameRec.width *= -1;
            }

            moveLeftFrameCounter++;
            if(moveLeftFrameCounter > 5)
            {
                moveLeftFrameCounter = 0;
                framesCounter = 30;
            }
        }
        else if (framesCounter >= (60 / 2)) 
        {
            // 서있는 프레임 설정 ( 2FPS )
            //
            framesCounter = 0;
            
            frameRec.x = (float)standingFrameCounter * (float)scarfy.width / 6;
            frameRec.y = scarfy.height / 8 * 1;

            standingFrameCounter++;
            if (standingFrameCounter >= NUM_STAND_FRAME)
            {
                standingFrameCounter = 0;
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
                15 + (int)frameRec.x,
                40 + (int)frameRec.y,
                abs((int)frameRec.width),
                abs((int)frameRec.height),
                RED
            );

            DrawTextureRec(scarfy, frameRec, playerPosition, WHITE);
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
