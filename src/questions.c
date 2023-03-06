#include "questions.h"

void read_questions(Question* questions, int* num_questions) {
    FILE* file;
    char line[MAX_LINE_LENGTH];
    *num_questions = 0;

    file = fopen("db_sample.tsv", "rb");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    while (fgets(line, MAX_LINE_LENGTH, file) && *num_questions < MAX_QUESTIONS) {
        sscanf(line, "%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n",
            &questions[*num_questions].id, questions[*num_questions].question,
            questions[*num_questions].option_1, questions[*num_questions].option_2,
            questions[*num_questions].option_3, questions[*num_questions].option_4,
            questions[*num_questions].right_answer, questions[*num_questions].date);

        (*num_questions)++;
    }

    fclose(file);
}

static count = 0;                       //이 소스 파일에서만 사용할 count변수
//틀린 문제의 INDEX 저장
int repeat[MAX_QUESTIONS] = { -1 };
int faltcount = 0;

void faltquestions(int id)
{
    repeat[count] = id;
    faltcount++;
    count++;
}

// 입력값이 1~4 사이의 문자인지 체크하는 함수
int is_valid_input(char input) {

    return input == '1' || input == '2' || input == '3' || input == '4';
}

int CheckAnswer(int id)
{
    char input;
    //사용자 입력 받기
    printf("답을 입력하세요(1~4): \n");
    scanf(" %c", &input);


    // 입력값이 유효한지 체크
    while (!is_valid_input(input)) {
        printf("잘못된 값이 입력되었습니다. 다시 입력해주세요(1~4): \n");
        scanf(" %c", &input);
    }

    // 정답 체크
    if (input == changedanswer()) {
        printf("정답입니다!\n\n");
        return 0;
    }
    else {
        printf("오답입니다. \n정답은 %c입니다.\n\n", changedanswer());
        return 1;

    }
}