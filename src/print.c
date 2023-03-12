#include "globals.h"

#define MAX_LINE_LENGTH 1024
#define MAX_QUESTIONS 100

static int count = 1;
char options[4][MAX_LINE_LENGTH];
static int maxlen = 0;
static int count_change_row = 0;


//���� �� ���� �� ���� ����
void OptionsMaxLen()
{
	maxlen -= maxlen;	//static�� �ʱ�ȭ
	for (int j = 0; j < 4; j++)	//maxlen�� ���� ū strlen�� ����
	{
		if (maxlen < strlen(options[j]))
			maxlen = strlen(options[j]);
	}
}
//���� ���
void printquestion(ObjectiveQuestion* questions, int id)
{

	printf("%d. %s\n\n", count, questions[id].question);

	count++;
}
//����1,2 ���� ����,�ٹٲ� ����
void changerow1()
{
	int lendiff1 = 37 - (_mbslen(options[0]));
	int lendiff2 = 37 - (_mbslen(options[2]));
	if (maxlen > 40)
	{
		printf("\n");
	}
	else
	{
		if (lendiff1 > 0)
		{
			lendiff1 += 8;
			while (lendiff1 > 0)
			{
				printf("\t");
				lendiff1 -= 8;
			}
		}
		else
			printf("\t\t");
	}
}
//����3,4 ���� ����,�ٹٲ� ����
void changerow2()
{
	int lendiff1 = 37 - (_mbslen(options[0]));
	int lendiff2 = 37 - (_mbslen(options[2]));
	if (maxlen > 40)
	{
		printf("\n");
	}
	else
	{
		if (lendiff2 > 0)
		{
			lendiff2 += 8;
			while (lendiff2 > 0)
			{
				printf("\t");
				lendiff2 -= 8;
			}
		}
		else
			printf("\t\t");
	}
}
static int right_answer;
//���� ��� ���� ���濡 ���� ���� ����
char changedanswer()
{
	return right_answer + '0';
}
//���� 1,2,3,4 ��� ���� ����
void optionchange(ObjectiveQuestion* questions, int id)
{
	right_answer -= right_answer;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < sizeof(options[x]); y++)
			options[x][y] = NULL;
	}

	int nums[4] = { 0, 1, 2, 3 };
	int i, temp, rand_idx;
	for (i = 0; i < 4; i++) {
		rand_idx = rand() % 4;  // 0 ~ 3������ ������ �ε��� ����
		temp = nums[i];
		nums[i] = nums[rand_idx];
		nums[rand_idx] = temp;  // ������ �ε����� �ش��ϴ� ���� i��° ���� ��ȯ
	}
	strncpy(options[nums[0]], questions[id].option_1, strlen(questions[id].option_1));
	strncpy(options[nums[1]], questions[id].option_2, strlen(questions[id].option_2));
	strncpy(options[nums[2]], questions[id].option_3, strlen(questions[id].option_3));
	strncpy(options[nums[3]], questions[id].option_4, strlen(questions[id].option_4));
	int answer = atoi(questions[id].right_answer);
	if (answer == 1)
		right_answer = nums[0] + 1;
	else if (answer == 2)
		right_answer = nums[1] + 1;
	else if (answer == 3)
		right_answer = nums[2] + 1;
	else if (answer == 4)
		right_answer = nums[3] + 1;

}
//���� 1,2,3,4 ��¼���
void printoptions(ObjectiveQuestion* questions, int id)
{
	optionchange(questions, id);
	OptionsMaxLen();
	printf("�� %s", options[0]);
	changerow1();
	printf("�� %s\n", options[1]);
	printf("�� %s", options[2]);
	changerow2();
	printf("�� %s\n\n", options[3]);
}

int rand_id[100] = { -1 };

