#ifndef MAP_CASTLE_H
#define MAP_CASTLE_H

#include "env_item.h"
#include "raylib.h"

typedef struct Map
{
    EnvItem *envItems;
    int envItemsLength;
} Map;

Map getMapCastle();

void drawMapCastle(
    Map mapCastle,
    Texture2D grassTexture,
    Texture2D dirtTexture,
    Texture2D redBlockTexture,
    Texture2D waterTexutre);

void freeMap(Map map);

#endif