#pragma once

#ifndef GLOBALS_H
#define GLOBALS_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mbstring.h>
#include <time.h>
#include <conio.h>

#include "questions.h"
#include "queue.h"
#include "print.h"
#include "interface.h"
#include "utilities.h"

#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 30

void initGlobals();

// 콘솔 관련
extern HANDLE console;
extern COORD cursorPosition;

// 옵션 관련
extern int font_size;
extern int color_mode;
extern int color_mode_preset[];
extern int interval_failed_questions;

// 인터페이스 관련
extern int current_menu;
extern int current_mode;
extern char key_pressed;

// 문제 관련
extern int num_objective_questions;
extern int num_subjective_questions;
extern int check_subjective;
extern char user_answer[MAX_LINE_LENGTH];
extern int rand_id[100];
extern int faltcount;
extern int changecolor[3];
extern int solved_questions;

// 기록 관련
extern int best_streak_objective;
extern int current_streak_objective;
extern int best_streak_subjective;
extern int current_streak_subjective;
extern int total_tried_objective;
extern int total_right_objective;
extern int total_tried_subjective;
extern int total_right_subjective;

#endif // GLOBALS_H