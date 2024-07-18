#include <stdlib.h>
#include <stdio.h>

#include "env_item.h"
#include "raylib.h"
#include "constants.h"
#include "texture.h"

typedef struct Map
{
    EnvItem *envItems;
    int envItemsLength;
} Map;

Map getMapCastle()
{   
    // 맵 환경 아이템 그리기
    //
    EnvItem envItemsTemp[] = {
        createEnvItem(
            "background",
            (Vector2){0, 0},
            SCREEN_WIDTH / ENVITEM_WIDTH_UNIT + 1,
            SCREEN_HEIGHT / ENVITEM_HEIGHT_UNIT + 1,
            0, 0),
        createEnvItem(
            "ground",
            (Vector2){0, GROUND_Y_POSITION},
            SCREEN_WIDTH / ENVITEM_WIDTH_UNIT + 1,
            (SCREEN_HEIGHT - GROUND_Y_POSITION) / ENVITEM_HEIGHT_UNIT + 1,
            0, 1),
        createEnvItem(
            "hill",
            (Vector2){500, GROUND_Y_POSITION - ENVITEM_HEIGHT_UNIT},
            3,
            1,
            0, 1),
        createEnvItem(
            "fence",
            (Vector2){300, GROUND_Y_POSITION - ENVITEM_HEIGHT_UNIT},
            1,
            2,
            1, 1),
        createEnvItem(
            "wall top 01",
            (Vector2){ENVITEM_HEIGHT_UNIT * 1 - 30, GROUND_Y_POSITION - ENVITEM_HEIGHT_UNIT * 2 - 20},
            1,
            1,
            0, 0),
        createEnvItem(
            "wall top 02",
            (Vector2){ENVITEM_HEIGHT_UNIT * 2 - 20, GROUND_Y_POSITION - ENVITEM_HEIGHT_UNIT * 2 - 20},
            1,
            1,
            0, 0),
        createEnvItem(
            "wall top 03",
            (Vector2){ENVITEM_HEIGHT_UNIT * 3 - 10, GROUND_Y_POSITION - ENVITEM_HEIGHT_UNIT * 2 - 20},
            1,
            1,
            0, 0),
        createEnvItem(
            "wall top 04",
            (Vector2){ENVITEM_HEIGHT_UNIT * 4, GROUND_Y_POSITION - ENVITEM_HEIGHT_UNIT * 2 - 20},
            1,
            1,
            0, 0),
        createEnvItem(
            "wall",
            (Vector2){0, GROUND_Y_POSITION - ENVITEM_HEIGHT_UNIT * 2},
            5,
            2,
            0, 0),
        createEnvItem(
            "pond",
            (Vector2){200, GROUND_Y_POSITION},
            2,
            0,
            0, 0)};
    int envItemsLength = sizeof(envItemsTemp) / sizeof(EnvItem);
    //


    // 동적 할당후 복사
    //
    EnvItem *envItems = (EnvItem *)malloc(sizeof(EnvItem) * envItemsLength);
    for(int i = 0; i < envItemsLength; i++)
    {   
        *(envItems + i) = envItemsTemp[i];
        printf("env name:%s\n", (envItems + i)->name);
    }

    Map mapCastle = (Map){envItems, envItemsLength};
    //

    return mapCastle;
}

void drawMapCastle(
    Map mapCastle, Texture2D grassTexture,
    Texture2D dirtTexture,
    Texture2D redBlockTexture,
    Texture2D waterTexutre)
{   
    drawGrassFieldTexture(*(mapCastle.envItems + 1), grassTexture, dirtTexture);
    drawGrassFieldTexture(*(mapCastle.envItems + 2), grassTexture, dirtTexture);
    drawGrassFieldTexture(*(mapCastle.envItems + 3), grassTexture, dirtTexture);
    drawRedBlockTexture(*(mapCastle.envItems + 4), redBlockTexture);
    drawRedBlockTexture(*(mapCastle.envItems + 5), redBlockTexture);
    drawRedBlockTexture(*(mapCastle.envItems + 6), redBlockTexture);
    drawRedBlockTexture(*(mapCastle.envItems + 7), redBlockTexture);
    drawRedBlockTexture(*(mapCastle.envItems + 8), redBlockTexture);
    drawWaterTexture(*(mapCastle.envItems + 9), waterTexutre);
}

void freeMap(Map map)
{
    free(map.envItems);
}