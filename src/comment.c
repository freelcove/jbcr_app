#include "comment.h"

struct Comment* create_comment(int id, char* text)
{
	struct Comment* temp = (struct Comment*)malloc(sizeof(struct Comment));
	temp->id = id;
	temp->mode = current_menu_item;
	strncpy(temp->text, text, 100);
	temp->next = NULL;
	return temp;
}

// 새로운 빈 comment_list를 만드는 function. 프로그램 시작때 한번만 실행.
struct Comment_list* create_comment_list()
{
	struct Comment_list* comment_list = (struct Comment_list*)malloc(sizeof(struct Comment_list));
	comment_list->front = comment_list->rear = NULL;
	return comment_list;
}

void enqueue_comment(struct Comment_list* comment_list, int id, char* text) {
	struct Comment* new_comment = create_comment(id, text);

	if (comment_list->rear == NULL) {
		comment_list->front = comment_list->rear = new_comment;
		return;
	}

	comment_list->rear->next = new_comment;
	comment_list->rear = new_comment;
}


void dequeue_comment(struct Comment_list* comment_list) {
	if (comment_list->front == NULL)
		return;

	struct Comment* temp = comment_list->front;
	comment_list->front = comment_list->front->next;

	if (comment_list->front == NULL)
		comment_list->rear = NULL;

	free (temp);
}


void write_txt_comments(struct Comment_list* comment_list) {
	FILE* file;
	char* current_time_str = get_current_time();
	char file_name[50];
	sprintf(file_name, "comments/comments %s.txt", current_time_str);
	file = fopen(file_name, "a+");
	if (file == NULL) {
		printf("Failed to open file.\n");
		return;
	}

	struct Comment* curr_obj = comment_list->front;
	while (curr_obj != NULL) {
		char* mode_name;
		current_time_str = get_current_time();
		switch (curr_obj->mode)
		{
		case 0: mode_name = "객관식";
			break;
		case 1: mode_name = "주관식";
			break;
		default:
			break;
		}		
		fprintf(file, "%s\n", current_time_str);
		fprintf(file, "%s [%d]: %s\n\n", mode_name, curr_obj->id, curr_obj->text);
		curr_obj = curr_obj->next;
	}

	fclose(file);
}