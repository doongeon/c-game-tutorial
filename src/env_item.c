#include <raylib.h>
#include "constants.h"

typedef struct EnvItem
{
    Rectangle rect;
    bool blockX;
    bool blockY;
    char *name;
    Color color;
} EnvItem;

EnvItem createEnvItem(char *name, Vector2 position, int width, int height, bool blockX, bool blockY)
{
    EnvItem envItem = (EnvItem){{position.x, position.y, (float)width * ENVITEM_WIDTH_UNIT, (float)height * ENVITEM_HEIGHT_UNIT}, blockX, blockY, name, GRAY};

    return envItem;
}