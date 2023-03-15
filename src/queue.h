#pragma once
#include "globals.h"

#ifndef QUEUE_H
#define QUEUE_H

// linked list (LL) 링크드 리스트 형태의 노드. key값과 다음 node (next)에 대한 포인터를 저장함.
struct Node
{
	int key;
	struct Node *next;
};

// Queue 큐. 가장 앞의 노드와 가장 뒤의 노드, 딱 2가지만 저장함. 배열을 사용하지 않음.
struct Queue
{
	struct Node *front, *rear;
};

// 새로운 노드를 만드는 function
struct Node *create_node(int k);

// 새로운 빈 Queue를 만드는 function. 프로그램 시작때 한번만 실행.
struct Queue *create_queue();

// queue의 가장 뒤에 int k를 추가하는 function. (즉, queue의 front에 새로운 노드를 등록)
void enqueue(struct Queue *queue, int k);

// queue의 가장 앞에 있는 노드를 제거하는 function.
void dequeue(struct Queue *q);

// 새로운 노드를 x번째 노드 이후에 삽입하는 function.
void insert_after_x(struct Queue *q, int key, int x);

#endif