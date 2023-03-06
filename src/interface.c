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

	//�ܼ� â �÷� �ٲٱ� (�� ��� ���� ����)
	system("COLOR F0");

	//�ܼ� ���ڵ� utf_8�� ����
	SetConsoleOutputCP(51949);
	SetConsoleCP(51949);

	//�ܼ� â ũ�� �ٲٱ�
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT windowSize = { 0, 0, 99, 119 };
	SetConsoleWindowInfo(console, TRUE, &windowSize);

	//�����̴� Ŀ�� ���ֱ�.
	SetCursorVisibility(0);
}
