#pragma once
#include "globals.h"

char changedanswer();
void optionchange(ObjectiveQuestion* questions, int id);
void Percentage(int num);
void print_change_row(char* sentence);
int select_color(int choice);
void print_objective_question(ObjectiveQuestion* questions, int id, int choice);
void option_select(ObjectiveQuestion* questions, int id);
int select_by_arrow(ObjectiveQuestion* questions, int id);
void exit_menu(int solved_questions);
void all_process_objective(ObjectiveQuestion* objective_questions, struct Queue* queue_objective);
