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

float slimeLeft(Slime slime);

float slimeRight(Slime slime);

float slimeTop(Slime slime);

float sliemBot(Slime slime);

#endif