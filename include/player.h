#ifndef PLAYER_H
#define PLAYER_H

#include "slime.h"
#include "weapon.h"
#include "damage.h"
#include "env_item.h"
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

Player createPlayer();

bool isWatchRight(Player player);

float playerRight(Player player);

float playerLeft(Player player);

float playerTop(Player player);

float playerBot(Player player);

void setAttackState(Player *player);

void setJumpState(Player *player);

void setMoveLeftState(Player *player);

void setMoveRightState(Player *player);

void updatePlayerPosition(Player *player);

void handleEnvitemCollisionY(Player *player, EnvItem *envItems, int envItemsLength);

void handleEnvitemCollisionX(Player *player, EnvItem *envItems, int envItemsLength);

void movePlayerLeft(Player *player);

void movePlayerRight(Player *player);

void attack(Player *player, Slime *slimes, int slimesLength, DamageNode **damageList);

void updatePlayerFrame(Texture2D scarfy, Player *player);

// Draw
//
void drawPlayer(Texture2D scarfy, Player player);

void drawPlayerRec(Player player);

void drawPlayerWeaponRange(Player player);

#endif

