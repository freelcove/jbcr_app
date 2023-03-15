#pragma once
#include "globals.h"

#ifndef MATCH_H
#define MATCH_H

int match(char* user_answer, char* subjective_questions);
int check_subjective_correction(SubjectiveQuestion* subjective_questions, int id, struct Queue* queue_subjective);
void all_process_subjective(SubjectiveQuestion* subjective_questions, struct Queue* queue_subjective);

#endif
