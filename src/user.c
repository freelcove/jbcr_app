#include "user.h"


void draw_user_options() {


	char option1[50];
	sprintf(option1, "���� �����: %s", user_name);


	char* option_items[] = { option1,
							 "����� ����",
							 "�̸� ����",
							 "��� �ʱ�ȭ",
							 "�ڷ� ����" };

	cursorPosition.X = 28;
	cursorPosition.Y = 16;
	SetConsoleCursorPosition(console, cursorPosition);

	for (int i = 0; i < 5; i++) {
		SetConsoleCursorPosition(console, cursorPosition);
		printf("%s %s\n", (current_menu_item) == i ? "��" : " ", option_items[i]);
		cursorPosition.Y += 2;
	}
}

void controlUserOptions(){
		if (key_pressed == 'w' || key_pressed == 'W' || key_pressed == 72) {
					current_menu_item = (current_menu_item - 1 + 5) % 5;
				}

				else if (key_pressed == 's' || key_pressed == 'S' || key_pressed == 80) {
					current_menu_item = (current_menu_item + 1) % 5;
				}

				else if (key_pressed == 'a' || key_pressed == 'A' || key_pressed == 37) {


				}
				else if (key_pressed == 'd' || key_pressed == 'D' || key_pressed == 39) {
				}

				//����� ����
				else if (key_pressed == '\r' && current_menu_item == 1) {
					ClearScreen();
					draw_title();
					draw_user_info();
					getch();
					ClearScreen();
					draw_title();
				}
				//�̸� ����
				else if (key_pressed == '\r' && current_menu_item == 2) {
					ClearScreen();
					draw_title();
					cursorPosition.X = 26;
					cursorPosition.Y = 16;
					SetConsoleCursorPosition(console, cursorPosition);
					printf("���ο� �̸��� �Է��ϼ���");

					cursorPosition.X = 26;
					cursorPosition.Y = 18;
					SetConsoleCursorPosition(console, cursorPosition);
					printf("�̸�: ");
					
					scanf("%s", &user_name);

					cursorPosition.X = 26;
					cursorPosition.Y = 20;
					SetConsoleCursorPosition(console, cursorPosition);
					printf("ȯ���մϴ� %s��!", user_name);
					getch();
					ClearScreen();
					draw_title();
				}

				//��� �ʱ�ȭ
				else if (key_pressed == '\r' && current_menu_item == 3) {
					resetUserInfo();
				}

				else if (key_pressed == '\r' && current_menu_item == 4) {

					
				}
}


void draw_user_info() {

	char option0[50];
	sprintf(option0, "�ְ� Streak: %d", best_streak);

	char option1[50];
	sprintf(option1, "�������� Ǭ �� ���� ��: %d", total_tried_objective + total_tried_subjective);

	char option2[50];
	int objective_percentage = (total_tried_objective == 0) ? 0 : (double)total_right_objective / total_tried_objective * 100;
	sprintf(option2, "������ Ǭ ���� ��: %d | �����: %d%%", total_tried_objective, objective_percentage);

	char option3[50];
	int subjective_percentage = (total_tried_subjective == 0) ? 0 : (double)total_right_subjective / total_tried_subjective * 100;
	sprintf(option3, "�ְ��� Ǭ ���� ��: %d | �����: %d%%", total_tried_subjective, subjective_percentage);

	char* user_info_list[] = { option0, option1, option2, option3, "(�ڷ� ������ �ƹ� Ű�� ��������.)" };

	cursorPosition.X = 26;
	cursorPosition.Y = 16;

	for (int i = 0; i < 5; i++) {
		SetConsoleCursorPosition(console, cursorPosition);
		printf("%s\n", user_info_list[i]);
		cursorPosition.Y += 2;
	}
}

void WriteUserInfo() {
	FILE* file;
	char line[MAX_LINE_LENGTH];

	file = fopen("db/db_user_info.tsv", "w");
	if (file == NULL) {
		printf("Failed to open file.\n");
		return;
	}

	fprintf(file, "%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
		user_name, interval_failed_questions, font_size,
		color_mode, best_streak, current_streak,
		total_tried_objective, total_right_objective,
		total_tried_subjective, total_right_subjective);

	fclose(file);
}

void LoadUserInfo() {
	FILE* file;
	char line[MAX_LINE_LENGTH];

	file = fopen("db/db_user_info.tsv", "r");
	if (file == NULL) {
		return;
	}

	fgets(line, MAX_LINE_LENGTH, file);
	
	sscanf(line, "%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",
		user_name, &interval_failed_questions, &font_size,
		&color_mode, &best_streak, &current_streak,
		&total_tried_objective, &total_right_objective,
		&total_tried_subjective, &total_right_subjective);
	
	fclose(file);
}

void resetUserInfo()
{
	best_streak = 0;
	current_streak = 0;

	total_tried_objective = 0;
	total_right_objective = 0;

	total_tried_subjective = 0;
	total_right_subjective = 0;
}

