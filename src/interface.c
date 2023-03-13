#include "globals.h"

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

void InitScreen()
{
	// 콘솔 창 크기 바꾸기
	SMALL_RECT windowSize = {0, 0, 79, 29}; // {, , 넓이(80열), 높이 (30행)}
	SetConsoleWindowInfo(console, TRUE, &windowSize);

	set_console_font_size(font_size);

	fit_console_screen_buffer_size();

	SetCursorVisibility(0);

	// 콘솔 창 컬러 바꾸기
	set_color_theme(color_mode);
}





// Main While Loop에서 쓰이는 3가지.
// 화면 클리어 추후 삭제.
void clearScreen()
{
	system("cls");
}

// char app_mode =  {"main_menu", ""}

// 화면 그리기
void drawScreen()
{
	system("cls");

	drawTopBar();

	if (app_mode == "objective")
	{
		drawQuestion();
		drawObjectiveOptions();
	}
	else if (app_mode == "subjective")
	{
		drawQuestion();
	}

	else if (app_mode == "main_menu" ||
			 app_mode == "options" ||
			 app_mode == "user_info")
	{
		drawTitle();
		drawMainMenu();
	}

	drawBottomBar();
}

// 유저 Input 받기
void getUserInput()
{
	app_input = getchar();
}

////////// Draw ///////////
void drawTitle()
{
	printf("\n");
	printf("\n");
	printf("                               안녕하세요 %s님!\n", user_name);
	printf("\n");
	printf("               _________  _____ ______       _             _       \n");
	printf("              |_  | ___ \\/  __ \\| ___ \\     | |           | |      \n");
	printf("                | | |_/ /| /  \\/| |_/ /  ___| |_ _   _  __| |_   _ \n");
	printf("                | | ___ \\| |    |    /  / __| __| | | |/ _` | | | |\n");
	printf("            /\\__/ / |_/ /| \\__/\\| |\\ \\  \\__ \\ |_| |_| | (_| | |_| |\n");
	printf("            \\____/\\____/  \\____/\\_| \\_| |___/\\__|\\__,_|\\__,_|\\__, |\n");
	printf("                                                              __/ |\n");
	printf("                                                             |___/ \n");
	printf("\n");
	printf("                            - 정보처리기사 공부 App -\n");

	cursorPosition.X = 28;
	cursorPosition.Y = 16;
	SetConsoleCursorPosition(console, cursorPosition);
}

void drawTopBar()
{
}
void drawQuestion()
{
}
void drawObjectiveOptions()
{
}

void drawBottomBar()
{
}

void drawMainMenu()
{

	const char *main_menu[] = {"1. 객관식 문제",
							   "2. 주관식 풀기",
							   "3. 사용자",
							   "4. 옵션",
							   "5. 종료"};

	cursorPosition.X = 28;
	cursorPosition.Y = 16;
	SetConsoleCursorPosition(console, cursorPosition);

	for (int i = 0; i < 5; i++)
	{
		SetConsoleCursorPosition(console, cursorPosition);
		printf("%s %s\n", (app_menu_item) == i ? "▶" : " ", main_menu[i]);
		cursorPosition.Y += 2;
	}
}
void DrawOptions()
{

	char option1[50];
	sprintf(option1, "틀린 문제 재학습 주기: %02d", interval_failed_questions);

	char option2[20];
	sprintf(option2, "화면 크기: %d", font_size);

	char option3[20];
	sprintf(option3, "테마: %d", color_mode);

	char *option_items[] = {option1,
							option2,
							option3,
							"디폴트 값으로 옵션 초기화",
							"뒤로 가기"};

	cursorPosition.X = 26;
	cursorPosition.Y = 16;
	SetConsoleCursorPosition(console, cursorPosition);

	for (int i = 0; i < 5; i++)
	{
		SetConsoleCursorPosition(console, cursorPosition);
		printf("%s %s\n", (app_menu_item) == i ? "▶" : " ", option_items[i]);
		cursorPosition.Y += 2;
	}
}

