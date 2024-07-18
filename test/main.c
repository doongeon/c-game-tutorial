
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "constants.h"
#include "circular_queue.h"
#include "slime.h"
#include "weapon.h"
#include "player.h"
#include "damage.h"
#include "linked_damage_list.h"
#include "env_item.h"
#include "texture.h"
#include "map_castle.h"

int main(void)
{
    // Initialization
    //------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "animation tutorial");
    SetRandomSeed((int)time(NULL));

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D scarfy = LoadTexture(TEXTURE_FILE_PATH); // Texture loading
    if (scarfy.id == 0)
    {
        printf("Failed to load texture\n");
        return -1; // Or handle the error as appropriate
    }

    Player player = createPlayer((Vector2){100, GROUND_Y_POSITION - 80});
    Slime slimes[] = {
        createSlime((Vector2){380, GROUND_Y_POSITION - 40}),
        createSlime((Vector2){480, GROUND_Y_POSITION - 40}),
        createSlime((Vector2){580, GROUND_Y_POSITION - 40}),
        createSlime((Vector2){680, GROUND_Y_POSITION - 40}),
        createSlime((Vector2){780, GROUND_Y_POSITION - 40})};
    int slimesLength = sizeof(slimes) / sizeof(Slime);
    DamageNode *damageList = initializeList();
    Map mapCastle = getMapCastle();

    Texture2D grassTexture = getGrassTexture();
    Texture2D dirtTexture = getDirtTexture();
    Texture2D redBlockTexture = getRedBlockTexture();
    Texture2D waterTexutre = getWaterTexture();

    SetTargetFPS(60);
    //------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //--------------------------------------------------------------------------
        removeExpiredNode(&damageList);

        for (int i = 0; i < slimesLength; i++)
        {
            Slime *slimePtr = slimes + i;
            updateSlimePosition(slimes + i, mapCastle.envItems, mapCastle.envItemsLength);
        }

        if (IsKeyDown(KEY_A))
        {
            setAttackState(&player);
            attack(&player, slimes, slimesLength, &damageList);
        }
        if (IsKeyDown(KEY_D))
        {
            if (!player.jumpState && !player.attackState)
                player.vMoveVector = -10;
            setJumpState(&player);
        }
        if (IsKeyDown(KEY_RIGHT))
            movePlayerRight(&player);
        if (IsKeyUp(KEY_RIGHT))
            player.moveRightState = false;
        if (IsKeyDown(KEY_LEFT))
            movePlayerLeft(&player);
        if (IsKeyUp(KEY_LEFT))
            player.moveLeftState = false;

        handleEnvitemCollisionY(&player, mapCastle.envItems, mapCastle.envItemsLength);
        handleEnvitemCollisionX(&player, mapCastle.envItems, mapCastle.envItemsLength);

        if (
            playerLeft(player) + player.hMoveVector <= 0 ||
            playerRight(player) + player.hMoveVector >= SCREEN_WIDTH)
        {
            player.hMoveVector = 0;
        }
        if (!player.moveLeftState && !player.moveRightState && !player.jumpState)
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
        
        updatePlayerPosition(&player);

        updatePlayerFrame(scarfy, &player); // Player
        //--------------------------------------------------------------------------


        // Draw
        //--------------------------------------------------------------------------
        BeginDrawing();
        {
            ClearBackground(SKYBLUE);

            // map
            //
            drawMapCastle(
                mapCastle,
                grassTexture,
                dirtTexture,
                redBlockTexture,
                waterTexutre);
            //


            // 슬라임
            //
            for (int i = 0; i < slimesLength; i++)
            {
                Slime *slimePtr = slimes + i;
                drawSlime(slimePtr); 
            }
            //


            // 데미지
            //
            if (!isDamageListEmpty(&damageList)) 
            {
                drawDamages(&damageList);
            }
            //


            // 플레이어
            //
            drawPlayer(scarfy, player); 
            // drawPlayerRec(player);
            // drawPlayerWeaponRange(player);
            //
        }
        EndDrawing();
        //--------------------------------------------------------------------------
    }

    // De-Initialization
    //------------------------------------------------------------------------------
    UnloadTexture(scarfy);
    freeMap(mapCastle);

    CloseWindow();
    //------------------------------------------------------------------------------

    return 0;
}