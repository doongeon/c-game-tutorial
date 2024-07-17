#ifndef SLIME_H
#define SLIME_H

#include "raylib.h"

typedef struct Slime
{
    Vector2 position;
    Rectangle frameRec;
    Color color;

    // Moves
    float hMoveVector;

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

Slime createSlime();

float slimeLeft(Slime slime);

float slimeRight(Slime slime);

float slimeTop(Slime slime);

float sliemBot(Slime slime);

void slimeRandomWalk(Slime *slime);

void updateSlimePosition(Slime *slime);

void drawSlime(Slime *slime);


#endif