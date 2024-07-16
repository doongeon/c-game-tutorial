#ifndef SLIME_H
#define SLIME_H

#include "raylib.h"

typedef struct Slime
{
    Vector2 position;
    Rectangle frameRec;
    Color color;
    bool hittedState;
    int frameCounter;
    int hitFrameCounter;
} Slime;

Slime createSlime();

float calculateSlimeLeft(Slime slime);

float calculateSlimeRight(Slime slime);

float calculateSlimeTop(Slime slime);

float calculateSlimeBot(Slime slime);

#endif