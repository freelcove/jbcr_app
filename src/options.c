#include "options.h"

void drawOptions()
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
		printf("%s %s\n", (current_menu) == i ? "▶" : " ", option_items[i]);
		cursorPosition.Y += 2;
	}
}

void controlOptions()
{

	if (key_pressed == 'w' || key_pressed == 'W' || key_pressed == 72)
	{
		current_menu = (current_menu - 1 + 5) % 5;
	}
	else if (key_pressed == 's' || key_pressed == 'S' || key_pressed == 80)
	{
		current_menu = (current_menu + 1) % 5;
	}

	else if (key_pressed == 'a' || key_pressed == 'A' || key_pressed == 37)
	{

		switch (current_menu)
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
				drawOptions();
			}
			break;
		}
	}
	else if (key_pressed == 'd' || key_pressed == 'D' || key_pressed == 39)
	{
		switch (current_menu)
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
				drawOptions();
			}
			break;
		}
	}

	else if (key_pressed == '\r' && current_menu == 3)
	{
		interval_failed_questions = 10;
		font_size = 25;
		color_mode = 0;
		InitScreen();
		clearScreen();
		drawTitle();
		drawOptions();
	}

	else if (key_pressed == '\r' && current_menu == 4)
	{
		
	}
	

}

