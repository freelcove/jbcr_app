#include "options.h"



void draw_options() {

	char option1[50];
	sprintf(option1, "Ʋ�� ���� ���н� �ֱ�: %02d", interval_failed_questions);

	char option2[20];
	sprintf(option2, "ȭ�� ũ��: %d", font_size);

	char option3[20];
	sprintf(option3, "�׸�: %d", color_mode);

	char* option_items[] = { option1,
								   option2,
								   option3,
								   "����Ʈ ������ �ɼ� �ʱ�ȭ",
								   "�ڷ� ����" };

	cursorPosition.X = 26;
	cursorPosition.Y = 16;
	SetConsoleCursorPosition(console, cursorPosition);

	for (int i = 0; i < 5; i++) {
		SetConsoleCursorPosition(console, cursorPosition);
		printf("%s %s\n", (current_option_item) == i ? "��" : " ", option_items[i]);
		cursorPosition.Y += 2;
	}
}