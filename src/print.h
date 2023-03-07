#pragma once
#include "globals.h"
#include"questions.h"
#include"interface.h"

void printquestion(ObjectiveQuestion* questions, int id);
void changerow1(ObjectiveQuestion* questions, int id);
void changerow2(ObjectiveQuestion* questions, int id);
void printoptions(ObjectiveQuestion* questions, int id);
int bool();
void repeatquestions(ObjectiveQuestion* questions, int bool);
int randnum();
