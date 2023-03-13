#include "globals.h"

void readObjectiveQuestions(ObjectiveQuestion* questions) {
	FILE* file;
	char line[MAX_LINE_LENGTH];

	file = fopen("db/db_objective.tsv", "rb");
	if (file == NULL) {
		printf("Failed to open file.\n");
		return;
	}

	while (fgets(line, MAX_LINE_LENGTH, file) && num_objective_questions < MAX_QUESTIONS) {
		sscanf(line, "%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n",
			&questions[num_objective_questions].id, questions[num_objective_questions].question,
			questions[num_objective_questions].option_1, questions[num_objective_questions].option_2,
			questions[num_objective_questions].option_3, questions[num_objective_questions].option_4,
			questions[num_objective_questions].right_answer, questions[num_objective_questions].date);

		(num_objective_questions)++;
	}

	fclose(file);
}

void readSubjectiveQuestions(SubjectiveQuestion* questions) {
	FILE* file;
	char line[MAX_LINE_LENGTH];

	file = fopen("db/db_subjective.tsv", "rb");
	if (file == NULL) {
		printf("Failed to open file.\n");
		return;
	}

	while (fgets(line, MAX_LINE_LENGTH, file) && num_subjective_questions < MAX_QUESTIONS) {
		sscanf(line, "%d\t%[^\t]\t%[^\n]\n",
			&questions[num_subjective_questions].id, questions[num_subjective_questions].name,
			questions[num_subjective_questions].definition);

		num_subjective_questions++;
	}

	fclose(file);
}

void readHistory(struct Queue* queue_objective, struct Queue* queue_subjective) {
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
		while (token != NULL) {
			if (i == 0) {
				enqueue(queue_objective, atoi(token));
			}
			else if (i == 1) {
				enqueue(queue_subjective, atoi(token));
			}
			token = strtok(NULL, "\t");
		}
		i++;
	}
	fclose(file);
}


void writeHistory(struct Queue* queue_objective, struct Queue* queue_subjective) {
	FILE* file;
	file = fopen("db/db_history.tsv", "w");
	if (file == NULL) {
		printf("Failed to open file.\n");
		return;
	}

	struct Node* curr_obj = queue_objective->front;
	while (curr_obj != NULL) {
		fprintf(file, "%d", curr_obj->key);
		if (curr_obj->next != NULL) {
			fprintf(file, "\t");
		}
		curr_obj = curr_obj->next;
	}
	fprintf(file, "\n");

	struct Node* curr_subj = queue_subjective->front;
	while (curr_subj != NULL) {
		fprintf(file, "%d", curr_subj->key);
		if (curr_subj->next != NULL) {
			fprintf(file, "\t");
		}
		curr_subj = curr_subj->next;
	}

	fclose(file);
}



static count = 0;     //이 소스 파일에서만 사용할 count변수
//틀린 문제의 INDEX 저장
extern int repeat[MAX_QUESTIONS] = { -1 };


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
extern int changecolor[3];
int CheckAnswer(ObjectiveQuestion* questions, int id, HANDLE console)
{
	int result;
	char input;
	printf("\n\n");
	//사용자 입력 받기
	printf("답을 입력하세요(1~4): \n");
	scanf(" %c", &input);
	// 입력값이 유효한지 체크
	while (!is_valid_input(input)) {
		printf("잘못된 값이 입력되었습니다. 다시 입력해주세요(1~4): \n");
		scanf(" %c", &input);
	}
	changecolor[0] += input - '0';
	changecolor[1] += changedanswer() - '0';
	changecolor[2] += 1;
	// 정답 체크
	clearScreen();

			//문제 보기 출력 추가필요

	printf("\n\n");
	if (input == changedanswer()) {
		printf("정답입니다!\n\n");
		result = 1;
	}
	else {
		faltquestions(id);
		printf("오답입니다. \n정답은 %c입니다.\n\n", changedanswer());
		result = 0;
	}
	changecolor[0] -= input - '0';
	changecolor[1] -= changedanswer() - '0';
	changecolor[2] -= 1;

	return result;
}

int check_my_answer(id)
{
	int result;
	if (changecolor[0] == changedanswer() - '0')
	{
		current_streak++;
		if (best_streak < current_streak)
			best_streak = current_streak;
		printf("\n\t     %d번은 정답입니다!\n\t     현재까지 맞춘 문제수 : %d\tBEST : %d\n\n",changecolor[0],current_streak,best_streak);
		cursorPosition.Y += 4;
		result = 1;
	}
	else {
		current_streak = 0;
		faltquestions(id);
		printf("\n\t     %d번은 오답입니다. \n\t     정답은 %c번입니다.\tBEST : %d\n\n", changecolor[0],changedanswer(),best_streak);
		cursorPosition.Y += 4;
		result = 0;
	}
	return result;
}