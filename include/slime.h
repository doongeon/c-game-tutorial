#ifndef SLIME_H
#define SLIME_H

#include "raylib.h"
#include "env_item.h"

typedef struct Slime
{
    Vector2 position;
    Rectangle frameRec;
    Color color;

    // Moves
    float hMoveVector;
    float vMoveVector;

    // States
    bool hittedState;
    bool moveRightState;
    bool moveLeftState;
    bool jumpState;

    // Animation Frames
    int frameCounter;
    int updateCounter;
    int hitFrameCounter;
} Slime;

Slime createSlime(Vector2 position);

float slimeLeft(Slime slime);

float slimeRight(Slime slime);

float slimeTop(Slime slime);

float slimeBot(Slime slime);

void handleSlimeEnvCollisionY(Slime *slime, EnvItem *envItems, int envItemsLength);

void handleSlimeEnvCollisionX(Slime *slime, EnvItem *envItems, int envItemsLength);

void slimeFriction(Slime *slime);

void slimeRandomWalk(Slime *slime);

void updateSlimePosition(Slime *slime, EnvItem *envItems, int envItemsLength);

void drawSlime(Slime *slime);


#endif