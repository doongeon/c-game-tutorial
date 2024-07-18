
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
    EnvItem envItems[] = {
        createEnvItem(
            "background",
            (Vector2){0, 0},
            SCREEN_WIDTH / ENVITEM_WIDTH_UNIT + 1,
            SCREEN_HEIGHT / ENVITEM_HEIGHT_UNIT + 1,
            0, 0),
        createEnvItem(
            "ground",
            (Vector2){0, GROUND_Y_POSITION},
            SCREEN_WIDTH / ENVITEM_WIDTH_UNIT + 1,
            (SCREEN_HEIGHT - GROUND_Y_POSITION) / ENVITEM_HEIGHT_UNIT + 1,
            0, 1),
        createEnvItem(
            "hill",
            (Vector2){500, GROUND_Y_POSITION - ENVITEM_HEIGHT_UNIT},
            3,
            1,
            0, 1),
        createEnvItem(
            "fence",
            (Vector2){300, GROUND_Y_POSITION - ENVITEM_HEIGHT_UNIT},
            1,
            2,
            1, 1),
        createEnvItem(
            "wall top 01",
            (Vector2){ENVITEM_HEIGHT_UNIT * 1 - 30, GROUND_Y_POSITION - ENVITEM_HEIGHT_UNIT * 2 - 20},
            1,
            1,
            0, 0),
        createEnvItem(
            "wall top 01",
            (Vector2){ENVITEM_HEIGHT_UNIT * 2 - 20, GROUND_Y_POSITION - ENVITEM_HEIGHT_UNIT * 2 - 20},
            1,
            1,
            0, 0),
        createEnvItem(
            "wall top 02",
            (Vector2){ENVITEM_HEIGHT_UNIT * 3 - 10, GROUND_Y_POSITION - ENVITEM_HEIGHT_UNIT * 2 - 20},
            1,
            1,
            0, 0),
        createEnvItem(
            "wall top 03",
            (Vector2){ENVITEM_HEIGHT_UNIT * 4, GROUND_Y_POSITION - ENVITEM_HEIGHT_UNIT * 2 - 20},
            1,
            1,
            0, 0),
        createEnvItem(
            "wall",
            (Vector2){0, GROUND_Y_POSITION - ENVITEM_HEIGHT_UNIT * 2},
            5,
            2,
            0, 0),
        createEnvItem(
            "pond",
            (Vector2){200, GROUND_Y_POSITION},
            2,
            0,
            0, 0)
    };
    int envItemsLength = sizeof(envItems) / sizeof(EnvItem);

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
            updateSlimePosition(slimes + i, envItems, envItemsLength);
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

        handleEnvitemCollisionY(&player, envItems, envItemsLength);
        handleEnvitemCollisionX(&player, envItems, envItemsLength);
        updatePlayerPosition(&player);

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

        updatePlayerFrame(scarfy, &player); // Player
        //--------------------------------------------------------------------------

        if (
            playerLeft(player) + player.hMoveVector <= 0 ||
            playerRight(player) + player.hMoveVector >= SCREEN_WIDTH)
        {
            player.hMoveVector = 0;
        }

        // Draw
        //--------------------------------------------------------------------------
        BeginDrawing();
        {
            ClearBackground(SKYBLUE);

            // map
            //
            drawGrassFieldTexture(envItems[1], grassTexture, dirtTexture);
            drawGrassFieldTexture(envItems[2], grassTexture, dirtTexture);
            drawGrassFieldTexture(envItems[3], grassTexture, dirtTexture);
            drawRedBlockTexture(envItems[4], redBlockTexture);
            drawRedBlockTexture(envItems[5], redBlockTexture);
            drawRedBlockTexture(envItems[6], redBlockTexture);
            drawRedBlockTexture(envItems[7], redBlockTexture);
            drawRedBlockTexture(envItems[8], redBlockTexture);
            drawWaterTexture(envItems[9], waterTexutre);
            //

            for (int i = 0; i < slimesLength; i++)
            {
                Slime *slimePtr = slimes + i;

                drawSlime(slimePtr); // 슬라임
            }

            if (!isDamageListEmpty(&damageList)) // 데미지
            {
                drawDamages(&damageList);
            }

            drawPlayer(scarfy, player); // 플레이어
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

    CloseWindow();
    //------------------------------------------------------------------------------

    return 0;
}