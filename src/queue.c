#include "globals.h"

// 새로운 노드를 만드는 function
struct Node* create_node(int k)
{
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp->key = k;
	temp->next = NULL;
	return temp;
}

// 새로운 빈 Queue를 만드는 function. 프로그램 시작때 한번만 실행.
struct Queue* create_queue()
{
	struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
	queue->front = queue->rear = NULL;
	return queue;
}

// queue의 가장 뒤에 int k를 추가하는 function. (즉, queue의 front에 새로운 노드를 등록)
void enqueue(struct Queue* queue, int k)
{
	struct Node* temp = create_node(k);

	// 만약 queue가 빈 상태라면 front와 rear 둘 다 새로운 노드를 등록
	if (queue->rear == NULL) {
		queue->front = queue->rear = temp;
		return;
	}

	// 현재 가장 뒤에 있는 노드의 next 값을 새로운 노드를 가르키게 함. 즉 원래 마지막 node의 next = temp
	// 그리고 새로 추가한 노드가 이제 rear가 됨.
	queue->rear->next = temp;
	queue->rear = temp;
}

// queue의 가장 앞에 있는 노드를 제거하는 function.
void dequeue(struct Queue* q)
{
	if (q->front == NULL)
		return;

	// 현재 front, 즉 지금 queue의 가장 앞에 있는 노드의 포인터를 temp에 저장.
	struct Node* temp = q->front;

	// 현재 front의 next, 즉 queue의 2번째 값을 front에 저장.
	q->front = q->front->next;

	// 만약 원래 queue의 2번째 값이 Null이었다면, 즉 queue에 값이 하나만 있었다면 queue는 빈 상태가 됨.
	// 따라서 front가 Null이면 rear도 Null.
	if (q->front == NULL)
		q->rear = NULL;

	// 첫번째 값을 메모리에서 제거.
	free(temp);
}

// 새로운 노드를 x번째 노드 이후에 삽입하는 function.
void insert_after_x(struct Queue* q, int key, int x) {
	struct Node* temp = create_node(key);
	struct Node* curr = q->front;
	int count = 0;

	while (curr != NULL) {

		// x번째 노드에 접근할 때까지 while문에서 "curr = 지금 노드가 가르키는 다음 노드"를 반복
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