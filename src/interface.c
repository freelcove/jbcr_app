#include "globals.h"

void ClearScreen()
{
	system("cls");
}

void SetCursorVisibility(int visible)
{
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(console, &cursor_info);
	cursor_info.bVisible = visible;
	SetConsoleCursorInfo(console, &cursor_info);
}

void set_console_font_size(int size)
{
	CONSOLE_FONT_INFOEX font_info = { 0 };
	font_info.cbSize = sizeof(font_info);
	GetCurrentConsoleFontEx(console, FALSE, &font_info);
	font_info.dwFontSize.Y = size; // set font size Y coordinate
	SetCurrentConsoleFontEx(console, FALSE, &font_info);
}

void InitScreen() {
	set_console_font_size(25);

	SetCursorVisibility(0);

	//콘솔 창 컬러 바꾸기 (흰 배경 검은 글자)
	system("COLOR F0");

	//콘솔 인코딩 utf_8로 설정
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	//콘솔 창 크기 바꾸기	
	SMALL_RECT windowSize = { 0, 0, 79, 29 };	// {, , 넓이(80열), 높이 (30행)}
	SetConsoleWindowInfo(console, TRUE, &windowSize);
}

void draw_title()
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

void draw_menu() {

	const char* menu_items[] = { "1. 객관식 문제",
								 "2. 주관식 문제",
								 "3. 미니게임",
								 "4. 옵션",
								 "5. 종료" };

	cursorPosition.X = 28;
	cursorPosition.Y = 16;
	SetConsoleCursorPosition(console, cursorPosition);

	for (int i = 0; i < 5; i++) {
		SetConsoleCursorPosition(console, cursorPosition);
		printf("%s %s\n", (current_menu_item) == i ? "▶" : " ", menu_items[i]);
		cursorPosition.Y += 2;
	}
}