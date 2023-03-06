#include <windows.h>
#include "interface.h"

void ClearScreen()
{
	system("cls");
}

void SetCursorVisibility(int visible)
{
	HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(console_handle, &cursor_info);
	cursor_info.bVisible = visible;
	SetConsoleCursorInfo(console_handle, &cursor_info);
}

void set_console_font_size(int size)
{
	CONSOLE_FONT_INFOEX font_info = { 0 };
	font_info.cbSize = sizeof(font_info);
	GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font_info);
	font_info.dwFontSize.Y = size; // set font size Y coordinate
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font_info);
}

void InitScreen() {

	//폰트 크기 바꾸기
	set_console_font_size(25);

	//콘솔 창 컬러 바꾸기 (흰 배경 검은 글자)
	system("COLOR F0");

	//콘솔 인코딩 utf_8로 설정
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	//콘솔 창 크기 바꾸기
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	// {시작 x좌표, 시작 y좌표, 넓이(80열), 높이 (30행)}
	SMALL_RECT windowSize = { 0, 0, 79, 29 };
	SetConsoleWindowInfo(console, TRUE, &windowSize);

	//깜빡이는 커서 없애기.
	SetCursorVisibility(0);
}