#include "globals.h"

int main()
{

	// ���� ���� Initialization
	init_globals();

	LoadUserInfo();

	// �ܼ�â Initialization.
	InitScreen();

	// db�� ������ questions[] ����
	ObjectiveQuestion *objective_questions = malloc(sizeof(ObjectiveQuestion) * MAX_QUESTIONS);
	SubjectiveQuestion *subjective_questions = malloc(sizeof(SubjectiveQuestion) * MAX_QUESTIONS);

	// tsv ���Ͽ��� ������ �ҷ��ͼ� questions[] �迭�� ����
	read_objective_questions(objective_questions);
	read_subjective_questions(subjective_questions);

	// �����丮�� ������ queue ����
	struct Queue *queue_objective = create_queue();
	struct Queue *queue_subjective = create_queue();

	read_history(queue_objective, queue_subjective);

	// ���� ���α׷� ù �����̶�� �����丮�� ���� ä�� ����.
	if (queue_objective->front == NULL)
	{
		for (int i = 0; i < num_objective_questions; i++)
		{
			enqueue(queue_objective, i);
		}
	}

	if (queue_subjective->front == NULL)
	{
		for (int i = 0; i < num_subjective_questions; i++)
		{
			enqueue(queue_subjective, i);
		}
	}

	// �ڸ�Ʈ ����Ʈ ����
	struct CommentList *comment_list = create_comment_list();

	// �ڸ�Ʈ �Է� �ϴ� ���:
	// 2��° parameter�� ���� id, 3��° parameter�� �ڸ�Ʈ�� ������ ��
	// enqueue_comment(comment_list, ���� id, �ڸ�Ʈ);

	// �ڸ�Ʈ �Է� �׽�Ʈ (���� ����)
	enqueue_comment(comment_list, 1, "Test");

	while (1)
	{
		ClearScreen();
		draw_title();

		while (1)
		{
			draw_menu();
			key_pressed = getch();
			if (key_pressed == 'w' || key_pressed == 'W' || key_pressed == 72)
			{
				current_menu_item = (current_menu_item - 1 + 5) % 5;
			}
			else if (key_pressed == 's' || key_pressed == 'S' || key_pressed == 80)
			{
				current_menu_item = (current_menu_item + 1) % 5;
			}
			else if (key_pressed == '\r')
			{
				ClearScreen();
				break;
			}
			else if (key_pressed == 27)
			{
				ClearScreen();
				current_menu_item = 4;
				break;
			}
		}
		switch (current_menu_item)
		{

			// �޴� "������ ����"
		case 0:
		{
			all_process_objective(objective_questions, queue_objective);
		}
		break;

		// �޴� "�ְ��� ����"
		
		case 1:
			printf("�ְ��� ����\n\n\n");
			{
				int solved_questions = 0;

				while (1)
				{
					int id = queue_subjective->front->key;

					printf("%s\n", subjective_questions[id].definition);

					printf("\n������ �Է��ϼ���\n");
					char user_answer[MAX_LINE_LENGTH];
					scanf("%[^\n]%*c", user_answer);


					/*


			printf("\n������ �Է��ϼ���\n");
					char user_answer[MAX_LINE_LENGTH];
					fgets(user_answer, MAX_LINE_LENGTH, stdin);
					int len = strlen(user_answer);
					if (user_answer[len - 1] == '\n') {
						user_answer[len - 1] = '\0';
					}
					*/




					//subjective_questions, id
					if (match(user_answer, subjective_questions[id].name) == 0) { // match �Լ� Ȱ��
						printf("�����Դϴ�.\n");
						enqueue(queue_subjective, queue_subjective->front->key);
						dequeue(queue_subjective);
					}

					else {
						printf("�����Դϴ�.\n");
						insert_after_x(queue_subjective, queue_subjective->front->key, interval_failed_questions);
						dequeue(queue_subjective);
					}



					solved_questions++;
					printf("���� ������ �Ѿ�÷��� ���͸� ��������\n���Ḧ ���Ͻø� x�� ��������.\n");
					current_menu_item = 0;
					int swit = 0;
					while (1)
					{
						if (kbhit()) {
							char input = getchar();
							if (input == 'x')
								swit = 1;
							break;
						}
					}
					if (swit == 1)
					{
						ClearScreen();
						Percentage(solved_questions);
						break;
					}
					ClearScreen();
				}


			}
			break;

		

			// �޴� "�����"
		case 2:
			draw_title();
			current_menu_item = 0;
			while (1)
			{
				draw_user_options();
				key_pressed = getch();
				if (key_pressed == 27)
				{
					break;
				};
				controlUserOptions();
			}
			break;

			// �޴� "�ɼ�"
		case 3:
			draw_title();
			current_menu_item = 0;
			while (1)
			{
				draw_options();
				key_pressed = getch();
				if (key_pressed == 27)
				{
					break;
				};
				controlOptions();
			}
			break;
			
		case 4:
			printf("���α׷� ����");

			// db_history.tsv�� history�� ����
			write_history(queue_objective, queue_subjective);

			// �ڸ�Ʈ�� txt ���Ϸ� ���
			write_txt_comments(comment_list);

			WriteUserInfo();

			// �����Ҵ��� �޸� ����
			free(objective_questions);
			free(subjective_questions);

			return 0;
		default:
			break;
		}
	}
	return 0;
}
