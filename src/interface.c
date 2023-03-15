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
	CONSOLE_FONT_INFOEX font_info = {0};
	font_info.cbSize = sizeof(font_info);
	GetCurrentConsoleFontEx(console, FALSE, &font_info);
	font_info.dwFontSize.Y = size; // set font size Y coordinate
	SetCurrentConsoleFontEx(console, FALSE, &font_info);
}

void fit_console_screen_buffer_size()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console, &csbi);

	COORD new_size = {
		csbi.srWindow.Right - csbi.srWindow.Left + 1,
		csbi.srWindow.Bottom - csbi.srWindow.Top + 1};
	SetConsoleScreenBufferSize(console, new_size);
}

void set_color_theme(int color_mode)
{

	SetConsoleTextAttribute(console, color_mode_preset[color_mode % 4]);
}

void initScreen()
{
	// 콘솔 창 크기 바꾸기
	SMALL_RECT windowSize = {0, 0, 75, 29}; // {, , 넓이(76열), 높이 (30행)}
	SetConsoleWindowInfo(console, TRUE, &windowSize);

	set_console_font_size(font_size);

	fit_console_screen_buffer_size();

	SetCursorVisibility(0);

	// 콘솔 창 컬러 바꾸기
	set_color_theme(color_mode);

	// 콘솔 인코딩 utf_8로 설정
}

void drawTitle()
{
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");

	int temp_color_mode;
	switch (color_mode)
	{
	case 0:
	temp_color_mode = 250;
		break;
	case 1:
	temp_color_mode = 142;
		break;
	case 2:
	temp_color_mode = 185;
		break;
	case 3:
	temp_color_mode = 237;
		break;
	default:
		break;
	}
	SetConsoleTextAttribute(console, temp_color_mode);
	printf("             _________  _____ ______       _             _       \n");
	printf("            |_  | ___ \\/  __ \\| ___ \\     | |           | |      \n");
	printf("              | | |_/ /| /  \\/| |_/ /  ___| |_ _   _  __| |_   _ \n");
	printf("              | | ___ \\| |    |    /  / __| __| | | |/ _` | | | |\n");
	printf("          /\\__/ / |_/ /| \\__/\\| |\\ \\  \\__ \\ |_| |_| | (_| | |_| |\n");
	printf("          \\____/\\____/  \\____/\\_| \\_| |___/\\__|\\__,_|\\__,_|\\__, |\n");
	printf("                                                            __/ |\n");
	printf("                                                           |___/ \n");
	set_color_theme(color_mode);
	printf("\n");
	printf("                          - 정보처리기사 공부 App -\n");
	cursorPosition.X = 54;
	cursorPosition.Y = 29;
	SetConsoleCursorPosition(console, cursorPosition);
	printf("Ver. 1.0 (2023.03.15)");
}

void drawMenu(int num_menu_items, char *menu_items[], int position_x, int position_y)
{

	COORD cursorPosition = {position_x, position_y};

	for (int i = 0; i < num_menu_items; i++, cursorPosition.Y += 2)
	{
		SetConsoleCursorPosition(console, cursorPosition);
		printf("%s %s\n", (current_menu) == i ? "▶" : " ", menu_items[i]);
	}
}
// 사용자 입력을 받아서 해당 키에 따라 값을 반환
// 숫자 -> 해당하는 메뉴 값 0~4
// 방향키 또는 wsad -> 좌우는 8, 9, 상하는 메뉴 값만 조정 반환값 -1
// 엔터키 -> 현재 메뉴 값 반환 0~4
// esc -> 4
// 디폴트 반환값 = -1

int processUserInput(int num_menu_items)
{

	key_pressed = getch();
	if(key_pressed==224)
		key_pressed = getch();
	switch (key_pressed)
	{
	case '1':
		return 0;
		break;
	case '2':
		return 1;
		break;
	case '3':
		return 2;
		break;
	case '4':
		return 3;
		break;
	case '5':
		return 4;
		break;
	case 27: // = esc
		return 4;
		break;
	default:
		break;
	}

	if (key_pressed == '\r')
	{
		switch (current_menu)
		{
		case 0:
			return 0;
			break;
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		case 3:
			return 3;
			break;
		case 4:
			return 4;
			break;
		default:
			break;
		}
	}

	else if (key_pressed == 'w' || key_pressed == 'W' || key_pressed == 72)
	{
		current_menu = (current_menu - 1 + num_menu_items) % num_menu_items;
	}
	else if (key_pressed == 's' || key_pressed == 'S' || key_pressed == 80)
	{
		current_menu = (current_menu + 1) % num_menu_items;
	}
	else if (key_pressed == 'a' || key_pressed == 'A' || key_pressed == 75)
	{
		return 8;
	}
	else if (key_pressed == 'd' || key_pressed == 'D' || key_pressed == 77)
	{
		return 9;
	}

	return -1;
}

void controlMainMenu(int input)
{
	switch (input)
	{
	case 0:
		current_mode = 0;
		current_menu = 0;
		break;
	case 1:
		current_mode = 1;
		current_menu = 0;
		break;
	case 2:
		current_mode = 2;
		current_menu = 0;
		break;
	case 3:
		current_mode = 3;
		current_menu = 0;
		break;
	case 4:
		current_mode = 4;
		break;
	default:
		break;
	}
}

void controlOptions(int input)
{
	switch (input)
	{
	// 초기화
	case 3:
		interval_failed_questions = 10;
		font_size = 25;
		color_mode = 0;
		initScreen();
		break;

	// 뒤로 가기
	case 4:
		current_mode = 5;
		current_menu = 0;
		break;

	// 증가
	case 8:
		if (current_menu == 0)
		{
			interval_failed_questions=(interval_failed_questions-2+50)%50+1;
		}
		else if (current_menu == 1)
		{
			font_size=(font_size-2+50)%50+1;
		}

		else if (current_menu == 2)
		{
			color_mode=(color_mode-1+4)%4;
		}
		initScreen(); /* code */
		break;

		// 감소
	case 9:
		if (current_menu == 0)
		{
			interval_failed_questions=(interval_failed_questions)%50+1;
		}
		else if (current_menu == 1)
		{
			font_size=(font_size)%50+1;
		}

		else if (current_menu == 2)
		{
			color_mode=(color_mode+1)%4;
		}
		initScreen();

	default:
		break;
	}
}

void controlInfo(int input)
{
	switch (input)
	{
	case 3:
		resetUserInfo();
		break;
	// 뒤로 가기
	case 4:
		current_mode = 5;
		current_menu = 0;
		break;

	default:
		break;
	}
}
