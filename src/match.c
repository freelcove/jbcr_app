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
	char subjective_data_answer[MAX_LINE_LENGTH] = {0};
	strcpy(subjective_data_answer, subjective_questions[id].name);
	int i = 0;
	int subjective_len = 0;
	int check_subjective_correct = 1;
	int k, l;
	for (k = 0, l = 0; user_answer[k]; k++)
	{
		if (user_answer[k] != ' ')
		{
			user_answer[l++] = user_answer[k];
		}
	}
	user_answer[l] = '\0';
	for (k = 0, l = 0; subjective_data_answer[k]; k++)
	{
		if (subjective_data_answer[k] != ' ')
		{
			subjective_data_answer[l++] = subjective_data_answer[k];
		}
	}
	subjective_data_answer[l] = '\0';
	while (user_answer[i] != NULL)
	{
		if (user_answer[i] >= 'a' && user_answer[i] <= 'z')
			user_answer[i] += 'A' - 'a';
		i++;
	}
	i = 0;

	while (subjective_data_answer[i] != NULL)
	{
		if (subjective_data_answer[i] >= 'a' && subjective_data_answer[i] <= 'z')
			subjective_data_answer[i] += 'A' - 'a';
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
		while (subjective_data_answer[subjective_len] != ',' && subjective_data_answer[subjective_len] != NULL)
		{
			subjective_answer[i] = subjective_data_answer[subjective_len];
			subjective_len++;
			i++;
		}
		i = 0;
		subjective_len += 1;
		int num = 1;
		if (user_answer[i] != subjective_answer[i] && subjective_answer[i] != NULL)
		{

			if (subjective_data_answer[subjective_len - 1] == NULL)
				break;
			continue;
		}
		else if (strlen(user_answer) != strlen(subjective_answer))
		{
			if (subjective_data_answer[subjective_len - 1] == NULL)
				break;
			continue;
		}
		num = strcmp(user_answer, subjective_answer);
		if (num == 0)
		{ // match 함수 활용
			SetConsoleTextAttribute(console, select_color(-1));
			printf("\n\t     정답입니다!\n");
			SetConsoleTextAttribute(console, color_mode_preset[color_mode % 4]);
			printf("\n\t     정답: ");
			SetConsoleTextAttribute(console, select_color(-1));
			printf("%s", subjective_questions[id].name);
			SetConsoleTextAttribute(console, color_mode_preset[color_mode % 4]);
			printf("\n");
			current_streak_subjective++;
			if (best_streak_subjective < current_streak_subjective)
				best_streak_subjective = current_streak_subjective;
			printf("\n\n\t     현재 연속으로 맞춘 수: %d\tBEST: %d", current_streak_subjective, best_streak_subjective);
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
		strcpy(temp + strlen(temp), subjective_questions[id].definition);
		printf("\t\t\t\t\t\t\tBEST: %d", best_streak_subjective);
		print_change_row(temp);
		printf("\n");
		printf("\t     답을 입력하세요:  ");
		SetCursorVisibility(1);
		fgets(user_answer, sizeof(user_answer), stdin);
		SetCursorVisibility(0);
		user_answer[strcspn(user_answer, "\n")] = 0;

		if (check_subjective_correction(subjective_questions, id, queue_subjective))
		{
			faltcount++;
			int temp_color_mode;
			switch (color_mode)
			{
			case 0:
				temp_color_mode = 252;
				break;
			case 1:
				temp_color_mode = 132;
				break;
			case 2:
				temp_color_mode = 188;
				break;
			case 3:
				temp_color_mode = 236;
				break;
			default:
				break;
			}
			SetConsoleTextAttribute(console, temp_color_mode);
			printf("\n\t     오답입니다.\n");
			set_color_theme(color_mode);

			printf("\n\t     정답: ");
			SetConsoleTextAttribute(console, select_color(-1));
			printf("%s", subjective_questions[id].name);
			SetConsoleTextAttribute(console, color_mode_preset[color_mode % 4]);
			current_streak_subjective = 0;
			insert_after_x(queue_subjective, queue_subjective->front->key, interval_failed_questions);
			dequeue(queue_subjective);
		}

		// clearInputBuffer();
		solved_questions++;
		printf("\n\n\n\t     다음 문제로 넘어가시려면 Enter를 누르세요.\n");
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
