#include "globals.h"

#define MAX_LINE_LENGTH 1024
#define MAX_QUESTIONS 100

static int count = 1;
char options[4][MAX_LINE_LENGTH];
static int maxlen = 0;
static int count_change_row = 0;
static int right_answer;


//보기 출력 순서 변경에 따른 정답 변경
char changedanswer()
{
	return right_answer + '0';
}

//보기 1,2,3,4 출력 순서 섞기
void optionchange(ObjectiveQuestion* questions, int id)
{
	right_answer = 0;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < sizeof(options[x]); y++)
			options[x][y] = NULL;
	}

	int nums[4] = { 0, 1, 2, 3 };
	int i, temp, rand_idx;
	for (i = 0; i < 4; i++) {
		rand_idx = (rand()*time(NULL)) % 4;  // 0 ~ 3까지의 랜덤한 인덱스 생성
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

//점수 출력
void Percentage(int num)
{
	if (num != 0)
	{
		int correct = num - faltcount;
		printf("\n\n\n\n\t\t\t%d문제중 %d문제 맞추었습니다.\n\n\t\t\t%d점\n", num, correct, correct * 100 / num);
	}
	if(num==0)
		printf("\n\n\n\n\t\t\t푼 문제가 없습니다.\n");

}

//문자열 길이 맞춰서 줄바꾸기
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
		//내용이 지정한 길이보다 길때 자를 위치 지정
		if (lengthname >= widlen)
		{
			for (int i = widlen; print_sentence[i] != ' '; i++)
				nextrow = i+1;
			for (int i = widlen; print_sentence[i] != ' '; i--)
				min_nextrow = i-1;
		}
		//자를위치가 내용의 길이와 같거나 길때 내용 그대로 출력하기 위해 반복문 종료
		if (nextrow - widlen > widlen - min_nextrow)
			nextrow = min_nextrow;
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
			printf("  %s\n", temp1);					//temp1의 내용 출력
		else
			printf("\t     %s\n", temp1);

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
		count_change_row++;
	}
	if (firstcount)
		printf("  %s\n", print_sentence);
	else
		printf("\t     %s\n", print_sentence);
}

//입력값에 따른 출력 색 변경
int select_color(int choice)
{	//240		143		176		225
	int mycolor = color_mode_preset[color_mode%4];
	//색 선택
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

//객관식 문제 출력
void print_objective_question(ObjectiveQuestion* questions, int id, int choice)
{

	char name[MAX_LINE_LENGTH] = { NULL };
	char addChar[5][10] = { {"  Q. "}, {"① "},{"② "},{"③ "},{"④ "} };
	int mycolor = select_color(choice);
	SetConsoleTextAttribute(console, mycolor);

	//출력할 내용 선택
	for (int i = 0; i < 10; i++)
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

//옵션들중 커서의 위치 출력
void option_select(ObjectiveQuestion* questions, int id)
{
	cursorPosition.X =6;
	cursorPosition.Y = 4;
	char icon[3][10] = { {"▶"},{"O"},{"X"}};
	int num;
	SetConsoleCursorPosition(console, cursorPosition);
	for (int i = 0; i < 4; i++) {
		if (i == 0)
		{
			print_objective_question(questions, id, 0);
			cursorPosition.Y += count_change_row;
		}
		SetConsoleCursorPosition(console, cursorPosition);
		if (changecolor[2] == 1)
		{
			if (changecolor[0] == changecolor[1]&&changecolor[0] == i + 1) {
				num = 1;
				current_menu = changecolor[0]-1;
			}
			else if (changecolor[0] != changecolor[1] && changecolor[0] == i+1){
				num = 2;
				current_menu = changecolor[0]-1;
			}
			else if (changecolor[1] == i+1){
				num = 1;
				current_menu = changecolor[1]-1;
			}
		}
		else num = 0;
		printf("%s ", ((current_menu) == i) ? icon[num] : " ");
		print_objective_question(questions, id, i + 1);
		cursorPosition.Y += count_change_row;
	}
}

void print_best_streak()
{
	int x1, y1;
	x1 = cursorPosition.X;
	y1 = cursorPosition.Y;
	cursorPosition.X = 64;
	cursorPosition.Y = 0;
	SetConsoleCursorPosition(console, cursorPosition);
	printf("BEST : %d\n", best_streak);	//첫줄 가장자리에 best_streak 출력
	cursorPosition.X = x1;
	cursorPosition.Y = y1;
	SetConsoleCursorPosition(console, cursorPosition);
}

//방향키나 번호로 정답 선택하기
int select_by_arrow(ObjectiveQuestion* questions, int id)
{
	int x1, y1;
	int key_in;
	int num;

	while (1) {
		print_best_streak();
		option_select(questions, id);
		printf("\n\n\t     정답을 선택하세요(1~4): \n");
		key_pressed = getch();
		if (key_pressed == 'w' || key_pressed == 'W' || key_pressed == 72) {
			current_menu = (current_menu + 3) % 4;
		}
		else if (key_pressed == 's' || key_pressed == 'S' || key_pressed == 80) {
			current_menu = (current_menu + 1) % 4;
		}
		else if (key_pressed == '\r') {
			clearScreen();
			break;
		}
		else if (key_pressed >= '1' && key_pressed <= '4') {
			current_menu = key_pressed - 1-'0';
			clearScreen();
			break;
		}
		else if (key_pressed == 27)
			return -1;
	}
	changecolor[0] += current_menu % 4 + 1;
	changecolor[1] += changedanswer() - '0';
	changecolor[2] += 1;
	current_menu = changedanswer() - '0' - 1;
	option_select(questions, id);
	num = check_my_answer(id);							//정답 체크

	print_best_streak();

	changecolor[0] = 0;
	changecolor[1] = 0;
	changecolor[2] = 0;
	return num;

}

//메뉴에서 나가기
void exit_menu(int solved_questions)
{
	clearScreen();
	Percentage(solved_questions);
	while (1)
	{
		if (kbhit()) {
			char input = getch();
			break;
		}
	}

}

void all_process_objective(ObjectiveQuestion* objective_questions, struct Queue* queue_objective)
{
	solved_questions = 0;
	current_streak = 0;
	faltcount = 0;
	while (1)
	{
		int start = time(NULL);
		int id = queue_objective->front->key;
		int num;
		int swit = 0;
		optionchange(objective_questions, id);
		num = select_by_arrow(objective_questions, id);
		if (num == 1) {
			enqueue(queue_objective, queue_objective->front->key);
			dequeue(queue_objective);
		}
		else if (num == 0) {
			insert_after_x(queue_objective, queue_objective->front->key, interval_failed_questions);
			dequeue(queue_objective);
		}
		else if (num == -1)
		{

			exit_menu(solved_questions);

			break;
		}
		solved_questions++;
		printf("\t     다음 문제로 넘어가시려면 엔터를 누르세요\n\t     종료를 원하시면 Esc를 누르세요.\n");
		current_menu = 0;
		while (1)
		{
			if (kbhit()) {
				char input = getch();
				if (input == 27)
					swit = 1;
				break;
			}
		}
		if (swit == 1)
		{
			exit_menu(solved_questions);
			break;
		}

		clearScreen();
	}
	total_tried_objective += solved_questions;
	total_right_objective += solved_questions-faltcount;
	solved_questions = 0;
	faltcount = 0;
	current_streak = 0;
}