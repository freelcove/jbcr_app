#pragma once

#ifndef GLOBALS_H
#define GLOBALS_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mbstring.h>
#include <time.h>
#include "questions.h"

#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 30

extern COORD cursorPosition;

extern int current_menu_item;

extern HANDLE console;

extern int num_objective_questions;

extern int num_subjective_questions;

extern char key_pressed;

extern ObjectiveQuestion* objective_questions;

#endif // GLOBALS_H