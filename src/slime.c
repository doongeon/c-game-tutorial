#include "raylib.h"
#include "constants.h"
#include <stdio.h>

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

Slime createSlime()
{
    Slime slime;
    slime.frameRec = (Rectangle){0, 0, 20, 20};
    slime.position = (Vector2){700, GROUND_Y_POSITION - slime.frameRec.height};
    slime.color = VIOLET;

    // States
    slime.hMoveVector = 0;

    // States
    slime.hittedState = false;
    slime.moveLeftState = false;
    slime.moveRightState = false;
    slime.jumpState = false;

    // Animation Frames
    slime.frameCounter = 0;
    slime.updateCounter = 0;
    slime.hitFrameCounter = 0;
    return slime;
}

// Utils
// ----------------------------------------------------------------------
void setSlimeMoveLeftState(Slime *slime)
{
    slime->moveLeftState = true;
    slime->moveRightState = false;
}

void setSlimeMoveRightState(Slime *slime)
{
    slime->moveLeftState = false;
    slime->moveRightState = true;
}

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

void moveSlimeLeft(Slime *slime)
{
    if (
        !slime->jumpState &&
        !slime->moveRightState)
    {
        setSlimeMoveLeftState(slime);
        slime->hMoveVector -= 0.2;
    }
    if (
        slime->jumpState &&
        !slime->moveRightState)
    {
        setSlimeMoveLeftState(slime);
        slime->hMoveVector -= 0.2;
    }
    if (slime->hMoveVector < -0.4)
    {
        slime->hMoveVector = -0.4;
    }
}

void moveSlimeRight(Slime *slime)
{
    if (
        !slime->jumpState &&
        !slime->moveLeftState)
    {
        setSlimeMoveRightState(slime);
        slime->hMoveVector += 0.2;
    }
    if (
        slime->jumpState &&
        !slime->moveLeftState)
    {
        setSlimeMoveRightState(slime);
        slime->hMoveVector += 0.2;
    }
    if (slime->hMoveVector > 0.4)
    {
        slime->hMoveVector = 0.4;
    }
}

void slimeFriction(Slime *slime)
{   
    if (!slime->moveLeftState && !slime->moveRightState && !slime->jumpState)
    {
        if (slime->hMoveVector > 0)
        {
            slime->hMoveVector -= 0.5;
            if (slime->hMoveVector < 0)
            {
                slime->hMoveVector = 0;
            }
        }

        if (slime->hMoveVector < 0)
        {
            slime->hMoveVector += 0.5;
            if (slime->hMoveVector > 0)
            {
                slime->hMoveVector = 0;
            }
        }
    }
}
// ----------------------------------------------------------------------

// Update
// ----------------------------------------------------------------------
void slimeRandomWalk(Slime *slime)
{   
    slime->updateCounter++;
    if(slime->updateCounter < 120) return;

    slime->updateCounter = 0;
    int randNum = GetRandomValue(0, 100);
    if (randNum < 30)
    {
        setSlimeMoveLeftState(slime);
    }
    else if (randNum < 60)
    {
        setSlimeMoveRightState(slime);
    }
    else
    {   
        slime->moveLeftState = false;
        slime->moveRightState = false;
    }
}

void updateSlimePosition(Slime *slime)
{
    if(slime->moveLeftState)
    {
        moveSlimeLeft(slime);
    }
    else if(slime->moveRightState)
    {
        moveSlimeRight(slime);
    }
    else
    {
        slimeFriction(slime);
    }

    slime->position.x += slime->hMoveVector;
    // slime->position.y += slime->vMoveVector;
}

// ----------------------------------------------------------------------

// Draw
// ----------------------------------------------------------------------
void drawSlime(Slime *slime)
{
    slime->frameCounter++;
    if (slime->frameCounter > 8)
    {
        slime->frameCounter = 0;

        if (slime->hittedState)
        {
            slime->hitFrameCounter++;
            if (slime->hitFrameCounter > 5)
            {
                slime->hittedState = false;
                slime->hitFrameCounter = 0;
            }
        }
    }

    DrawRectangle(slime->position.x, slime->position.y, slime->frameRec.width, slime->frameRec.height, slime->color);
}
// ----------------------------------------------------------------------
