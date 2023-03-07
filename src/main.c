#include "globals.h"
#include "questions.h"
#include "interface.h"
#include "print.h"
#include <conio.h> 



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
			
			//사용자 입력 받기
			
			/*
			
			do while() 써서 key_pressed = getch(); 한번은 먼저 입력 받음.
			그리고 while문에서 1~4 또는 종료 키가 나오기 전까지 아무 반응 하지 않기.
			
			if (key_pressed == 정답){
			정답임을 표시
			}

			else (정답이 아니면){
			오답과 정답 표시
			}
			
			사용자 맞춤 학습 데이터 추가 함수 call.

			key_pressed = getch();
			사용자 입력 받아서 추가 행동 실행: 일단은 다음 문제로 넘어가기 하나만 구현				

			
			*/

		{
			while (1)
			{
				int start = time(NULL);
				int id = randnum();
				rowchange(questions, id, 0);
				puts("");
				rowchange(questions, id, 1);
				puts("");
				rowchange(questions, id, 2);
				puts("");
				rowchange(questions, id, 3);
				puts("");
				rowchange(questions, id, 4);
				puts("");
				CheckAnswer(id);
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
					break;
				ClearScreen();
			}
		}
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
