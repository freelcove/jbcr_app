#include "globals.h"
#include "questions.h"

void read_objective_questions(ObjectiveQuestion* questions, int* num_objective_questions) {
	FILE* file;
	char line[MAX_LINE_LENGTH];
	*num_objective_questions = 0;

	file = fopen("db/db_objective.tsv", "rb");
	if (file == NULL) {
		printf("Failed to open file.\n");
		return;
	}

	while (fgets(line, MAX_LINE_LENGTH, file) && *num_objective_questions < MAX_QUESTIONS) {
		sscanf(line, "%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n",
			&questions[*num_objective_questions].id, questions[*num_objective_questions].question,
			questions[*num_objective_questions].option_1, questions[*num_objective_questions].option_2,
			questions[*num_objective_questions].option_3, questions[*num_objective_questions].option_4,
			questions[*num_objective_questions].right_answer, questions[*num_objective_questions].date);

		(*num_objective_questions)++;
	}

	fclose(file);
}

void read_subjective_questions(SubjectiveQuestion* questions, int* num_subjective_questions) {
	FILE* file;
	char line[MAX_LINE_LENGTH];
	*num_subjective_questions = 0;

	file = fopen("db/db_subjective.tsv", "rb");
	if (file == NULL) {
		printf("Failed to open file.\n");
		return;
	}

	while (fgets(line, MAX_LINE_LENGTH, file) && *num_subjective_questions < MAX_QUESTIONS) {
		sscanf(line, "%d\t%[^\t]\t%[^\n]\n",
			&questions[*num_subjective_questions].id, questions[*num_subjective_questions].name,
			questions[*num_subjective_questions].definition);

		(*num_subjective_questions)++;
	}

	fclose(file);
}

void read_history(int* objective_history, int* subjective_history) {
	// 첫째 행 객관식 문제 큐 배열
	// 둘째 행 주관식 문제 큐 배열
	FILE* file;

	file = fopen("db/db_history.tsv", "r");
	if (file == NULL) {
		printf("Failed to open file.\n");
		return;
	}
	int value1, value2;
	char line[2000];
	int i = 0;
	while (fgets(line, sizeof(line), file) != NULL) {
		char* token = strtok(line, "\t");
		int j = 0;
		while (token != NULL) {
			if (i == 0) {
				objective_history[j] = atoi(token);
			}
			else if (i == 1) {
				subjective_history[j] = atoi(token);
			}
			token = strtok(NULL, "\t");
			j++;
		}
		i++;
	}
	fclose(file);
}

void write_history(int* objective_history, int* subjective_history, int* num_objective_questions, int* num_subjective_questions) {
	FILE* file;
	file = fopen("db/db_history.tsv", "w");
	if (file == NULL) {
		printf("Failed to open file.\n");
		return;
	}

	for (int i = 0; i < *num_objective_questions; i++) {
		fprintf(file, "%d\t", objective_history[i]);
	}
	fprintf(file, "\n");

	for (int i = 0; i < *num_subjective_questions; i++) {
		fprintf(file, "%d\t", subjective_history[i]);
	}

	fclose(file);
}

void reset_history(int* objective_history, int* subjective_history) {
	FILE* file;
	file = fopen("db/db_history.tsv", "w");
	if (file == NULL) {
		printf("Failed to open file.\n");
		return;
	}
	fprintf(file, "%d", -1);
	fprintf(file, "\n");
	fprintf(file, "%d", -1);
	fclose(file);
}




static count = 0;     //이 소스 파일에서만 사용할 count변수
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