void id_sequence()
{
	int num = 0;
	for (int i = 0; i < 29; i++)
	{
		while (1)
		{
			int swit = 1;
			num = randnum();
			for (int j = 0; j <= i; j++)
			{
				if (rand_id[j] == num)
					swit = 0;
			}
			if (swit)
			{
				rand_id[i] = num;
				break;
			}
		}

	}
}
//������ ���� ��ȯ(29�̸�)
int randnum()
{
	srand(time(NULL) * rand());
	return rand() % 29;
}

extern repeat[];
extern faltcount;


void Percentage(int num)
{
	int correct = num - faltcount;

	printf("\n\n\n\n\t\t\t%d������ %d���� ���߾����ϴ�.\n\n\t\t\t%d��\n", num, correct, correct * 100 / num);
}

//�� �ٲ㼭 ����ϱ�(0:����, 1:�ɼ�1, 2:�ɼ�2, 3:�ɼ�3, 4:�ɼ�4)
void rowchange(ObjectiveQuestion* questions, int id, int choice)
{
	char name[1024] = { NULL };
	int widlen = 70;
	char temp1[1024] = { NULL };
	char temp2[1024] = { NULL };
	char addChar[10] = { "Q. " };
	int nextrow = 0;
	int firstcount = 1;
	//����� ���� ����
	optionchange(questions, id);

	for (int i = 0; i < 4; i++)
	{
		name[i] = addChar[i];
	}
	strcpy(name + strlen(name), questions[id].question);
	while (strlen(name) > widlen)
	{
		int lengthname = strlen(name);
		//������ ������ ���̺��� �涧 �ڸ� ��ġ ����
		if (lengthname >= widlen)
		{
			for (int i = widlen; name[i] != ' '; i++)
				nextrow = i + 1;
		}
		//�ڸ���ġ�� ������ ���̿� ���ų� �涧 ���� �״�� ����ϱ� ���� �ݺ��� ����
		if (nextrow >= lengthname)
			break;
		int dellen = sizeof(temp1);
		for (int j = 0; j < dellen; j++)	//temp1�� ���� �����
			temp1[j] = NULL;
		strncpy(temp1, name, nextrow);		//temp1�� name ���� �����ϱ�
		int k = 0;
		if (name[nextrow] == ' ')
			nextrow++;
		//temp2���ٰ� temp1�� ������ ������� ���� �������� ���� �����ϱ�
		for (int j = nextrow; name[j] != NULL; j++)
		{
			temp2[k] = name[j];
			k++;
		}
		for (int j = 0; j < lengthname; j++)	//name�� �ִ� ������ �����
			name[j] = NULL;
		strcpy(name, temp2);					//temp2�� ������ name���� �ű��
		printf("\t%s\n", temp1);					//temp1�� ���� ���
		dellen = sizeof(temp2);
		for (int j = 0; j < dellen; j++)		//������ ���� �����͸� ���� temp2�� ���� �����
			temp2[j] = NULL;
		nextrow = widlen;
		lengthname = 0;
		dellen = 0;
	}
	printf("\t%s\n", name);
	puts("");
}
//����(0),����(1),���(2),���(3),�Ķ�(4),����(5),û��(6),����ȸ��(7)
char textcolor[8][20] = {
	{"\033[0;30m"},{"\033[0;31m"},{"\033[0;32m"},{"\033[0;33m"},{"\033[0;34m"},{"\033[0;35m"},
	{"\033[0;36m"},{"\033[0;37m"}
};
char endcolor[20] = { "\033[0m" };
//����(0),����(1),���(2),���(3),�Ķ�(4),����(5),û��(6),����ȸ��(7)
char backcolor[8][20] = {
	{"\033[0;40m"},{"\033[0;41m"},{"\033[0;42m"},{"\033[0;43m"},{"\033[0;44m"},{"\033[0;45m"},
	{"\033[0;46m"},{"\033[0;47m"}
};
//[0] : �Է��� ��ȣ, [1] : ���� ��ȣ, [2] : 0==�� ��ȯX, 1==�� ��ȯO
int changecolor[3] = { 0,0,0 };

