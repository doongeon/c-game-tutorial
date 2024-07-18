#include "raylib.h"
#include "constants.h"
#include "env_item.h"
#include <stdio.h>

#define SLIME_SIZE 10
#define SLIME_MAX_SPEED 0.4
#define SLIME_JUMP 10

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

Slime createSlime()
{
    Slime slime;
    slime.frameRec = (Rectangle){0, 0, SLIME_SIZE, SLIME_SIZE};
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

void setSlimeJumpState(Slime *slime)
{
    slime->jumpState = true;
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

float slimeBot(Slime slime)
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
    if (slime->hMoveVector < -SLIME_MAX_SPEED)
    {
        slime->hMoveVector = -SLIME_MAX_SPEED;
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
    if (slime->hMoveVector > SLIME_MAX_SPEED)
    {
        slime->hMoveVector = SLIME_MAX_SPEED;
    }
}

void moveSlimeJump(Slime *slime)
{
    if (!slime->jumpState)
    {
        slime->vMoveVector -= SLIME_JUMP;
    }
}

void handleSlimeEnvCollisionY(Slime *slime, EnvItem *envItems, int envItemsLength)
{
    bool hitObstacle = false;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        if (
            ei->blockY &&
            envItemLeft(*ei) <= slimeRight(*slime) &&
            envItemRight(*ei) >= slimeLeft(*slime) &&
            envItemTop(*ei) >= slimeBot(*slime) &&
            envItemTop(*ei) <= slimeBot(*slime) + slime->vMoveVector)
        {
            hitObstacle = true;
            if (hitObstacle)
                break;
        }
    }
    if (hitObstacle)
    {
        slime->vMoveVector = 0;
        slime->jumpState = false;
    }
    else
    {
        slime->vMoveVector += 1; // 중력처럼 작용
        slime->jumpState = true;
    }
}

void handleSlimeEnvCollisionX(Slime *slime, EnvItem *envItems, int envItemsLength)
{
    bool hitObstacle = false;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        if (
            ei->blockX &&
            envItemLeft(*ei) <= slimeRight(*slime) + slime->hMoveVector &&
            envItemRight(*ei) >= slimeLeft(*slime) + slime->hMoveVector &&
            envItemTop(*ei) < slimeBot(*slime) &&
            envItemBot(*ei) > slimeTop(*slime))
        {
            hitObstacle = true;
            if (hitObstacle)
            {   
                slime->hMoveVector = 0;
                break;
            }
        }
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

void slimeRandomWalk(Slime *slime)
{
    slime->updateCounter++;
    if (slime->updateCounter < 120)
        return;

    slime->updateCounter = 0;
    int randNum = GetRandomValue(0, 100);
    if (randNum < 10)
    {
        moveSlimeJump(slime);
        setSlimeMoveLeftState(slime);
    }
    else if (randNum < 30)
    {
        setSlimeMoveLeftState(slime);
    }
    else if (randNum < 40)
    {
        moveSlimeJump(slime);
        setSlimeMoveRightState(slime);
    }
    else if (randNum < 60)
    {
        setSlimeMoveRightState(slime);
    }
    else if (randNum < 70)
    {
        moveSlimeJump(slime);
        slime->moveLeftState = false;
        slime->moveRightState = false;
    }
    else
    {

        slime->moveLeftState = false;
        slime->moveRightState = false;
    }
}
// ----------------------------------------------------------------------

// Update
// ----------------------------------------------------------------------
void updateSlimePosition(Slime *slime, EnvItem *envItems, int envItemsLength)
{   
    slimeRandomWalk(slime);

    if (slime->moveLeftState)
    {
        moveSlimeLeft(slime);
    }
    else if (slime->moveRightState)
    {
        moveSlimeRight(slime);
    }
    else
    {
        slimeFriction(slime);
    }

    if(
        slimeLeft(*slime) + slime->hMoveVector <= 0 ||
        slimeRight(*slime) + slime->hMoveVector >= SCREEN_WIDTH
    )
    {
        slime->hMoveVector = 0;
    }

    handleSlimeEnvCollisionY(slime, envItems, envItemsLength);
    handleSlimeEnvCollisionX(slime, envItems, envItemsLength);

    slime->position.x += slime->hMoveVector;
    slime->position.y += slime->vMoveVector;
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

    DrawRectangle(slime->position.x, slime->position.y + 3, slime->frameRec.width, slime->frameRec.height, slime->color);
}
// ----------------------------------------------------------------------
