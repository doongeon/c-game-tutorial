#include <stdlib.h>
#include <stdio.h>

#include "damage.h"

typedef struct DamageNode
{
    Damage damage;
    struct DamageNode *next;
} DamageNode;

DamageNode *initializeList()
{
    return NULL; // 초기에는 리스트가 비어 있으므로 NULL을 반환
}

bool isDamageListEmpty(DamageNode **head)
{
    if (*head == NULL)
        return true;
    else
        return false;
}

void append(DamageNode **head, Damage newData)
{
    DamageNode *newNode = (DamageNode *)malloc(sizeof(DamageNode));
    newNode->damage = newData;
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        DamageNode *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void deleteNode(DamageNode **head, int position)
{
    if (*head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    DamageNode *temp = *head;

    if (position == 0)
    {
        *head = temp->next;
        free(temp);
        return;
    }

    for (int i = 0; temp != NULL && i < position - 1; i++)
    {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL)
    {
        printf("Position not found.\n");
        return;
    }

    DamageNode *next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

void removeExpiredNode(DamageNode **head)
{
    // 헤드가 NULL이면 바로 리턴
    if (*head == NULL)
        return;

    // 첫 번째 노드부터 연속적으로 만료된 노드를 제거
    while (*head != NULL && isDamageExpired((*head)->damage))
    {
        DamageNode *temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    // 만약 모든 노드가 제거되었다면 함수 종료
    if (*head == NULL)
        return;

    // 두 번째 루프: 중간이나 마지막에 있는 만료된 노드 제거
    DamageNode *current = *head;
    while (current->next != NULL)
    {
        if (isDamageExpired(current->next->damage))
        {
            DamageNode *temp = current->next;
            current->next = current->next->next;
            free(temp);
        }
        else
        {
            current = current->next;
        }
    }
}


void drawDamages(DamageNode *node)
{
    while (node != NULL)
    {
        drawDamage(&(node->damage));
        node = node->next;
    }
}