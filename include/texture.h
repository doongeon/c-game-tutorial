#ifndef TEXTURE_H
#define TEXTURE_H

#include "raylib.h"

Texture2D getGrassTexture();

Texture2D getDirtTexture();

void drawGrassFieldTexture(EnvItem envItem, Texture2D grassTexture, Texture2D dirtTexture);

#endif

