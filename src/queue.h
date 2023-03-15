#pragma once
#include "globals.h"

#ifndef QUEUE_H
#define QUEUE_H

// linked list (LL) ��ũ�� ����Ʈ ������ ���. key���� ���� node (next)�� ���� �����͸� ������.
struct Node
{
	int key;
	struct Node *next;
};

// Queue ť. ���� ���� ���� ���� ���� ���, �� 2������ ������. �迭�� ������� ����.
struct Queue
{
	struct Node *front, *rear;
};

// ���ο� ��带 ����� function
struct Node *create_node(int k);

// ���ο� �� Queue�� ����� function. ���α׷� ���۶� �ѹ��� ����.
struct Queue *create_queue();

// queue�� ���� �ڿ� int k�� �߰��ϴ� function. (��, queue�� front�� ���ο� ��带 ���)
void enqueue(struct Queue *queue, int k);

// queue�� ���� �տ� �ִ� ��带 �����ϴ� function.
void dequeue(struct Queue *q);

// ���ο� ��带 x��° ��� ���Ŀ� �����ϴ� function.
void insert_after_x(struct Queue *q, int key, int x);

#endif