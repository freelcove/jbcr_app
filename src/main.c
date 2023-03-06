#include "globals.h"
#include "questions.h"
#include "interface.h"
#include "print.h"



int main()
{

	COORD cursorPosition = { 0, 0 };

	//콘솔 관련 함수 사용에 필요
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	//콘솔창 Initialization.
	InitScreen(console);

	//db를 저장할 questions[] 선언
	Question* questions = malloc(sizeof(Question) * MAX_QUESTIONS);

	// 총 문제 수;
	int num_questions;

	//tsv 파일에서 데이터 불러와서 questions[] 배열에 저장
	read_questions(questions, &num_questions);

	int current_menu_item = 0;

	char key_pressed = ' ';
	

	// 문제 출제 및 사용자 입력 받기
	while (1)
	{
		ClearScreen();
		
		draw_title();
		while (1) {
			draw_menu(console, &current_menu_item, cursorPosition);
			key_pressed = getch();
			if (key_pressed == 'w' || key_pressed == 'W') {
				current_menu_item = (current_menu_item - 1 + 5) % 5;
			}
			else if (key_pressed == 's' || key_pressed == 'S') {
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
			draw_objective_question(console, questions, 4, cursorPosition);
			break;
		case 1:
			printf("주관식 문제 풀기");
			break;
		case 2:
			printf("미정");
			break;
		case 3:
			printf("옵션");
			break;
		case 4:
			printf("프로그램 종료");
			return 0;
		default:
			break;
		}

		key_pressed = getch();


		// 아래 코드로 questions[] db에 접근 가능

		//questions[i].id,				questions[i].question,		questions[i].option_1,
		//questions[i].option_2,		questions[i].option_3,		questions[i].option_4,
		//questions[i].right_answer,	questions[i].date

		

		
	}
	free(questions); // 동적할당한 메모리 해제
	return 0;
}
