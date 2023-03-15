#include "globals.h"

int match(char *user_answer, char *subjective_questions)
{
	int i = 0;
	while (user_answer[i] != '\0' && subjective_questions[i] != '\0')
	{
		if (user_answer[i] != subjective_questions[i])
		{
			return 1;
		}
		i++;
	}
	if (user_answer[i] != '\0' || subjective_questions[i] != '\0')
	{
		return 1;
	}

	return 0;
}

int check_subjective_correction(SubjectiveQuestion *subjective_questions, int id, struct Queue *queue_subjective)
{

	char subjective_answer[MAX_LINE_LENGTH] = {0};
	int i = 0;
	int subjective_len = 0;
	int check_subjective_correct = 1;
	while (user_answer[i] != NULL)
	{
		if (user_answer[i] >= 'a' && user_answer[i] <= 'z')
			user_answer[i] += 'A' - 'a';
		i++;
	}
	i = 0;
	while (subjective_questions[id].name[i] != NULL)
	{
		if (subjective_questions[id].name[i] >= 'a' && subjective_questions[id].name[i] <= 'z')
			subjective_questions[id].name[i] += 'A' - 'a';
		i++;
	}
	i = 0;
	while (1)
	{
		int len = strlen(subjective_answer - 1);
		while (i != len)
		{
			subjective_answer[i] = NULL;
			i++;
		}
		i = 0;
		while (subjective_questions[id].name[subjective_len] != ',' && subjective_questions[id].name[subjective_len] != NULL)
		{
			subjective_answer[i] = subjective_questions[id].name[subjective_len];
			subjective_len++;
			i++;
		}
		i = 0;
		subjective_len += 1;
		int num=1;
		if (user_answer[i] != subjective_answer[i] && subjective_answer[i] != NULL)
		{

			if (subjective_questions[id].name[subjective_len - 1] == NULL)
				break;
			continue;
		}
		else if (strlen(user_answer) != strlen(subjective_answer))
		{
			if (subjective_questions[id].name[subjective_len - 1] == NULL)
				break;
			continue;
		}
		num=strcmp(user_answer, subjective_answer);
		if (num == 0)
		{ // match 함수 활용
			SetConsoleTextAttribute(console, select_color(-1));
			printf("\n\t     정답입니다!\n");
			SetConsoleTextAttribute(console, color_mode_preset[color_mode % 4]);
			current_streak_subjective++;
			if (best_streak_subjective < current_streak_subjective)
				best_streak_subjective = current_streak_subjective;
			printf("\t     현재까지 맞춘 문제수 : %d\tBEST : %d\n", current_streak_subjective, best_streak_subjective);
			enqueue(queue_subjective, queue_subjective->front->key);
			dequeue(queue_subjective);
			check_subjective_correct = 0;
			return 0;
		}
	}
	return check_subjective_correct;
}

void all_process_subjective(SubjectiveQuestion *subjective_questions, struct Queue *queue_subjective)
{
	int solved_questions = 0;
	current_streak_subjective = 0;
	faltcount = 0;

	while (1)
	{
		
		int id = queue_subjective->front->key;

		check_subjective = 1;
		char temp[1024] = "\n\n\n\t     Q. ";
		strcpy(temp+strlen(temp), subjective_questions[id].definition);
		printf("\t\t\t\t\t\t\t\tBEST : %d", best_streak_subjective);
		print_change_row(temp);
		printf("\n");
		printf("\t     정답을 입력하세요 :  ");

		fgets(user_answer, sizeof(user_answer), stdin);
		user_answer[strcspn(user_answer, "\n")] = 0;

		if (check_subjective_correction(subjective_questions, id, queue_subjective))
		{
			faltcount++;
			char error_message[100];
			sprintf(error_message, "%s은(는) 오답입니다.", user_answer);
			printf("\n\t     %s\n", error_message);

			printf("\t     정답은 ");
			SetConsoleTextAttribute(console, select_color(-1));
			printf("%s", subjective_questions[id].name);
			SetConsoleTextAttribute(console, color_mode_preset[color_mode % 4]);
			printf(" 입니다.\n");
			current_streak_subjective = 0;
			printf("\n\t     BEST : %d\n", best_streak_subjective);
			insert_after_x(queue_subjective, queue_subjective->front->key, interval_failed_questions);
			dequeue(queue_subjective);
		}

		// clearInputBuffer();
		solved_questions++;
		printf("\n\n\t     다음 문제로 넘어가시려면 Enter를 누르세요.\n");
		printf("\t     종료를 원하시면 Esc를 누르세요.\n");

		key_pressed = getch();
		if (key_pressed == 27)
		{			
			exit_menu(solved_questions);
			break;
		}

		clearScreen();
	}
	total_tried_subjective += solved_questions;
	total_right_subjective += solved_questions - faltcount;
	solved_questions = 0;
	faltcount = 0;
	current_streak_subjective = 0;
}
