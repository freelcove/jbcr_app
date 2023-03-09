#include "globals.h"

#define MAX_LINE_LENGTH 1024
#define MAX_QUESTIONS 100

static int count = 1;
char options[4][MAX_LINE_LENGTH];
static int maxlen = 0;


//보기 중 가장 긴 길이 저장
void OptionsMaxLen()
{
	maxlen -= maxlen;	//static값 초기화
	for (int j = 0; j < 4; j++)	//maxlen에 가장 큰 strlen값 저장
	{
		if (maxlen < strlen(options[j]))
			maxlen = strlen(options[j]);
	}
}
//문제 출력
void printquestion(ObjectiveQuestion* questions, int id)
{

	printf("%d. %s\n\n", count, questions[id].question);

	count++;
}
//보기1,2 사이 간격,줄바꿈 설정
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
//보기3,4 사이 간격,줄바꿈 설정
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
//보기 출력 순서 변경에 따른 정답 변경
char changedanswer()
{
	return right_answer + '0';
}
//보기 1,2,3,4 출력 순서 섞기
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
		rand_idx = rand() % 4;  // 0 ~ 3까지의 랜덤한 인덱스 생성
		temp = nums[i];
		nums[i] = nums[rand_idx];
		nums[rand_idx] = temp;  // 랜덤한 인덱스에 해당하는 값과 i번째 값을 교환
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
//보기 1,2,3,4 출력설정
void printoptions(ObjectiveQuestion* questions, int id)
{
	optionchange(questions, id);
	OptionsMaxLen();
	printf("① %s", options[0]);
	changerow1();
	printf("② %s\n", options[1]);
	printf("③ %s", options[2]);
	changerow2();
	printf("④ %s\n\n", options[3]);
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
//랜덤의 숫자 반환(29미만)
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

	printf("\n\n\n\n\t\t\t%d문제중 %d문제 맞추었습니다.\n\n\t\t\t%d점\n", num, correct, correct * 100 / num);
}

//줄 바꿔서 출력하기(0:문제, 1:옵션1, 2:옵션2, 3:옵션3, 4:옵션4)
void rowchange(ObjectiveQuestion*questions,int id,int choice)
{
	char name[1024] = { NULL };
	int widlen = 70;
	char temp1[1024] = { NULL };
	char temp2[1024] = { NULL };
	char addChar[10] = {"Q. "};
	int nextrow=0;
	int firstcount = 1;
	//출력할 내용 선택
	optionchange(questions, id);
	printf("\n\n");
	for (int i = 0; i < 4; i++)
	{
		name[i] = addChar[i];
	}
	strcpy(name + strlen(name), questions[id].question);
	while (strlen(name) > widlen)
	{
		int lengthname = strlen(name);
		//내용이 지정한 길이보다 길때 자를 위치 지정
		if (lengthname >= widlen)
		{
			for (int i = widlen; name[i] != ' '; i++)
				nextrow = i + 1;
		}
		//자를위치가 내용의 길이와 같거나 길때 내용 그대로 출력하기 위해 반복문 종료
		if (nextrow >= lengthname)
			break;
		int dellen = sizeof(temp1);
		for (int j = 0; j < dellen; j++)	//temp1의 내용 지우기
			temp1[j] = NULL;
		strncpy(temp1, name, nextrow);		//temp1에 name 내용 복사하기
		int k = 0;
		if (name[nextrow] == ' ')
			nextrow++;
		//temp2에다가 temp1의 내용을 집어놓고 남은 나머지의 내용 복사하기
		for (int j = nextrow; name[j] != NULL; j++)
		{
			temp2[k] = name[j];
			k++;
		}
		for (int j = 0; j < lengthname; j++)	//name에 있는 데이터 지우기
			name[j] = NULL;
		strcpy(name, temp2);					//temp2의 내용을 name으로 옮기기
		printf("\t%s\n", temp1);					//temp1의 내용 출력
		dellen = sizeof(temp2);
		for (int j = 0; j < dellen; j++)		//다음에 받을 데이터를 위해 temp2의 내용 지우기
			temp2[j] = NULL;
		nextrow = widlen;
		lengthname = 0;
		dellen = 0;
	}
	printf("\t%s\n", name);
	puts("");
}
//검정(0),빨강(1),녹색(2),노랑(3),파랑(4),자주(5),청록(6),밝은회색(7)
char textcolor[8][20] = {
	{"\033[0;30m"},{"\033[0;31m"},{"\033[0;32m"},{"\033[0;33m"},{"\033[0;34m"},{"\033[0;35m"},
	{"\033[0;36m"},{"\033[0;37m"} 
};
char endcolor[20] = { "\033[0m"};
//검정(0),빨강(1),녹색(2),노랑(3),파랑(4),자주(5),청록(6),밝은회색(7)
char backcolor[8][20] = {
	{"\033[0;40m"},{"\033[0;41m"},{"\033[0;42m"},{"\033[0;43m"},{"\033[0;44m"},{"\033[0;45m"},
	{"\033[0;46m"},{"\033[0;47m"}
};
//[0] : 입력한 번호, [1] : 정답 번호, [2] : 0==색 변환X, 1==색 변환O
int changecolor[3] = { 0,0,0 };

