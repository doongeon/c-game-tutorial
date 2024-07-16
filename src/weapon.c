#include "raylib.h"

typedef struct Weapon
{
    char *name;
    Rectangle range;
} Weapon;

Weapon createSword()
{
    Weapon result;
    result.name = "sword";
    result.range = (Rectangle){0, 0, 35, 47};
    return result;
};