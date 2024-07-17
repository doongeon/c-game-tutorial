#ifndef LINKED_DAMAGE_LIST
#define LINKED_DAMAGE_LIST

#include "damage.h"

typedef struct DamageNode
{
    Damage damage;
    struct DamageNode *next;
} DamageNode;

DamageNode* initializeList();

void append(DamageNode **head, Damage newData);

void deleteNode(DamageNode **head, int position);

void removeExpiredNode(DamageNode **head);

void drawDamages(DamageNode *node);

#endif