//���ڿ� ���� ���缭 �ٹٲٱ�
void print_change_row(char* sentence)
{
	count_change_row = 2;
	char print_sentence[1024] = { NULL };
	int widlen = 50;
	char temp1[1024] = { NULL };
	char temp2[1024] = { NULL };
	int firstcount = 1;
	strcpy(print_sentence, sentence);
	while (strlen(print_sentence) > widlen)
	{
		int nextrow = widlen;
		int min_nextrow = widlen;
		int lengthname = strlen(print_sentence);
		//������ ������ ���̺��� �涧 �ڸ� ��ġ ����
		if (lengthname >= widlen)
		{
			for (int i = widlen; print_sentence[i] != ' '; i++)
				nextrow = i+1;
			for (int i = widlen; print_sentence[i] != ' '; i--)
				min_nextrow = i-1;
		}
		//�ڸ���ġ�� ������ ���̿� ���ų� �涧 ���� �״�� ����ϱ� ���� �ݺ��� ����
		if (nextrow - widlen > widlen - min_nextrow)
			nextrow = min_nextrow;
		if (nextrow >= lengthname)
			break;
		int dellen = sizeof(temp1);
		for (int j = 0; j < dellen; j++)	//temp1�� ���� �����
			temp1[j] = NULL;
		strncpy(temp1, print_sentence, nextrow);		//temp1�� name ���� �����ϱ�
		int k = 0;
		if (print_sentence[nextrow] == ' ')
			nextrow++;
		//temp2���ٰ� temp1�� ������ ������� ���� �������� ���� �����ϱ�
		for (int j = nextrow; print_sentence[j] != NULL; j++)
		{
			temp2[k] = print_sentence[j];
			k++;
		}
		for (int j = 0; j < lengthname; j++)	//name�� �ִ� ������ �����
			print_sentence[j] = NULL;
		strcpy(print_sentence, temp2);					//temp2�� ������ name���� �ű��

		if (firstcount)
			printf("\t%s\n", temp1);					//temp1�� ���� ���
		else
			printf("\t   %s\n", temp1);

		dellen = sizeof(temp2);
		for (int j = 0; j < dellen; j++)		//������ ���� �����͸� ���� temp2�� ���� �����
			temp2[j] = NULL;
		if (firstcount)
		{
			widlen -= 6;
			firstcount = 0;
		}
		nextrow = widlen;
		lengthname = 0;
		dellen = 0;
		count_change_row++;
	}
	if (firstcount)
		printf("\t%s\n", print_sentence);
	else
		printf("\t   %s\n", print_sentence);
}

//���� �ڵ� �ٹٲ��ؼ� ���
void questionrowchange(ObjectiveQuestion* questions, int id)
{
	printf("\n\n");
	if (changecolor[2] != 1)
		optionchange(questions, id);
	char name[1024] = { NULL };
	char addChar[10] = { "Q. " };

	//����� ���� ����
	for (int i = 0; i < 4; i++)
	{
		name[i] = addChar[i];
	}
	strcpy(name + strlen(name), questions[id].question);
	print_change_row(&name);
	printf("\n");
}

//�Է°��� ���� ��� �� ����
int select_color(int choice)
{	//240		143		176		225
	int mycolor = color_mode_preset[color_mode%4];
	//�� ����
	int origin_color=mycolor;
	int add_color[2];
	if (color_mode%4 == 1)
	{
		add_color[0] = 256-3;
		add_color[1] = 256-5;
	}
	else
	{
		add_color[0] = 12;
		add_color[1] = 2;
	}
	int option_color = color_mode%4;
	if (changecolor[2] == 1) {
		if (changecolor[0] != changecolor[1] && changecolor[0] == choice) {
			origin_color += add_color[0];
			mycolor = origin_color % 256;
		}
		else if (changecolor[1] == choice) {
			origin_color += add_color[1];
			mycolor = origin_color % 256;
		}
	}
	else {
		mycolor = color_mode_preset[color_mode%4];
	}
	return mycolor;
}

