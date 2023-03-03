#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_LINE_LENGTH 1024
#define MAX_QUESTIONS 100

//데이터를 struct Question 형태로 저장
typedef struct {
    int id;
    char question[MAX_LINE_LENGTH];
    char option_1[MAX_LINE_LENGTH];
    char option_2[MAX_LINE_LENGTH];
    char option_3[MAX_LINE_LENGTH];
    char option_4[MAX_LINE_LENGTH];
    char right_answer[MAX_LINE_LENGTH];
    char date[MAX_LINE_LENGTH];
} Question;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    FILE* file;
    char line[MAX_LINE_LENGTH];
    int num_questions = 0;
    //struct Question을 저장하는 배열 questions[]
    Question questions[MAX_QUESTIONS];

    // tsv 파일을 읽어옴.
    file = fopen("db_sample.tsv", "rb");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    // fgets로 file을 읽음. 한 줄씩 읽으며 이는 line에 임시로 저장됨. 
    while (fgets(line, MAX_LINE_LENGTH, file) && num_questions < MAX_QUESTIONS) {
        // line에 저장된 데이터를 \t기준으로 나누어 struct Question에 저장.
        sscanf(line, "%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n",
            &questions[num_questions].id, questions[num_questions].question,
            questions[num_questions].option_1, questions[num_questions].option_2,
            questions[num_questions].option_3, questions[num_questions].option_4,
            questions[num_questions].right_answer, questions[num_questions].date);

        num_questions++;
    }

  
    fclose(file);

    // questions[]에 저장된 데이터를 하나씩 모두 출력
    for (int i = 0; i < num_questions; i++) {
        printf("ID: %d\nQuestion: %s\nOption 1: %s\nOption 2: %s\nOption 3: %s\nOption 4: %s\nRight answer: %s\nDate: %s\n\n",
            questions[i].id, questions[i].question, questions[i].option_1,
            questions[i].option_2, questions[i].option_3, questions[i].option_4,
            questions[i].right_answer, questions[i].date);
    }

    return 0;
}
