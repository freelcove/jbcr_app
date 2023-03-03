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
