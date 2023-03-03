
#include "questions.h"
#include "interface.h"
#include "print.h"


int main() {

	//콘솔 창 초기화. (화면 크기, 글자 색, 커서 깜빡임 등 설정)
	InitScreen();

	//db를 저장할 questions[] 선언
	Question* questions = malloc(sizeof(Question) * MAX_QUESTIONS);

	int num_questions;

	//tsv 파일에서 데이터 불러와서 questions[] 배열에 저장
	read_questions(questions, &num_questions);

	// 아래 코드로 questions[] db에 접근 가능

	//questions[i].id, questions[i].question, questions[i].option_1,
	//questions[i].option_2, questions[i].option_3, questions[i].option_4,
	//    questions[i].right_answer, questions[i].date


	/* 대략적인 구조

	func 문제 풀기()
	func 화면 출력()


	 func 문제 풀기()
	 {

		문제 선정;

		func 화면 출력(문제);

		사용자 입력 받기;

		func 화면 출력(결과);

		사용자 입력 받으면 function 종료;

	 }

		while(프로그램 종료전까지)
		{

		문제 풀기()

		}

*/
	//print question 테스트
	printquestion(questions, 2);

	return 0;
}


/*
//
//	참고
// 
 
//Question questions[MAX_QUESTIONS];
//위 코드는 stack 메모리를 너무 많이 사용하기 때문에 본 코드에서는 동적할당으로 바꿈 (stack이 아닌 heap에 저장).

//db의 모든 데이터 출력
for (int i = 0; i < num_questions; i++) {
	printf("ID: %d\nQuestion: %s\nOption 1: %s\nOption 2: %s\nOption 3: %s\nOption 4: %s\nRight answer: %s\nDate: %s\n\n",
		questions[i].id, questions[i].question, questions[i].option_1,
		questions[i].option_2, questions[i].option_3, questions[i].option_4,
		questions[i].right_answer, questions[i].date);

//

		*/