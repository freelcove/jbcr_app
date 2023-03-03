#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "questions.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Question questions[MAX_QUESTIONS];
    int num_questions;

    read_questions(questions, &num_questions);

    //여기까지 db에서 데이터 불러와서 questions[] 배열에 저장하기 완료
    //
    // 아래 코드로 questions[] db에 접근 가능
    // 
    //questions[i].id, questions[i].question, questions[i].option_1,
    //questions[i].option_2, questions[i].option_3, questions[i].option_4,
    //    questions[i].right_answer, questions[i].date


    //출력 기능



    // 문제 푸는 기능




    return 0;
}
