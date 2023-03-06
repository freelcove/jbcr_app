
#include "questions.h"
#include "interface.h"
#include "print.h"


int is_valid_input(char input) {
	// 입력값이 a~d 사이의 문자인지 체크하는 함수
	//a~d -> 1~4로 수정
	return input == '1' || input == '2' || input == '3' || input == '4';
}

int main()
{
	//콘솔 창 초기화. (화면 크기, 글자 색, 커서 깜빡임 등 설정)
	InitScreen();

	//db를 저장할 questions[] 선언
	Question* questions = malloc(sizeof(Question) * MAX_QUESTIONS);

	int num_questions;
	
	// 사용자가 입력한 문제 개수 저장
	int num_to_solve;

	//tsv 파일에서 데이터 불러와서 questions[] 배열에 저장
	read_questions(questions, &num_questions);

	// 사용자로부터 문제 개수 입력 받기
	do {
		printf("Enter the number of questions you want to solve: ");
		scanf("%d", &num_to_solve);
	} while (num_to_solve <= 0 || num_to_solve > num_questions);


	int i = 0;
	char input;

	// 문제 출제 및 사용자 입력 받기
	while (i < num_to_solve) {
		//print question 테스트
		printquestion(questions, i);
		printoptions(questions, i);

		//사용자 입력 받기
		printf("Input answr (1~4): \n");
		scanf(" %c", &input);

		// 입력값이 유효한지 체크
		while (!is_valid_input(input)) {
			printf("Invalid input. Enter your answer (1~4): \n");
			scanf(" %c", &input);
		}

		// 정답 체크
		if (input == questions[i].right_answer[0]) {
			printf("Correct!\n\n");
		}
		else {
			printf("Incorrect. \nThe correct answer is %s.\n\n", questions[i].right_answer);
		}

		// 다음 문제로 넘어가기
		i++;
	}

	free(questions); // 동적할당한 메모리 해제


	// 아래 코드로 questions[] db에 접근 가능

	//questions[i].id, questions[i].question, questions[i].option_1,
	//questions[i].option_2, questions[i].option_3, questions[i].option_4,
	//    questions[i].right_answer, questions[i].date


	return 0;
}