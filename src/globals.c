#include "globals.h"

HANDLE console = NULL;
COORD cursorPosition = {0, 0};

int color_mode = 0;
int color_mode_preset[] = {240, 143, 176, 224};
int font_size = 25;
char key_pressed = ' ';
int interval_failed_questions = 10;

int current_menu = 0;
int current_mode = 5;

int faltcount = 0;
int solved_questions = 0;
int changecolor[3] = {0, 0, 0};
int num_objective_questions = 0;
int num_subjective_questions = 0;
int check_subjective = 0;
extern char user_answer[MAX_LINE_LENGTH] = {0};

ObjectiveQuestion *objective_questions = NULL;
SubjectiveQuestion *subjective_questions = NULL;

int best_streak = 0;
int current_streak = 0;
int total_tried_objective = 0;
int total_right_objective = 0;
int total_tried_subjective = 0;
int total_right_subjective = 0;

void initGlobals()
{
	console = GetStdHandle(STD_OUTPUT_HANDLE);
}

void clearInputBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
	{
	}
}