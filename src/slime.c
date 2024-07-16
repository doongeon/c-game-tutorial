#include "raylib.h"
#include "constants.h"

typedef struct Slime
{
    Vector2 position;
    Rectangle frameRec;
    Color color;
    bool hittedState;
    int frameCounter;
    int hitFrameCounter;
} Slime;

Slime createSlime()
{
    Slime slime;
    slime.frameRec = (Rectangle){0, 0, 20, 20};
    slime.position = (Vector2){700, GROUND_Y_POSITION - slime.frameRec.height};
    slime.color = VIOLET;
    slime.hittedState = false;
    slime.frameCounter = 0;
    slime.hitFrameCounter = 0;
    return slime;
}

// Utils
// ----------------------------------------------------------------------
float slimeLeft(Slime slime)
{
    return slime.position.x;
}

float slimeRight(Slime slime)
{
    return slime.position.x + slime.frameRec.width;
}

float slimeTop(Slime slime)
{
    return slime.position.y;
}

float sliemBot(Slime slime)
{
    return slime.position.y + slime.frameRec.height;
}
// ----------------------------------------------------------------------
