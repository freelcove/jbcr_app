#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "questions.h"

int main() {

    //콘솔 인코딩 utf_8로 설정
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    //콘솔 창 크기 바꾸기
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = { 0, 0, 79, 49 };
    SetConsoleWindowInfo(console, TRUE, &windowSize);

    //db를 저장할 questions[] 선언
    Question questions[MAX_QUESTIONS];
    int num_questions;

    read_questions(questions, &num_questions);

    //여기까지 db에서 데이터 불러와서 questions[] 배열에 저장하기 완료
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

        while(프로그램 종료전까지){

        문제 풀기()

        }
}

*/

    return 0;
}
