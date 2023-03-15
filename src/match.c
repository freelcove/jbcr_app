#include "globals.h"

int match(char* user_answer, char* subjective_questions) {
    int i = 0;
    while (user_answer[i] != '\0' && subjective_questions[i] != '\0') {
        if (user_answer[i] != subjective_questions[i]) {
            return 1;
        }
        i++;
    }
    if (user_answer[i] != '\0' || subjective_questions[i] != '\0') {
        return 1;
    }

    return 0;
}

int check_subjective_correction(SubjectiveQuestion* subjective_questions, int id,struct Queue* queue_subjective)
{

	char subjective_answer[MAX_LINE_LENGTH] = { 0 };
	int i = 0;
	int subjective_len = 0;
	int check_subjective_correct = 1;
	while (user_answer[i] != NULL)
	{
		if (user_answer[i] >= 'a' && user_answer[i] <= 'z')
			user_answer[i] += 'A' - 'a';
		i++;
	}
	i = 0;
	while (subjective_questions[id].name[i] != NULL)
	{
		if (subjective_questions[id].name[i] >= 'a' && subjective_questions[id].name[i] <= 'z')
			subjective_questions[id].name[i] += 'A' - 'a';
		i++;
	}
	i = 0;
	while (1)
	{
		int len = strlen(subjective_answer - 1);
		while (i != len)
		{
			subjective_answer[i] = NULL;
			i++;
		}
		i = 0;
		while (subjective_questions[id].name[subjective_len] != ',' && subjective_questions[id].name[subjective_len] != NULL)
		{
			subjective_answer[i] = subjective_questions[id].name[subjective_len];
			subjective_len++;
			i++;
		}
		i = 0;
		subjective_len += 1;
		if (user_answer[i] != subjective_answer[i] && subjective_answer[i] != NULL)
		{
			if (subjective_questions[id].name[subjective_len - 1] == NULL)
				break;
			continue;
		}
		int num = strcmp(user_answer, subjective_answer);
		if (num == 0)
		{ // match 함수 활용
			printf("\n\t     정답입니다.\n");
			enqueue(queue_subjective, queue_subjective->front->key);
			dequeue(queue_subjective);
			check_subjective_correct = 0;
			return 0;
		}
	}
	return check_subjective_correct;
}