//문자열 길이 맞춰서 줄바꾸기
void print_change_row(char* sentence)
{
	char print_sentence[1024] = { NULL };
	int widlen = 70;
	char temp1[1024] = { NULL };
	char temp2[1024] = { NULL };
	int firstcount = 1;
	strcpy(print_sentence, sentence);
	while (strlen(print_sentence) > widlen)
	{
		int nextrow = widlen;
		int lengthname = strlen(print_sentence);
		//내용이 지정한 길이보다 길때 자를 위치 지정
		if (lengthname >= widlen)
		{
			for (int i = widlen; print_sentence[i] != ' '; i++)
				nextrow = i + 1;
		}
		//자를위치가 내용의 길이와 같거나 길때 내용 그대로 출력하기 위해 반복문 종료
		if (nextrow >= lengthname)
			break;
		int dellen = sizeof(temp1);
		for (int j = 0; j < dellen; j++)	//temp1의 내용 지우기
			temp1[j] = NULL;
		strncpy(temp1, print_sentence, nextrow);		//temp1에 name 내용 복사하기
		int k = 0;
		if (print_sentence[nextrow] == ' ')
			nextrow++;
		//temp2에다가 temp1의 내용을 집어놓고 남은 나머지의 내용 복사하기
		for (int j = nextrow; print_sentence[j] != NULL; j++)
		{
			temp2[k] = print_sentence[j];
			k++;
		}
		for (int j = 0; j < lengthname; j++)	//name에 있는 데이터 지우기
			print_sentence[j] = NULL;
		strcpy(print_sentence, temp2);					//temp2의 내용을 name으로 옮기기
		
		if (firstcount)
			printf("\t%s\n", temp1);					//temp1의 내용 출력
		else
			printf("\t   %s\n", temp1);
		
		dellen = sizeof(temp2);
		for (int j = 0; j < dellen; j++)		//다음에 받을 데이터를 위해 temp2의 내용 지우기
			temp2[j] = NULL;
		if (firstcount)
		{
			widlen -= 6;
			firstcount = 0;
		}
		nextrow = widlen;
		lengthname = 0;
		dellen = 0;
	}
	if (firstcount)
		printf("\t%s\n", print_sentence);
	else
		printf("\t   %s\n", print_sentence);
	puts("");
}
//문제 자동 줄바꿈해서 출력
void questionrowchange(ObjectiveQuestion* questions, int id)
{
	printf("\n\n");
	if (changecolor[2] != 1)
		optionchange(questions,id);
	char name[1024] = { NULL };
	char addChar[10] = {"Q. "};

	//출력할 내용 선택
	for (int i = 0; i < 4; i++)
	{
		name[i] = addChar[i];
	}
	strcpy(name + strlen(name), questions[id].question);
	print_change_row(&name);
	printf("\n");
}
//보기 자동 줄바꿈해서 출력
void optionrowchange(ObjectiveQuestion* questions, int id, int choice)
{
	char name[1024] = { NULL };
	char addChar[4][10] = {{"① "},{"② "},{"③ "},{"④ "} };
	int mycolor=240;
	//색 선택
	if (changecolor[2] == 1){
		if (changecolor[0] == changecolor[1] && changecolor[0] == choice)
			mycolor = 242;
		else if (changecolor[0] != changecolor[1] && changecolor[0] == choice)
			mycolor = 252;
		else if (changecolor[0] != changecolor[1] && changecolor[1] == choice)
			mycolor = 249;
	}
	else{
		mycolor = 240;
	}
	SetConsoleTextAttribute(console, mycolor);
	//출력할 내용 선택
	for (int i = 0; i < 4; i++)
	{
		name[i] = addChar[choice-1][i];
	}
	strcpy(name + strlen(name), options[choice-1]);
	print_change_row(&name);
	SetConsoleTextAttribute(console, 240);
}