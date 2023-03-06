
#include "questions.h"
#include "interface.h"
#include "print.h"


int is_valid_input(char input) {
	// �Է°��� a~d ������ �������� üũ�ϴ� �Լ�
	//a~d -> 1~4�� ����
	return input == '1' || input == '2' || input == '3' || input == '4';
}

int main()
{
	//�ܼ� â �ʱ�ȭ. (ȭ�� ũ��, ���� ��, Ŀ�� ������ �� ����)
	InitScreen();

	//db�� ������ questions[] ����
	Question* questions = malloc(sizeof(Question) * MAX_QUESTIONS);

	int num_questions;
	
	// ����ڰ� �Է��� ���� ���� ����
	int num_to_solve;

	//tsv ���Ͽ��� ������ �ҷ��ͼ� questions[] �迭�� ����
	read_questions(questions, &num_questions);

	// ����ڷκ��� ���� ���� �Է� �ޱ�
	do {
		printf("Ǯ ���� �� �Է�: ");
		scanf("%d", &num_to_solve);
	} while (num_to_solve <= 0 || num_to_solve > num_questions);


	int i = 0;
	char input;

	// ���� ���� �� ����� �Է� �ޱ�
	while (i < num_to_solve) {
		//print question �׽�Ʈ
		printquestion(questions, i);
		printoptions(questions, i);

		//����� �Է� �ޱ�
		printf("���� �Է��ϼ���(1~4): \n");
		scanf(" %c", &input);

		// �Է°��� ��ȿ���� üũ
		while (!is_valid_input(input)) {
			printf("�߸��� ���� �ԷµǾ����ϴ�. �ٽ� �Է����ּ���(1~4): \n");
			scanf(" %c", &input);
		}

		// ���� üũ
		if (input == questions[i].right_answer[0]) {
			printf("�����Դϴ�!\n\n");
		}
		else {
			printf("�����Դϴ�. \n������ %s�Դϴ�.\n\n", questions[i].right_answer);
		}

		// ���� ������ �Ѿ��
		i++;
	}

	free(questions); // �����Ҵ��� �޸� ����


	// �Ʒ� �ڵ�� questions[] db�� ���� ����

	//questions[i].id, questions[i].question, questions[i].option_1,
	//questions[i].option_2, questions[i].option_3, questions[i].option_4,
	//    questions[i].right_answer, questions[i].date


	return 0;
}