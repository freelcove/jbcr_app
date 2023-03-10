#include "globals.h"

// ���ο� ��带 ����� function
struct Node* create_node(int k)
{
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp->key = k;
	temp->next = NULL;
	return temp;
}

// ���ο� �� Queue�� ����� function. ���α׷� ���۶� �ѹ��� ����.
struct Queue* create_queue()
{
	struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
	queue->front = queue->rear = NULL;
	return queue;
}

// queue�� ���� �ڿ� int k�� �߰��ϴ� function. (��, queue�� front�� ���ο� ��带 ���)
void enqueue(struct Queue* queue, int k)
{
	struct Node* temp = create_node(k);

	// ���� queue�� �� ���¶�� front�� rear �� �� ���ο� ��带 ���
	if (queue->rear == NULL) {
		queue->front = queue->rear = temp;
		return;
	}

	// ���� ���� �ڿ� �ִ� ����� next ���� ���ο� ��带 ����Ű�� ��. �� ���� ������ node�� next = temp
	// �׸��� ���� �߰��� ��尡 ���� rear�� ��.
	queue->rear->next = temp;
	queue->rear = temp;
}

// queue�� ���� �տ� �ִ� ��带 �����ϴ� function.
void dequeue(struct Queue* q)
{
	if (q->front == NULL)
		return;

	// ���� front, �� ���� queue�� ���� �տ� �ִ� ����� �����͸� temp�� ����.
	struct Node* temp = q->front;

	// ���� front�� next, �� queue�� 2��° ���� front�� ����.
	q->front = q->front->next;

	// ���� ���� queue�� 2��° ���� Null�̾��ٸ�, �� queue�� ���� �ϳ��� �־��ٸ� queue�� �� ���°� ��.
	// ���� front�� Null�̸� rear�� Null.
	if (q->front == NULL)
		q->rear = NULL;

	// ù��° ���� �޸𸮿��� ����.
	free(temp);
}

// ���ο� ��带 x��° ��� ���Ŀ� �����ϴ� function.
void insert_after_x(struct Queue* q, int key, int x) {
	struct Node* temp = create_node(key);
	struct Node* curr = q->front;
	int count = 0;

	while (curr != NULL) {

		// x��° ��忡 ������ ������ while������ "curr = ���� ��尡 ����Ű�� ���� ���"�� �ݺ�
		if (count == x) {
			temp->next = curr->next;
			curr->next = temp;
			if (curr == q->rear) {
				q->rear = temp;
			}
			return;
		}
		curr = curr->next;
		count++;
	}
}