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

	// 코멘트 리스트 생성
	struct CommentList* comment_list = create_comment_list();


	// 코멘트 입력 하는 방법:
	// 2번째 parameter에 문제 id, 3번째 parameter에 코멘트를 넣으면 됨
	// enqueue_comment(comment_list, 문제 id, 코멘트);

	// 코멘트 입력 테스트 (추후 삭제)
	enqueue_comment(comment_list, 1, "test");

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
			printf("주관식 문제");



			break;
		case 2:
			printf("사용자 정보");
			break;



		case 3:
			draw_title();
			while (1) {
				draw_options();
				key_pressed = getch();
				if (key_pressed == 'w' || key_pressed == 'W' || key_pressed == 72) {
					current_option_item = (current_option_item - 1 + 5) % 5;
				}
				else if (key_pressed == 's' || key_pressed == 'S' || key_pressed == 80) {
					current_option_item = (current_option_item + 1) % 5;
				}

				else if (key_pressed == 'a' || key_pressed == 'A' || key_pressed == 37) {

					switch (current_option_item) {
					case 0:
						if (interval_failed_questions > 1) {
							interval_failed_questions--;
						}
						break;
					case 1:
						if (font_size > 1) {
							font_size--;
							set_console_font_size(font_size);
						}
						break;
					case 2:
						if (color_mode > 0) {
							color_mode--;
							set_color_theme(color_mode);
							ClearScreen();
							draw_title();
							draw_options();
						}
						break;
					}

				}
				else if (key_pressed == 'd' || key_pressed == 'D' || key_pressed == 39) {
					switch (current_option_item) {
					case 0:
						if (interval_failed_questions < 50) {
							interval_failed_questions++;
						}
						break;
					case 1:
						if (font_size < 50) {
							font_size++;
							set_console_font_size(font_size);
						}
						break;
					case 2:
						if (color_mode < 3)
						{
							color_mode++;
							set_color_theme(color_mode);
							ClearScreen();
							draw_title();
							draw_options();
						}
						break;
					}

				}

				else if (key_pressed == '\r' && current_option_item == 3) {
					interval_failed_questions = 10;
					font_size = 25;				
					color_mode = 0;
					InitScreen();
					ClearScreen();
					draw_title();
					draw_options();

				}

				else if (key_pressed == '\r' && current_option_item == 4) {

					break;
				}

			}

			break;
		case 4:
			printf("프로그램 종료");

			//db_history.tsv에 history를 저장
			write_history(queue_objective, queue_subjective);

			//코멘트를 txt 파일로 출력
			write_txt_comments(comment_list);

			// 동적할당한 메모리 해제
			free(objective_questions);
			free(subjective_questions);

			return 0;
		default:
			break;
		}
	}
	return 0;
}