void drawUserInfo()
{
	char option0[50];
	sprintf(option0, "최고 Streak: %d", best_streak);

	char option1[50];
	int objective_percentage = (total_tried_objective == 0) ? 0 : (double)total_right_objective / total_tried_objective * 100;
	sprintf(option1, "객관식 푼 문제 수: %d | 정답률: %d%%", total_tried_objective, objective_percentage);

	char option2[50];
	int subjective_percentage = (total_tried_subjective == 0) ? 0 : (double)total_right_subjective / total_tried_subjective * 100;
	sprintf(option2, "주관식 푼 문제 수: %d | 정답률: %d%%", total_tried_subjective, subjective_percentage);

	char *option_items[] = {option0,
							option1,
							option2,
							"사용자 이름 변경",
							"뒤로 가기"};

	cursorPosition.X = 28;
	cursorPosition.Y = 16;
	SetConsoleCursorPosition(console, cursorPosition);

	for (int i = 0; i < 5; i++)
	{
		SetConsoleCursorPosition(console, cursorPosition);
		printf("%s %s\n", (app_menu_item) == i ? "▶" : " ", option_items[i]);
		cursorPosition.Y += 2;
	}
}

////////// control ///////////

void controlOptions()
{

	if (app_input == 'w' || app_input == 'W' || app_input == 72)
	{
		app_menu_item = (app_menu_item - 1 + 5) % 5;
	}
	else if (app_input == 's' || app_input == 'S' || app_input == 80)
	{
		app_menu_item = (app_menu_item + 1) % 5;
	}

	else if (app_input == 'a' || app_input == 'A' || app_input == 37)
	{

		switch (app_menu_item)
		{
		case 0:
			if (interval_failed_questions > 1)
			{
				interval_failed_questions--;
			}
			break;
		case 1:
			if (font_size > 1)
			{
				font_size--;
				set_console_font_size(font_size);
			}
			break;
		case 2:
			if (color_mode > 0)
			{
				color_mode--;
				set_color_theme(color_mode);
				clearScreen();
				drawTitle();
				draw_options();
			}
			break;
		}
	}
	else if (app_input == 'd' || app_input == 'D' || app_input == 39)
	{
		switch (app_menu_item)
		{
		case 0:
			if (interval_failed_questions < 50)
			{
				interval_failed_questions++;
			}
			break;
		case 1:
			if (font_size < 50)
			{
				font_size++;
				set_console_font_size(font_size);
			}
			break;
		case 2:
			if (color_mode < 3)
			{
				color_mode++;
				set_color_theme(color_mode);
				clearScreen();
				drawTitle();
				draw_options();
			}
			break;
		}
	}

	else if (app_input == '\r' && app_menu_item == 3)
	{
		interval_failed_questions = 10;
		font_size = 25;
		color_mode = 0;
		InitScreen();
		clearScreen();
		drawTitle();
		draw_options();
	}

	else if (app_input == '\r' && app_menu_item == 4)
	{
	}
}

void controlUserInfo()
{
	if (app_input == 'w' || app_input == 'W' || app_input == 72)
	{
		app_menu_item = (app_menu_item - 1 + 5) % 5;
	}

	else if (app_input == 's' || app_input == 'S' || app_input == 80)
	{
		app_menu_item = (app_menu_item + 1) % 5;
	}

	else if (app_input == 'a' || app_input == 'A' || app_input == 37)
	{
	}
	else if (app_input == 'd' || app_input == 'D' || app_input == 39)
	{
	}

	// 사용자 정보
	else if (app_input == '\r' && app_menu_item == 1)
	{
		clearScreen();
		drawTitle();
		draw_user_info();
		getch();
		clearScreen();
		drawTitle();
	}
	// 이름 변경
	else if (app_input == '\r' && app_menu_item == 2)
	{
		clearScreen();
		drawTitle();
		cursorPosition.X = 26;
		cursorPosition.Y = 16;
		SetConsoleCursorPosition(console, cursorPosition);
		printf("새로운 이름을 입력하세요");

		cursorPosition.X = 26;
		cursorPosition.Y = 18;
		SetConsoleCursorPosition(console, cursorPosition);
		printf("이름: ");

		scanf("%s", &user_name);

		cursorPosition.X = 26;
		cursorPosition.Y = 20;
		SetConsoleCursorPosition(console, cursorPosition);
		printf("환영합니다 %s님!", user_name);
		getch();
		clearScreen();
		drawTitle();
	}

	// 기록 초기화
	else if (app_input == '\r' && app_menu_item == 3)
	{
		resetUserInfo();
	}

	else if (app_input == '\r' && app_menu_item == 4)
	{
	}
}