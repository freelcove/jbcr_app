#include"questions.h"
#include"print.h"
#include<mbstring.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

static int count = 1;

//문제 출력
void printquestion(Question*questions, int id)
{
	printf("%d. %s\n\n",count,questions[id].question);

	count++;
}
//보기1,2 사이 간격,줄바꿈 설정
void changerow1(Question* questions, int id)
{
	int lendiff1 = 37-(_mbslen(questions[id].option_1));
	int lendiff2 = 37-(_mbslen(questions[id].option_3));
	if (strlen(questions[id].option_1) > 40) 
	{
		printf("\n");
	}
	else
	{
		if (lendiff1 >0)
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
void changerow2(Question* questions, int id)
{
	int lendiff1 = 37 - (_mbslen(questions[id].option_1));
	int lendiff2 = 37 - (_mbslen(questions[id].option_3));
	if (strlen(questions[id].option_1) > 40)
	{
		printf("\n");
	}
	else
	{
		if (lendiff2 >0)
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
//보기 1,2,3,4 출력설정
//a~d -> 1~4로 수정

void printoptions(Question* questions, int id)
{
	printf("1. %s", questions[id].option_1);
	changerow1(questions,id);
	printf("2. %s\n", questions[id].option_2);
	printf("3. %s", questions[id].option_3);
	changerow2(questions, id);
	printf("4. %s\n\n", questions[id].option_4);
}

//랜덤의 숫자 반환(10미만)
int randnum()
{
	srand(time(NULL)*rand());
	return (rand()%10);
}
