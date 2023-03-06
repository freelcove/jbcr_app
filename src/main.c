#include "questions.h"
#include "interface.h"
#include "print.h"

int main()
{
	//콘솔창 Initialization.
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
		printf("풀 문제 수 입력: ");
		scanf("%d", &num_to_solve);
	} while (num_to_solve <= 0 || num_to_solve > num_questions);


	int i = 0;


	// 문제 출제 및 사용자 입력 받기
	while (i < num_to_solve) {

		int id = randnum();

		ClearScreen();
		//print question 테스트
		printquestion(questions, id);
		printoptions(questions, id);

		if (CheckAnswer(id)) {
			faltquestions(id);
		}
		int a = time(NULL);
		while (time(NULL) - a < 2);
		ClearScreen();
		// 다음 문제로 넘어가기
		i++;
	}
	//틀린 문제 풀기
	Percentage(num_to_solve);
	repeatquestions(questions, bool());


	free(questions); // 동적할당한 메모리 해제


	// 아래 코드로 questions[] db에 접근 가능

	//questions[i].id,				questions[i].question,		questions[i].option_1,
	//questions[i].option_2,		questions[i].option_3,		questions[i].option_4,
	//questions[i].right_answer,	questions[i].date

	return 0;
}
