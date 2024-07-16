#include <stdlib.h>

#include "raylib.h"
#include "constants.h"
#include "weapon.h"
#include "slime.h"

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
    player.weapon = createSword();
    player.frameCounter = 0;
    player.standingFrameCounter = 0;
    player.attackFrameCounter = 0;
    player.moveRightFrameCounter = 0;
    player.moveLeftFrameCounter = 0;
    player.hMoveVector = 0;
    player.vMoveVector = 0;
    player.attackState = false;
    player.moveRightState = false;
    player.moveLeftState = false;
    player.jumpState = true;

    player.weaponRanegePosition = (Vector2){player.position.x + abs((int)player.frameRec.width) / 2, player.position.y + player.frameRec.height - player.weapon.range.height + 10};
    return player;
}

// Utils
// ----------------------------------------------------------------------
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

    player->weaponRanegePosition = (Vector2){player->position.x + abs((int)player->frameRec.width) / 2, player->position.y + player->frameRec.height - player->weapon.range.height + 10};
}

void moveLeft(Player *player)
{
    if (!player->attackState && !player->jumpState && !player->moveRightState)
    {
        setMoveLeftState(player);
        player->hMoveVector -= 0.5;
    }
    if (!player->attackState && player->jumpState && !player->moveRightState)
    {
        setMoveLeftState(player);
        player->hMoveVector -= 0.2;
    }
    if (player->hMoveVector < -2)
    {
        player->hMoveVector = -2;
    }
}

void attack(Player *player, Slime *slime)
{
    if (player->frameRec.width > 0) // 플레이어가 오른쪽을 볼때
    {
        if (
            slime->position.x + slime->frameRec.width >= player->weaponRanegePosition.x &&
            slime->position.x <= player->weaponRanegePosition.x + player->weapon.range.width &&
            slime->position.y >= player->weaponRanegePosition.y &&
            slime->position.y <= player->weaponRanegePosition.y + player->weapon.range.height)
        {
            slime->hittedState = true;
        }
    }
    else // 플레이어가 왼쪽을 볼때
    {
        if (
            slime->position.x <= player->weaponRanegePosition.x &&
            slime->position.x + slime->frameRec.width >= player->weaponRanegePosition.x - player->weapon.range.width &&
            slime->position.y >= player->weaponRanegePosition.y &&
            slime->position.y <= player->weaponRanegePosition.y + player->weapon.range.height)
        {
            slime->hittedState = true;
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

