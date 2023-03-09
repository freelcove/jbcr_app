#include "globals.h"
#include "questions.h"

HANDLE console = NULL;
COORD cursorPosition = { 0, 0 };

int font_size = 25;
int current_menu_item = 0;
int current_option_item = 0;

char key_pressed = ' ';
int num_objective_questions = 0;
int num_subjective_questions = 0;
int interval_failed_questions = 10;
ObjectiveQuestion* objective_questions = NULL;
SubjectiveQuestion* subjective_questions = NULL;
int color_mode = 0;

int color_mode_preset[] = {  240, 143, 176, 225 };


void init_globals() {
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    
}