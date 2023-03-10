#include "globals.h"
#include "questions.h"

HANDLE console = NULL;
COORD cursorPosition = { 0, 0 };

int font_size = 25;
int current_menu_item = 0;
int current_option_item = 0;

int app_started = 0;

int best_streak;
int current_streak;

int total_tried_objective;
int total_right_objective;

int total_tried_subjective;
int total_right_subjective;

char key_pressed = ' ';
int num_objective_questions = 0;
int num_subjective_questions = 0;

int interval_failed_questions = 10;
ObjectiveQuestion* objective_questions = NULL;
SubjectiveQuestion* subjective_questions = NULL;

int color_mode = 0;
int color_mode_preset[] = { 240, 143, 176, 225 };

char user_name[50];

void init_globals() {
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    strcpy(user_name, "guest");
}