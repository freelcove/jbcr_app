#pragma once
#include "globals.h"

#ifndef COMMENT_H
#define COMMENT_H

// linked list (LL) 링크드 리스트 형태의 노드. key값과 다음 node (next)에 대한 포인터를 저장함.
struct Comment {
	int id;
	int mode;
	char text[100];
	struct Comment* next;
};

// Queue 큐. 가장 앞의 노드와 가장 뒤의 노드, 딱 2가지만 저장함. 배열을 사용하지 않음.
struct Comment_list {
	struct Comment* front, * rear;
};


struct Comment* create_comment(int id, char* text);

struct Comment_list* create_comment_list();

void enqueue_comment(struct Comment_list* comment_list, int id, char* text);

void dequeue_comment(struct Comment_list* comment_list);

void write_txt_comments(struct Comment_list* comment_list);


#endif