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