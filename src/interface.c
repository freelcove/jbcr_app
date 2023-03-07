#include "globals.h"
#include "interface.h"
#include "questions.h"
#include <windows.h>

void ClearScreen()
{
	system("cls");
}

void SetCursorVisibility(int visible, HANDLE console)
{
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(console, &cursor_info);
	cursor_info.bVisible = visible;
	SetConsoleCursorInfo(console, &cursor_info);
}

void set_console_font_size(int size, HANDLE console)
{
	CONSOLE_FONT_INFOEX font_info = { 0 };
	font_info.cbSize = sizeof(font_info);
	GetCurrentConsoleFontEx(console, FALSE, &font_info);
	font_info.dwFontSize.Y = size; // set font size Y coordinate
	SetCurrentConsoleFontEx(console, FALSE, &font_info);
}

void InitScreen(HANDLE console) {
	set_console_font_size(25, console);

	SetCursorVisibility(0, console);

	//콘솔 창 컬러 바꾸기 (흰 배경 검은 글자)
	system("COLOR F0");

	//콘솔 인코딩 utf_8로 설정
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	//콘솔 창 크기 바꾸기	
	SMALL_RECT windowSize = { 0, 0, 79, 29 };	// {, , 넓이(80열), 높이 (30행)}
	SetConsoleWindowInfo(console, TRUE, &windowSize);
}

void draw_title(HANDLE console)
{
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	SetConsoleTextAttribute(console, 250);
	printf("              _________  _____ ______       _             _       \n");
	printf("             |_  | ___ \\/  __ \\| ___ \\     | |           | |      \n");
	printf("               | | |_/ /| /  \\/| |_/ /  ___| |_ _   _  __| |_   _ \n");
	printf("               | | ___ \\| |    |    /  / __| __| | | |/ _` | | | |\n");
	printf("           /\\__/ / |_/ /| \\__/\\| |\\ \\  \\__ \\ |_| |_| | (_| | |_| |\n");
	printf("           \\____/\\____/  \\____/\\_| \\_| |___/\\__|\\__,_|\\__,_|\\__, |\n");
	printf("                                                             __/ |\n");
	printf("                                                            |___/ \n");
	printf("\n");
	SetConsoleTextAttribute(console, 240);
	printf("                           - 정보처리기사 공부 App -\n");
}

void draw_menu(HANDLE console, int* current_menu_item, COORD cursorPosition) {
	const char* menu_items[] = { "1. 객관식 문제 풀기",
								 "2. 주관식 문제 풀기",
								 "3. (미정)",
								 "4. 옵션",
								 "5. 종료" };

	cursorPosition.X = 28;
	cursorPosition.Y = 16;
	SetConsoleCursorPosition(console, cursorPosition);

	for (int i = 0; i < 5; i++) {
		SetConsoleCursorPosition(console, cursorPosition);
		printf("%s %s\n", (*current_menu_item) == i ? "▶" : " ", menu_items[i]);
		cursorPosition.Y += 2;
	}
}

void draw_question(HANDLE console, Question* questions, int id, COORD cursorPosition) {
	int sentence_length = strlen(questions[id].question);
	int target_width = 70;
	int num_lines = sentence_length / target_width + 1;
	int start_index = 0;
	for (int i = 4; i < 4 + num_lines; i++) {

		int line_length = strnlen(questions[id].question + start_index, target_width);

		// 마지막 글자가 한글인지 체크
		int check = 0;
		if ((questions[id].question[start_index + line_length - 1] & 0x80) != 0) {
			line_length++;
			check = 1;
		}

		char substring[73];
		strncpy(substring, questions[id].question + start_index, line_length);
		substring[line_length + 1] = '\0';

		cursorPosition.X = 14;
		cursorPosition.Y = i;
		SetConsoleCursorPosition(console, cursorPosition);
		printf("%s\n", substring);

		if (check == 1) {
			start_index += line_length - 2;
		}
		else {
			start_index += line_length;
		}
	}
}

void draw_options(HANDLE console, Question* questions, int id, COORD cursorPosition) {

	cursorPosition.X = 10;
	cursorPosition.Y = 10;
	const char* options[] = { questions[id].option_1, questions[id].option_2,questions[id].option_3,questions[id].option_4 };
	const char* numbering[] = { "①", "②", "③", "④" };
	for (int i = 0; i < 4; i++) {
		SetConsoleCursorPosition(console, cursorPosition);
		printf("%s %s\n", numbering[i], options[i]);
		cursorPosition.Y += 2;
	}
}