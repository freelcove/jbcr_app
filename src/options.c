#include "options.h"



void draw_options() {

	char option1[50];
	sprintf(option1, "틀린 문제 재학습 주기: %02d", interval_failed_questions);

	char option2[20];
	sprintf(option2, "화면 크기: %d", font_size);

	char option3[20];
	sprintf(option3, "테마: %d", color_mode);

	char* option_items[] = { option1,
								   option2,
								   option3,
								   "디폴트 값으로 옵션 초기화",
								   "뒤로 가기" };

	cursorPosition.X = 26;
	cursorPosition.Y = 16;
	SetConsoleCursorPosition(console, cursorPosition);

	for (int i = 0; i < 5; i++) {
		SetConsoleCursorPosition(console, cursorPosition);
		printf("%s %s\n", (current_option_item) == i ? "▶" : " ", option_items[i]);
		cursorPosition.Y += 2;
	}
}