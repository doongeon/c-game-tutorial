#ifndef TEXTURE_H
#define TEXTURE_H

#include "raylib.h"

Texture2D getGrassTexture();

Texture2D getDirtTexture();

Texture2D getRedBlockTexture();

Texture2D getWaterTexture();

void drawGrassFieldTexture(EnvItem envItem, Texture2D grassTexture, Texture2D dirtTexture);

void drawRedBlockTexture(EnvItem envItem, Texture2D RedBlockTexture);

void drawWaterTexture(EnvItem envItem, Texture2D waterTexture);

#endif

