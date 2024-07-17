#include <stdlib.h>

#include "raylib.h"
#include "constants.h"
#include "weapon.h"
#include "slime.h"
#include "damage.h"
#include "linked_damage_list.h"

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

Player createPlayer()
{
    Player player;

    player.frameRec = (Rectangle){0.0f, 0.0f, (float)SCARFY_WIDTH / 6, (float)SCARFY_HEIGHT / 8 * 1};
    player.position = (Vector2){550.0f, GROUND_Y_POSITION - player.frameRec.height};

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
    player.weaponRanegePosition = (Vector2){player.position.x + abs((int)player.frameRec.width) / 2, player.position.y + player.frameRec.height - player.weapon.range.height + 10};

    return player;
}

// Utils
// ----------------------------------------------------------------------
bool isWatchRight(Player player)
{
    bool result = player.frameRec.width > 0 ? true : false;
    return result;
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
    return player.weaponRanegePosition.y + player.weaponRanegePosition.y;
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
        player->position.x + abs((int)player->frameRec.width) / 2,
        player->position.y + player->frameRec.height - player->weapon.range.height + 10};
}

void moveLeft(Player *player)
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

void attack(Player *player, Slime *slime, DamageNode **damageList)
{
    if (
        slimeLeft(*slime) <= weaponRangeRight(*player) &&
        slimeRight(*slime) >= weaponRangeLeft(*player) &&
        slimeTop(*slime) >= weaponRangeTop(*player) &&
        slimeTop(*slime) <= weaponRangeBot(*player))
    {
        slime->hittedState = true;
        append(damageList, createDamage(*slime));
    }
}

void updatePlayerFrame(Texture2D scarfy, Player *player)
{
    player->frameCounter++;
    if (player->attackState && player->frameCounter >= (60 / 6))
    {
        // 공격하는 프레임 설정 ( 6 FPS )
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
        abs((int)(player.frameRec.width)),
        player.frameRec.height,
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
