#include "globals.h"

int main()
{

	// ���� ���� Initialization
	initGlobals();

	loadUserInfo();

	// �ܼ�â Initialization.
	initScreen();

	// db�� ������ questions[] ����
	ObjectiveQuestion *objective_questions = malloc(sizeof(ObjectiveQuestion) * MAX_QUESTIONS);
	SubjectiveQuestion *subjective_questions = malloc(sizeof(SubjectiveQuestion) * MAX_QUESTIONS);

	// tsv ���Ͽ��� ������ �ҷ��ͼ� questions[] �迭�� ����
	readObjectiveQuestions(objective_questions);
	readSubjectiveQuestions(subjective_questions);

	// �����丮�� ������ queue ����
	struct Queue *queue_objective = create_queue();
	struct Queue *queue_subjective = create_queue();

	readHistory(queue_objective, queue_subjective);

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

	const char *main_menu_items[] = {"1. ������ ����",
									 "2. �ְ��� Ǯ��",
									 "3. ���",
									 "4. �ɼ�",
									 "5. ����"};
	int num_main_menu_items = sizeof(main_menu_items) / sizeof(main_menu_items[0]);
	5;

	// ���θ޴� = 5
	// ������ = 0
	// �ְ��� = 1
	// ����� = 2
	// �ɼ�	= 3
	// ���� = 4

	while (1)
	{
		clearScreen();
		switch (current_mode)
		{

			// current_mode = ���θ޴�
		case 5:

			drawTitle();
			drawMenu(num_main_menu_items, main_menu_items, 28, 16);
			controlMainMenu(processUserInput(num_main_menu_items));
			break;

			// current_mode = ������ ����
		case 0:
			all_process_objective(objective_questions, queue_objective);
			break;

			// current_mode = ������ ����
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

					// subjective_questions, id
					if (match(user_answer, subjective_questions[id].name) == 0)
					{ // match �Լ� Ȱ��
						printf("�����Դϴ�.\n");
						enqueue(queue_subjective, queue_subjective->front->key);
						dequeue(queue_subjective);
					}

					else
					{
						printf("�����Դϴ�.\n");
						printf("\n������ \033[1m%s\033[0m �Դϴ�.\n", subjective_questions[id].name);
						insert_after_x(queue_subjective, queue_subjective->front->key, interval_failed_questions);
						dequeue(queue_subjective);
					}

					solved_questions++;
					printf("���� ������ �Ѿ�÷��� ���͸� ��������\n���Ḧ ���Ͻø� x�� ��������.\n");
					current_menu = 0;
					int swit = 0;
					while (1)
					{
						if (kbhit())
						{
							char input = getchar();
							if (input == 'x')
								swit = 1;
							break;
						}
					}
					if (swit == 1)
					{
						clearScreen();
						Percentage(solved_questions);
						current_mode = 5;
						current_menu = 0;
						break;
					}
					clearScreen();
				}
			}
			break;

			// current_mode = ���
		case 2:
			drawTitle();
			char info0[50];
			sprintf(info0, "Best Streak: %d", best_streak);

			char info1[50];
			int objective_percentage = (total_tried_objective == 0) ? 0 : (double)total_right_objective / total_tried_objective * 100;
			sprintf(info1, "������ Ǭ ���� ��: %d | �����: %d%%", total_tried_objective, objective_percentage);

			char info2[50];
			int subjective_percentage = (total_tried_subjective == 0) ? 0 : (double)total_right_subjective / total_tried_subjective * 100;
			sprintf(info2, "�ְ��� Ǭ ���� ��: %d | �����: %d%%", total_tried_subjective, subjective_percentage);

			char *info_items[] = {info0, info1, info2, "��� �ʱ�ȭ", "�ڷ� ����"};
			int num_info_items = sizeof(info_items) / sizeof(info_items[0]);

			drawMenu(num_info_items, info_items, 22, 16);
			controlInfo(processUserInput(num_info_items));
			break;
			drawTitle();

			// current_mode = �ɼ�
		case 3:
			drawTitle();
			char option0[50];
			sprintf(option0, "Ʋ�� ���� ���н� �ֱ�: %02d", interval_failed_questions);

			char option1[20];
			sprintf(option1, "ȭ�� ũ��: %d", font_size);

			char option2[20];
			sprintf(option2, "�׸�: %d", color_mode);

			char *option_items[] = {option0,
									option1,
									option2,
									"����Ʈ ������ �ɼ� �ʱ�ȭ",
									"�ڷ� ����"};
			int num_option_items = sizeof(option_items) / sizeof(option_items[0]);

			drawMenu(num_option_items, option_items, 25, 16);
			controlOptions(processUserInput(num_option_items));
			break;

			// current_mode = ����
		case 4:
			printf("���α׷� ����");

			// db_history.tsv�� history�� ����
			writeHistory(queue_objective, queue_subjective);

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
