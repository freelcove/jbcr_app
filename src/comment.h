#pragma once
#include "globals.h"

#ifndef COMMENT_H
#define COMMENT_H

// linked list (LL) ��ũ�� ����Ʈ ������ ���. key���� ���� node (next)�� ���� �����͸� ������.
struct Comment {
	int id;
	int mode;
	char text[256];
	struct Comment* next;
};

// Queue ť. ���� ���� ���� ���� ���� ���, �� 2������ ������. �迭�� ������� ����.
struct Comment_list {
	struct Comment* front, * rear;
};


struct Comment* create_comment(int id, char* text);

struct Comment_list* create_comment_list();

void enqueue_comment(struct Comment_list* comment_list, int id, char* text);

void dequeue_comment(struct Comment_list* comment_list);

void write_txt_comments(struct Comment_list* comment_list);


#endif