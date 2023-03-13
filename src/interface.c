#include "globals.h"

void clearScreen()
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

void fit_console_screen_buffer_size() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console, &csbi);

	COORD new_size = {
		csbi.srWindow.Right - csbi.srWindow.Left + 1,
		csbi.srWindow.Bottom - csbi.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(console, new_size);
}


void set_color_theme(int color_mode) {

	SetConsoleTextAttribute(console, color_mode_preset[color_mode%4]);

}


void InitScreen() {
	//�ܼ� â ũ�� �ٲٱ�	
	SMALL_RECT windowSize = { 0, 0, 75, 29 };	// {, , ����(76��), ���� (30��)}
	SetConsoleWindowInfo(console, TRUE, &windowSize);

	set_console_font_size(font_size);

	fit_console_screen_buffer_size();

	SetCursorVisibility(0);

	//�ܼ� â �÷� �ٲٱ�
	set_color_theme(color_mode);

	//�ܼ� ���ڵ� utf_8�� ����



}

void drawTitle()
{
	printf("\n");
	printf("\n");
	printf("                            �ȳ��ϼ��� %s��!\n", user_name);
	printf("\n");
	printf("             _________  _____ ______       _             _       \n");
	printf("            |_  | ___ \\/  __ \\| ___ \\     | |           | |      \n");
	printf("              | | |_/ /| /  \\/| |_/ /  ___| |_ _   _  __| |_   _ \n");
	printf("              | | ___ \\| |    |    /  / __| __| | | |/ _` | | | |\n");
	printf("          /\\__/ / |_/ /| \\__/\\| |\\ \\  \\__ \\ |_| |_| | (_| | |_| |\n");
	printf("          \\____/\\____/  \\____/\\_| \\_| |___/\\__|\\__,_|\\__,_|\\__, |\n");
	printf("                                                            __/ |\n");
	printf("                                                           |___/ \n");
	printf("\n");
	printf("                          - ����ó����� ���� App -\n");

}

void draw_menu() {

	const char* menu_items[] = { "1. ������ ����",
								 "2. �ְ��� Ǯ��",
								 "3. �����",
								 "4. �ɼ�",
								 "5. ����" };

	cursorPosition.X = 28;
	cursorPosition.Y = 16;
	SetConsoleCursorPosition(console, cursorPosition);

	for (int i = 0; i < 5; i++) {
		SetConsoleCursorPosition(console, cursorPosition);
		printf("%s %s\n", (current_menu) == i ? "��" : " ", menu_items[i]);
		cursorPosition.Y += 2;
	}
}
