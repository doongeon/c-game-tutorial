#ifndef WEAPON_H
#define WEAPON_H

#include "raylib.h"

typedef struct Weapon
{
    char *name;
    Rectangle range;
} Weapon;

Weapon createSword();

#endif // WEAPON_H
