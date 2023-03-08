#include "globals.h"



int main()
{
	//전역 변수 Initialization
	init_globals();

	//콘솔창 Initialization.
	InitScreen();

	//db를 저장할 questions[] 선언
	ObjectiveQuestion* objective_questions = malloc(sizeof(ObjectiveQuestion) * MAX_QUESTIONS);
	SubjectiveQuestion* subjective_questions = malloc(sizeof(SubjectiveQuestion) * MAX_QUESTIONS);

	//tsv 파일에서 데이터 불러와서 questions[] 배열에 저장
	read_objective_questions(objective_questions);
	read_subjective_questions(subjective_questions);

	//히스토리를 저장할 queue 생성
	struct Queue* queue_objective = create_queue();
	struct Queue* queue_subjective = create_queue();

	read_history(queue_objective, queue_subjective);
	
	//만약 프로그램 첫 실행이라면 히스토리를 새로 채워 넣음.
	if (queue_objective->front == NULL)
	{
		for (int i = 0; i < num_objective_questions; i++) {
			enqueue(queue_objective, i);
		}
	}

	if (queue_subjective->front == NULL)
	{
		for (int i = 0; i < num_subjective_questions; i++) {
			enqueue(queue_subjective, i);
		}
	}

	// 문제 출제 및 사용자 입력 받기
	while (1)
	{
		ClearScreen();
		draw_title();

		while (1) {
			draw_menu();
			key_pressed = getch();
			if (key_pressed == 'w' || key_pressed == 'W' || key_pressed == 72) {
				current_menu_item = (current_menu_item - 1 + 5) % 5;
			}
			else if (key_pressed == 's' || key_pressed == 'S' || key_pressed == 80) {
				current_menu_item = (current_menu_item + 1) % 5;
			}
			else if (key_pressed == '\r') {
				ClearScreen();
				break;
			}
		}
		switch (current_menu_item)
		{
		case 0:
		{
			int solved_questions = 0;

			while (1)
			{
				int start = time(NULL);
				int id = queue_objective->front->key;

				questionrowchange(objective_questions, id);

				optionrowchange(objective_questions, id, 1);

				optionrowchange(objective_questions, id, 2);

				optionrowchange(objective_questions, id, 3);

				optionrowchange(objective_questions, id, 4);

		
				if (CheckAnswer(objective_questions, id) == 1) {
					enqueue(queue_objective, queue_objective->front->key);
					dequeue(queue_objective);
				}
				else {
					insert_after_x(queue_objective, queue_objective->front->key, interval_failed_questions);
					dequeue(queue_objective);
				}

				solved_questions++;
				while (getchar() != '\n');
				printf("다음 문제로 넘어가시려면 엔터를 누르세요\n종료를 원하시면 x를 누르세요.\n");
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

		case 1:
			printf("주관식 문제 풀기");



			break;
		case 2:
			printf("미니게임");
			break;
		case 3:
			printf("옵션");
			break;
		case 4:
			printf("프로그램 종료");

			//db_history.tsv에 history를 저장
			write_history(queue_objective, queue_subjective);

			// 동적할당한 메모리 해제
			free(objective_questions);
			free(subjective_questions);

			return 0;
		default:
			break;
		}
		key_pressed = getch();
	}
	return 0;
}
