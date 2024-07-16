#ifndef PLAYER_H
#define PLAYER_H

#include "slime.h"
#include "weapon.h"

typedef struct Player
{
    Vector2 position;
    Rectangle frameRec;

    float hMoveVector;
    float vMoveVector;

    int frameCounter;
    int standingFrameCounter;
    int attackFrameCounter;
    int moveRightFrameCounter;
    int moveLeftFrameCounter;

    bool attackState;
    bool moveRightState;
    bool moveLeftState;
    bool jumpState;

    Weapon weapon;
    Vector2 weaponRanegePosition;
} Player;

Player createPlayer();

void setAttackState(Player *player);

void setJumpState(Player *player);

void setMoveLeftState(Player *player);

void setMoveRightState(Player *player);

void updatePlayerPosition(Player *player);

void moveLeft(Player *player);

void attack(Player *player, Slime *slime);

void updatePlayerFrame(Texture2D scarfy, Player *player);

// Draw
//
void drawPlayer(Texture2D scarfy, Player player);

void drawPlayerRec(Player player);

void drawPlayerWeaponRange(Player player);

#endif

