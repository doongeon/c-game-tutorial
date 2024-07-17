#include "raylib.h"
#include "env_item.h"

#define TEXTURE_HEIGHT 10
#define TEXTURE_WIDTH 10

Image generateGrassTexture()
{
    Image image = GenImageColor(TEXTURE_WIDTH, TEXTURE_HEIGHT, DARKGREEN);

    for (int y = 0; y < TEXTURE_HEIGHT; y += 2)
    {
        for (int x = 0; x < TEXTURE_WIDTH; x += 2)
        {
            Color color = (GetRandomValue(0, 1) == 0) ? GREEN : DARKGREEN;
            ImageDrawPixel(&image, x, y, color);
        }
    }

    return image;
}

Texture2D getGrassTexture()
{
    Image grassImage = generateGrassTexture();
    Texture2D grassTexture = LoadTextureFromImage(grassImage);
    UnloadImage(grassImage);

    return grassTexture;
}

Image generateDirtTexture()
{
    Image image = GenImageColor(10, 10, DARKBROWN);

    for (int y = 0; y < TEXTURE_HEIGHT; y += 2)
    {
        for (int x = 0; x < 10; x += 2)
        {
            Color color = (GetRandomValue(0, 1) == 0) ? DARKBROWN : BROWN;
            ImageDrawPixel(&image, x, y, color);
        }
    }

    return image;
}

Texture2D getDirtTexture()
{
    Image dirtImage = generateDirtTexture();
    Texture2D dirtTexture = LoadTextureFromImage(dirtImage);
    UnloadImage(dirtImage);

    return dirtTexture;
}

void drawGrassFieldTexture(EnvItem envItem, Texture2D grassTexture, Texture2D dirtTexture)
{
    for ( // 언덕 흙 텍스쳐
        int x = envItem.rect.x;
        x < envItem.rect.x + envItem.rect.width;
        x += TEXTURE_WIDTH)
    {
        for (
            int y = envItem.rect.y + TEXTURE_HEIGHT;
            y < envItem.rect.y + envItem.rect.height;
            y += TEXTURE_HEIGHT)
        {
            DrawTexture(dirtTexture, x, y, WHITE);
        }
    }
    for ( // 언덕 잔지 텍스쳐
        int x = envItem.rect.x;
        x < envItem.rect.x + envItem.rect.width;
        x += TEXTURE_WIDTH)
    {
        for (
            int y = envItem.rect.y;
            y < envItem.rect.y + 10;
            y += TEXTURE_HEIGHT)
        {
            DrawTexture(grassTexture, x, y, WHITE);
        }
    }
}
