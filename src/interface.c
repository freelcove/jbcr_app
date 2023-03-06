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




void InitScreen() {

	//콘솔 창 컬러 바꾸기 (흰 배경 검은 글자)
	system("COLOR F0");

	//콘솔 인코딩 utf_8로 설정
	SetConsoleOutputCP(51949);
	SetConsoleCP(51949);

	//콘솔 창 크기 바꾸기
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT windowSize = { 0, 0, 99, 119 };
	SetConsoleWindowInfo(console, TRUE, &windowSize);

	//깜빡이는 커서 없애기.
	SetCursorVisibility(0);
}
