#ifndef DAMAGE_H
#define DAMAGE_H

#include "raylib.h"

#include "slime.h"

typedef struct Damage
{
    Vector2 position;
    int frameCounter;
    int duration;
} Damage;

Damage createDamage(Slime slime);

bool isDamageExpired(Damage damage);

void drawDamage(Damage *damage);

#endif

