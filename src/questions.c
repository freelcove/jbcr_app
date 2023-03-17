#include "globals.h"

void readObjectiveQuestions(ObjectiveQuestion *questions)
{
	FILE *file;
	char line[MAX_LINE_LENGTH];

	file = fopen("db/db_objective.tsv", "rb");
	if (file == NULL)
	{
		printf("Failed to open file.\n");
		return;
	}

	while (fgets(line, MAX_LINE_LENGTH, file) && num_objective_questions < MAX_QUESTIONS)
	{
		sscanf(line, "%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n",
			   &questions[num_objective_questions].id, questions[num_objective_questions].question,
			   questions[num_objective_questions].option_1, questions[num_objective_questions].option_2,
			   questions[num_objective_questions].option_3, questions[num_objective_questions].option_4,
			   questions[num_objective_questions].right_answer, questions[num_objective_questions].date);

		(num_objective_questions)++;
	}

	fclose(file);
}

void readSubjectiveQuestions(SubjectiveQuestion *questions)
{
	FILE *file;
	char line[MAX_LINE_LENGTH];

	file = fopen("db/db_subjective.tsv", "rb");
	if (file == NULL)
	{
		printf("Failed to open file.\n");
		return;
	}

	while (fgets(line, MAX_LINE_LENGTH, file) && num_subjective_questions < MAX_QUESTIONS)
	{
		sscanf(line, "%d\t%[^\t]\t%[^\n]\n",
			   &questions[num_subjective_questions].id, questions[num_subjective_questions].name,
			   questions[num_subjective_questions].definition);

		num_subjective_questions++;
	}

	fclose(file);
}

void readHistory(struct Queue *queue_objective, struct Queue *queue_subjective)
{
	// ù° �� ������ ���� ť �迭
	// ��° �� �ְ��� ���� ť �迭
	FILE *file;

	file = fopen("db/db_history.tsv", "r");
	if (file == NULL)
	{
		printf("Failed to open file.\n");
		return;
	}
	int value1, value2;
	char line[2000];
	int i = 0;
	while (fgets(line, sizeof(line), file) != NULL)
	{
		char *token = strtok(line, "\t");
		while (token != NULL)
		{
			if (i == 0)
			{
				enqueue(queue_objective, atoi(token));
			}
			else if (i == 1)
			{
				enqueue(queue_subjective, atoi(token));
			}
			token = strtok(NULL, "\t");
		}
		i++;
	}
	fclose(file);
}

void writeHistory(struct Queue *queue_objective, struct Queue *queue_subjective)
{
	FILE *file;
	file = fopen("db/db_history.tsv", "w");
	if (file == NULL)
	{
		printf("Failed to open file.\n");
		return;
	}

	struct Node *curr_obj = queue_objective->front;
	while (curr_obj != NULL)
	{
		fprintf(file, "%d", curr_obj->key);
		if (curr_obj->next != NULL)
		{
			fprintf(file, "\t");
		}
		curr_obj = curr_obj->next;
	}
	fprintf(file, "\n");

	struct Node *curr_subj = queue_subjective->front;
	while (curr_subj != NULL)
	{
		fprintf(file, "%d", curr_subj->key);
		if (curr_subj->next != NULL)
		{
			fprintf(file, "\t");
		}
		curr_subj = curr_subj->next;
	}

	fclose(file);
}

static count = 0; // �� �ҽ� ���Ͽ����� ����� count����
// Ʋ�� ������ INDEX ����
extern int repeat[MAX_QUESTIONS] = {-1};

void faltquestions(int id)
{
	repeat[count] = id;
	faltcount++;
	count++;
}

// �Է°��� 1~4 ������ �������� üũ�ϴ� �Լ�
int is_valid_input(char input)
{

	return input == '1' || input == '2' || input == '3' || input == '4';
}
extern int changecolor[3];
int CheckAnswer(ObjectiveQuestion *questions, int id, HANDLE console)
{
	int result;
	char input;
	printf("\n\n");
	// ����� �Է� �ޱ�
	printf("���� �Է��ϼ���(1~4): \n");
	scanf(" %c", &input);
	// �Է°��� ��ȿ���� üũ
	while (!is_valid_input(input))
	{
		printf("�߸��� ���� �ԷµǾ����ϴ�. �ٽ� �Է����ּ���(1~4): \n");
		scanf(" %c", &input);
	}
	changecolor[0] += input - '0';
	changecolor[1] += changedanswer() - '0';
	changecolor[2] += 1;
	// ���� üũ
	clearScreen();

	// ���� ���� ��� �߰��ʿ�

	printf("\n\n");
	if (input == changedanswer())
	{
		printf("�����Դϴ�!\n\n");
		result = 1;
	}
	else
	{
		faltquestions(id);
		printf("�����Դϴ�. \n������ %c�Դϴ�.\n\n", changedanswer());
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
		current_streak_objective++;
		if (best_streak_objective < current_streak_objective)
			best_streak_objective = current_streak_objective;
		printf("\n\t     %d���� �����Դϴ�!\n\t     ���� �������� ���� ��: %d\tBEST : %d\n\n", changecolor[0], current_streak_objective, best_streak_objective);
		cursorPosition.Y += 4;
		result = 1;
	}
	else
	{
		current_streak_objective = 0;
		faltquestions(id);
		printf("\n\t     %d���� �����Դϴ�. \n\t     ������ %c���Դϴ�.\tBEST : %d\n\n", changecolor[0], changedanswer(), best_streak_objective);
		cursorPosition.Y += 4;
		result = 0;
	}
	return result;
}

// Fisher-Yates shuffle algorithm�� ���.
void enqueueRandom(struct Queue *queue, int size)
{
	srand(time(NULL));

	int *indices = (int *)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
	{
		indices[i] = i;
	}
	for (int i = size - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		int temp = indices[i];
		indices[i] = indices[j];
		indices[j] = temp;
	}

	for (int i = 0; i < size; i++)
	{
		enqueue(queue, indices[i]);
	}

	free(indices);
}