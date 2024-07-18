#include <stdlib.h>

#include "raylib.h"
#include "constants.h"
#include "weapon.h"
#include "slime.h"
#include "damage.h"
#include "linked_damage_list.h"
#include "env_item.h"

#define PLAYER_WIDTH 13
#define PLAYER_HEIGHT 30


typedef struct Player
{
    Vector2 position;
    Rectangle frameRec;

    // Moves
    float hMoveVector;
    float vMoveVector;

    // Animation Frames
    int frameCounter;
    int standingFrameCounter;
    int attackFrameCounter;
    int moveRightFrameCounter;
    int moveLeftFrameCounter;

    // States
    bool attackState;
    bool moveRightState;
    bool moveLeftState;
    bool jumpState;

    // Weapon
    Weapon weapon;
    Vector2 weaponRanegePosition;
} Player;

Player createPlayer(Vector2 position)
{
    Player player;

    player.frameRec = (Rectangle){0.0f, 0.0f, (float)SCARFY_WIDTH / 6, (float)SCARFY_HEIGHT / 8 * 1};
    player.position = (Vector2){position.x, position.y};

    player.hMoveVector = 0;
    player.vMoveVector = 0;

    player.frameCounter = 0;
    player.standingFrameCounter = 0;
    player.attackFrameCounter = 0;
    player.moveRightFrameCounter = 0;
    player.moveLeftFrameCounter = 0;

    player.attackState = false;
    player.moveRightState = false;
    player.moveLeftState = false;
    player.jumpState = true;

    player.weapon = createSword();
    player.weaponRanegePosition = (Vector2){player.position.x + abs((int)player.frameRec.width) / 2, player.position.y + player.frameRec.height};

    return player;
}





// Utils
// ----------------------------------------------------------------------
bool isWatchRight(Player player)
{
    bool result = player.frameRec.width > 0 ? true : false;
    return result;
}

float playerRight(Player player)
{
    return player.position.x + abs((int)(player.frameRec.width)) - 30;
}

float playerLeft(Player player)
{
    return player.position.x + 30;
}

float playerTop(Player player)
{
    return player.position.y + 16;
}

float playerBot(Player player)
{
    return player.position.y + player.frameRec.height - 3;
}

float weaponRangeLeft(Player player)
{
    if (isWatchRight(player))
    {
        return player.weaponRanegePosition.x;
    }
    else
    {
        return player.weaponRanegePosition.x - player.weapon.range.width;
    }
}

float weaponRangeRight(Player player)
{
    if (isWatchRight(player))
    {
        return player.weaponRanegePosition.x + player.weapon.range.width;
    }
    else
    {
        return player.weaponRanegePosition.x;
    }
}

float weaponRangeTop(Player player)
{
    return player.weaponRanegePosition.y;
}

float weaponRangeBot(Player player)
{
    return player.weaponRanegePosition.y + player.weapon.range.height;
}
// ----------------------------------------------------------------------





// Update
// ----------------------------------------------------------------------
void setAttackState(Player *player)
{
    if (!player->attackState)
    {
        player->attackState = true;
        player->moveLeftState = false;
        player->moveRightState = false;
    }
}

void setJumpState(Player *player)
{
    if (!player->jumpState && !player->attackState)
        player->jumpState = true;
}

void setMoveLeftState(Player *player)
{
    player->moveLeftState = true;
    player->moveRightState = false;
}

void setMoveRightState(Player *player)
{
    player->moveLeftState = false;
    player->moveRightState = true;
    ;
}

void updatePlayerPosition(Player *player)
{
    player->position.x += player->hMoveVector;
    player->position.y += player->vMoveVector;

    player->weaponRanegePosition = (Vector2){
        player->position.x + abs((int)player->frameRec.width) / 2, playerTop(*player)};
}

void handleEnvitemCollisionY(Player *player, EnvItem *envItems, int envItemsLength)
{
    bool hitObstacle = false;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        if (
            ei->blockY &&
            envItemLeft(*ei) <= playerRight(*player) &&
            envItemRight(*ei) >= playerLeft(*player) &&
            envItemTop(*ei) >= playerBot(*player) &&
            envItemTop(*ei) <= playerBot(*player) + player->vMoveVector)
        {
            hitObstacle = true;
            if (hitObstacle)
                break;
        }
    }
    if (hitObstacle)
    {
        player->vMoveVector = 0;
        player->jumpState = false;
    }
    else
    {
        player->vMoveVector += 1; // 중력처럼 작용
        player->jumpState = true;
    }
}

void handleEnvitemCollisionX(Player *player, EnvItem *envItems, int envItemsLength)
{
    bool hitObstacle = false;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        if (
            ei->blockX &&
            envItemLeft(*ei) <= playerRight(*player) + player->hMoveVector &&
            envItemRight(*ei) >= playerLeft(*player) + player->hMoveVector &&
            envItemTop(*ei) < playerBot(*player) &&
            envItemBot(*ei) > playerTop(*player))
        {
            hitObstacle = true;
            if (hitObstacle)
            {
                player->hMoveVector = 0;
                break;
            }
        }
    }
}

