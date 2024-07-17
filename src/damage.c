#include "raylib.h"
#include "slime.h"
#include <stdio.h>

#define DAMAGE_FONT_SIZE 20

typedef struct Damage
{
    Vector2 position;
    int frameCounter;
    int duration;
} Damage;

Damage createDamage(Slime slime)
{
    Damage damage = {slime.position, 0, 20};
    return damage;
}

// Util
// ---------------------------------------------------------------------------
bool isDamageExpired(Damage damage)
{
    if (damage.frameCounter > damage.duration)
        return true;
    else
        return false;
}


// ---------------------------------------------------------------------------

// Draw
// ---------------------------------------------------------------------------
void drawDamage(Damage *damage)
{
    if (isDamageExpired(*damage)) return;
    damage->frameCounter++;
    DrawText("hit", (int)damage->position.x, (int)damage->position.y - 20, DAMAGE_FONT_SIZE, RED);
    damage->position.y -= 1;
}
// ---------------------------------------------------------------------------
