#include "globals.h"

int main()
{

	// 전역 변수 Initialization
	init_globals();

	LoadUserInfo();

	// 콘솔창 Initialization.
	InitScreen();

	// db를 저장할 questions[] 선언
	ObjectiveQuestion *objective_questions = malloc(sizeof(ObjectiveQuestion) * MAX_QUESTIONS);
	SubjectiveQuestion *subjective_questions = malloc(sizeof(SubjectiveQuestion) * MAX_QUESTIONS);

	// tsv 파일에서 데이터 불러와서 questions[] 배열에 저장
	read_objective_questions(objective_questions);
	read_subjective_questions(subjective_questions);

	// 히스토리를 저장할 queue 생성
	struct Queue *queue_objective = create_queue();
	struct Queue *queue_subjective = create_queue();

	read_history(queue_objective, queue_subjective);

	// 만약 프로그램 첫 실행이라면 히스토리를 새로 채워 넣음.
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

	// 코멘트 리스트 생성
	struct CommentList *comment_list = create_comment_list();

	// 코멘트 입력 하는 방법:
	// 2번째 parameter에 문제 id, 3번째 parameter에 코멘트를 넣으면 됨
	// enqueue_comment(comment_list, 문제 id, 코멘트);

	// 코멘트 입력 테스트 (추후 삭제)
	enqueue_comment(comment_list, 1, "Test");

	while(1){
		clearScreen();
		drawScreen();
		getUserInput();
		processUserInput();
	}
/*
	while (1)
	{
		clearScreen();
		drawTitle();

		while (1)
		{
			draw_menu();
			app_input = getch();
			if (app_input == 'w' || app_input == 'W' || app_input == 72)
			{
				app_menu_item = (app_menu_item - 1 + 5) % 5;
			}
			else if (app_input == 's' || app_input == 'S' || app_input == 80)
			{
				app_menu_item = (app_menu_item + 1) % 5;
			}
			else if (app_input == '\r')
			{
				clearScreen();
				break;
			}
			else if (app_input == 27)
			{
				clearScreen();
				app_menu_item = 4;
				break;
			}
		}
		switch (app_menu_item)
		{

			// 메뉴 "객관식 문제"
		case 0:
		{
			all_process_objective(objective_questions, queue_objective);
		}
		break;

		// 메뉴 "주관식 문제"
		case 1:
			break;

			// 메뉴 "사용자"
		case 2:
			drawTitle();
			app_menu_item = 0;
			while (1)
			{
				draw_user_options();
				app_input = getch();
				if (app_input == 27)
				{
					break;
				};
				void controlUserOptions();
			}
			break;

			// 메뉴 "옵션"
		case 3:
			drawTitle();
			app_menu_item = 0;
			while (1)
			{
				draw_options();
				app_input = getch();
				if (app_input == 27)
				{
					break;
				};
				controlOptions();
			}
			break;
			
		case 4:
			printf("프로그램 종료");

			// db_history.tsv에 history를 저장
			write_history(queue_objective, queue_subjective);

			// 코멘트를 txt 파일로 출력
			write_txt_comments(comment_list);

			WriteUserInfo();

			// 동적할당한 메모리 해제
			free(objective_questions);
			free(subjective_questions);

			return 0;
		default:
			break;
		}
	}
	*/
	return 0;
}
