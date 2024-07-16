#include "circular_queue.h"
#include <stdio.h>

// 큐 초기화 함수
void initQueue(CircularQueue* q) {
    q->front = 0;
    q->rear = 0;
}

// 큐가 비어있는지 확인하는 함수
bool isEmpty(CircularQueue* q) {
    return q->front == q->rear;
}

// 큐가 가득 찼는지 확인하는 함수
bool isFull(CircularQueue* q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

// 큐에 데이터를 삽입하는 함수
bool enqueue(CircularQueue* q, int item) {
    if (isFull(q)) {
        return false; // 큐가 가득 차서 삽입 불가
    }
    q->data[q->rear] = item;
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    return true;
}

// 큐에서 데이터를 제거하는 함수
bool dequeue(CircularQueue* q, int* item) {
    if (isEmpty(q)) {
        return false; // 큐가 비어서 제거 불가
    }
    *item = q->data[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return true;
}

// 큐의 앞쪽 데이터를 확인하는 함수
bool peek(CircularQueue* q, int* item) {
    if (isEmpty(q)) {
        return false; // 큐가 비어서 확인 불가
    }
    *item = q->data[q->front];
    return true;
}