void movePlayerLeft(Player *player)
{
    if (
        !player->attackState &&
        !player->jumpState &&
        !player->moveRightState)
    {
        setMoveLeftState(player);
        player->hMoveVector -= 0.5;
    }
    if (
        !player->attackState &&
        player->jumpState &&
        !player->moveRightState)
    {
        setMoveLeftState(player);
        player->hMoveVector -= 0.2;
    }
    if (player->hMoveVector < -2)
    {
        player->hMoveVector = -2;
    }
}

void movePlayerRight(Player *player)
{
    if (!player->attackState && !player->jumpState && !player->moveLeftState)
    {
        setMoveRightState(player);
        player->hMoveVector += 0.5;
    }
    if (!player->attackState && player->jumpState && !player->moveLeftState)
    {
        setMoveRightState(player);
        player->hMoveVector += 0.2;
    }
    if (player->hMoveVector > 2)
    {
        player->hMoveVector = 2;
    }
}

void attack(Player *player, Slime *slimes, int slimesLength, DamageNode **damageList)
{
    for(int i = 0; i < slimesLength; i++)
    {   
        Slime *slimePtr = slimes + i;
        if (
            slimeLeft(*slimePtr) <= weaponRangeRight(*player) &&
            slimeRight(*slimePtr) >= weaponRangeLeft(*player) &&
            slimeTop(*slimePtr) <= weaponRangeBot(*player) &&
            slimeBot(*slimePtr) >= weaponRangeTop(*player) &&
            player->attackFrameCounter == 1 &&
            player->frameCounter == 0)
        {
            slimePtr->hittedState = true;
            append(damageList, createDamage(*slimePtr));
        }
    }
}

void updatePlayerFrame(Texture2D scarfy, Player *player)
{
    player->frameCounter++;
    if (player->attackState && player->frameCounter >= (60 / 20))
    {
        // 공격하는 프레임 설정 ( 20 FPS )
        //
        player->frameCounter = 0;

        player->frameRec.x = (float)player->attackFrameCounter * (float)scarfy.width / 6;
        player->frameRec.y = scarfy.height / 8 * 3;

        player->attackFrameCounter++;

        if (!player->jumpState)
            player->hMoveVector = 0;

        if (player->attackFrameCounter >= NUM_ATTACK_FRAME)
        {
            player->attackFrameCounter = 0;
            player->frameCounter = 30;
            player->attackState = false;
        }
    }
    else if (player->moveRightState && player->frameCounter >= (60 / 8))
    {
        // 오른쪽으로 이동하는 프레임 설정 ( 8 FPS )
        //
        player->frameCounter = 0;

        player->frameRec.x = (float)player->moveRightFrameCounter * (float)scarfy.width / 6;
        player->frameRec.y = scarfy.height / 8 * 0;

        if (player->frameRec.width < 0)
        {
            // 캐릭터가 오른쪽을 보도록 지정
            //
            player->frameRec.width *= -1;
        }

        player->moveRightFrameCounter++;
        if (player->moveRightFrameCounter > 5)
        {
            player->moveRightFrameCounter = 0;
            player->frameCounter = 30;
        }
    }
    else if (player->moveLeftState && player->frameCounter >= (60 / 8))
    {
        // 왼쪽으로 이동하는 프레임임 설정 ( 8 FPS )
        //
        player->frameCounter = 0;
        player->frameRec.x = (float)player->moveLeftFrameCounter * (float)scarfy.width / 6;
        player->frameRec.y = scarfy.height / 8 * 0;
        if (player->frameRec.width > 0)
        {
            // 캐릭터가 왼쪽을 보도록 지정
            //
            player->frameRec.width *= -1;
        }
        player->moveLeftFrameCounter++;
        if (player->moveLeftFrameCounter > 5)
        {
            player->moveLeftFrameCounter = 0;
            player->frameCounter = 30;
        }
    }
    else if (player->frameCounter >= (60 / 2))
    {
        // 서있는 프레임 설정 ( 2FPS )
        //
        player->frameCounter = 0;

        player->frameRec.x = (float)player->standingFrameCounter * (float)scarfy.width / 6;
        player->frameRec.y = scarfy.height / 8 * 1;

        player->standingFrameCounter++;
        if (player->standingFrameCounter >= NUM_STAND_FRAME)
        {
            player->standingFrameCounter = 0;
        }
    }
}
// ----------------------------------------------------------------------





// Control
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------





// Draw
// ----------------------------------------------------------------------
void drawPlayer(Texture2D scarfy, Player player)
{
    DrawTextureRec(scarfy, player.frameRec, player.position, WHITE);
}

void drawPlayerRec(Player player)
{
    DrawRectangleLines(
        player.position.x,
        player.position.y,
        PLAYER_WIDTH,
        PLAYER_HEIGHT,
        LIME);
}

void drawPlayerWeaponRange(Player player)
{
    DrawRectangleLines(
        player.weaponRanegePosition.x,
        player.weaponRanegePosition.y,
        player.frameRec.width > 0 ? player.weapon.range.width : -player.weapon.range.width,
        player.weapon.range.height,
        RED);
}
// ----------------------------------------------------------------------
