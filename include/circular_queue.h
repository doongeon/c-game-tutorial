#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stdbool.h>

#define MAX_QUEUE_SIZE 100  // 큐의 최대 크기 설정

typedef struct {
    int front;                // 큐의 앞쪽 인덱스
    int rear;                 // 큐의 뒤쪽 인덱스
    int data[MAX_QUEUE_SIZE]; // 큐 데이터 저장 배열
} CircularQueue;

// 큐 초기화 함수
void initQueue(CircularQueue* q);

// 큐가 비어있는지 확인하는 함수
bool isEmpty(CircularQueue* q);

// 큐가 가득 찼는지 확인하는 함수
bool isFull(CircularQueue* q);

// 큐에 데이터를 삽입하는 함수
bool enqueue(CircularQueue* q, int item);

// 큐에서 데이터를 제거하는 함수
bool dequeue(CircularQueue* q, int* item);

// 큐의 앞쪽 데이터를 확인하는 함수
bool peek(CircularQueue* q, int* item);

#endif // CIRCULAR_QUEUE_H
