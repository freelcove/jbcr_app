#include "user.h"


void draw_user_options() {


	char option1[50];
	sprintf(option1, "현재 사용자: %s", user_name);


	char* option_items[] = { option1,
							 "사용자 정보",
							 "이름 변경",
							 "기록 초기화",
							 "뒤로 가기" };

	cursorPosition.X = 28;
	cursorPosition.Y = 16;
	SetConsoleCursorPosition(console, cursorPosition);

	for (int i = 0; i < 5; i++) {
		SetConsoleCursorPosition(console, cursorPosition);
		printf("%s %s\n", (current_option_item) == i ? "▶" : " ", option_items[i]);
		cursorPosition.Y += 2;
	}
}


void draw_user_info() {

	char option0[50];
	sprintf(option0, "최고 Streak: %d", best_streak);

	char option1[50];
	sprintf(option1, "이제까지 푼 총 문제 수: %d", total_tried_objective + total_tried_subjective);

	char option2[50];
	int objective_percentage = (total_tried_objective == 0) ? 0 : total_right_objective / total_tried_objective * 100;
	sprintf(option2, "객관식 푼 문제 수: %d | 정답률: %d%%", total_tried_objective, objective_percentage);

	char option3[50];
	int subjective_percentage = (total_tried_subjective == 0) ? 0 : total_right_subjective / total_tried_subjective * 100;
	sprintf(option3, "주관식 푼 문제 수: %d | 정답률: %d%%", total_tried_subjective, subjective_percentage);

	char* user_info_list[] = { option0, option1, option2, option3, "(뒤로 가려면 아무 키나 누르세요.)" };

	cursorPosition.X = 26;
	cursorPosition.Y = 16;

	for (int i = 0; i < 5; i++) {
		SetConsoleCursorPosition(console, cursorPosition);
		printf("%s\n", user_info_list[i]);
		cursorPosition.Y += 2;
	}
}