//���� �ڵ� �ٹٲ��ؼ� ���
void optionrowchange(ObjectiveQuestion* questions, int id, int choice)
{
	char name[1024] = { NULL };
	char addChar[4][10] = { {"�� "},{"�� "},{"�� "},{"�� "} };
	int mycolor = select_color(choice);
	SetConsoleTextAttribute(console, mycolor);

	//����� ���� ����
	for (int i = 0; i < 4; i++)
	{
		name[i] = addChar[choice - 1][i];
	}
	strcpy(name + strlen(name), options[choice - 1]);
	print_change_row(&name);
	SetConsoleTextAttribute(console, 240);
	puts("");
}

void print_row_change(ObjectiveQuestion* questions, int id, int choice)
{

	char name[1024] = { NULL };
	char addChar[5][10] = { {"Q. "}, {"�� "},{"�� "},{"�� "},{"�� "} };
	int mycolor = select_color(choice);
	SetConsoleTextAttribute(console, mycolor);

	//����� ���� ����
	for (int i = 0; i < 5; i++)
	{
		name[i] = addChar[choice][i];
	}
	if (choice == 0)
		strcpy(name + strlen(name), questions[id].question);
	else
		strcpy(name + strlen(name), options[choice - 1]);
	print_change_row(&name);
	SetConsoleTextAttribute(console, color_mode_preset[color_mode%4]);
	puts("");
}

void option_select(ObjectiveQuestion* questions, int id)
{
	cursorPosition.X = 2;
	cursorPosition.Y = 4;
	char icon[3][10] = { {"��"},{"O"},{"X"}};
	int num;
	SetConsoleCursorPosition(console, cursorPosition);
	for (int i = 0; i < 4; i++) {
		if (i == 0)
		{
			print_row_change(questions, id, 0);
			cursorPosition.Y += count_change_row;
		}
		SetConsoleCursorPosition(console, cursorPosition);
		if (changecolor[2] == 1)
		{
			if (changecolor[0] == changecolor[1]&&changecolor[0] == i + 1) {
				num = 1;
				current_menu_item = changecolor[0]-1;
			}
			else if (changecolor[0] != changecolor[1] && changecolor[0] == i+1){
				num = 2;
				current_menu_item = changecolor[0]-1;
			}
			else if (changecolor[1] == i+1){
				num = 1;
				current_menu_item = changecolor[1]-1;
			}
		}
		else num = 0;
		printf("%s ", ((current_menu_item) == i) ? icon[num] : " ");
		print_row_change(questions, id, i + 1);
		cursorPosition.Y += count_change_row;
	}
}

void select_by_arrow(ObjectiveQuestion* questions, int id)
{
	int num;
	while (1) {
		option_select(questions, id);
		printf("\n\n������ �����ϼ���(1~4): \n");
		key_pressed = getch();
		if (key_pressed == 'w' || key_pressed == 'W' || key_pressed == 72) {
			current_menu_item = (current_menu_item + 3) % 4;
		}
		else if (key_pressed == 's' || key_pressed == 'S' || key_pressed == 80) {
			current_menu_item = (current_menu_item + 1) % 4;
		}
		else if (key_pressed == '\r') {
			ClearScreen();
			break;
		}
		else if (key_pressed >= 1 && key_pressed <= 4) {
			current_menu_item = key_pressed - 1;
			ClearScreen();
			break;
		}
	}
	changecolor[0] += current_menu_item % 4 + 1;
	changecolor[1] += changedanswer() - '0';
	changecolor[2] += 1;
	current_menu_item = changedanswer() - '0' - 1;
	option_select(questions, id);
	num = check_my_answer();
	changecolor[0] = 0;
	changecolor[1] = 0;
	changecolor[2] = 0;
	return num;

}