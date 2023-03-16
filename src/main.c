#include "globals.h"

int main()
{

	// ���� ���� Initialization
	initGlobals();

	// ��Ʈ �ٲٱ�
	CONSOLE_FONT_INFOEX font_info = {sizeof(CONSOLE_FONT_INFOEX)};
	wcscpy(font_info.FaceName, L"D2Coding");
	if (!SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font_info))
	{
		wcscpy(font_info.FaceName, L"Segoe UI");
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font_info);
	}

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
	// enqueueRandom()�� db�� ���� ������ �޸� �����ϰ� ����.
	if (queue_objective->front == NULL)
	{
		enqueueRandom(queue_objective, num_objective_questions);
	}

	if (queue_subjective->front == NULL)
	{
		enqueueRandom(queue_subjective, num_subjective_questions);
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

			// current_mode = �ְ��� ����
		case 1:
			all_process_subjective(subjective_questions, queue_objective);

			break;

			// current_mode = ���
		case 2:
			drawTitle();
			char info0[50];
			sprintf(info0, "������ Best: %d  |  �ְ��� Best: %d", best_streak_objective, best_streak_subjective);

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
