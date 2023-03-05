#include <locale.h>
#include "questions.h"
#include "interface.h"
#include "print.h"

int is_valid_input(char input) {
// 입력값이 a~d 사이의 문자인지 체크하는 함수
return input == 'a' || input == 'b' || input == 'c' || input == 'd';
}

int main()
{
// 로케일 설정
setlocale(LC_ALL, "");
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
	printf("풀 문제 개수를 입력하세요: ");
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
	printf("정답을 입력하세요 (a~d): ");
	scanf(" %c", &input);

	// 입력값이 유효한지 체크
	while (!is_valid_input(input)) {
		printf("잘못된 입력입니다. 정답을 입력하세요 (a~d): ");
		scanf(" %c", &input);
	}

	// 정답 체크
	if (input == questions[i].right_answer[0]) {
		printf("정답입니다!\n\n");
	}
	else {
		printf("오답입니다. 정답은 %s입니다.\n\n", questions[i].right_answer);
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