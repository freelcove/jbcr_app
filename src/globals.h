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
#include "interface.h"
#include "print.h"

#include "comment.h"
#include "utilities.h"
#include "options.h"
#include "user.h"

#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 30

void init_globals();

extern int app_started;

extern char user_name[50];

extern int font_size;

//Ŀ�� ��ġ ����
extern COORD cursorPosition;

//�ܼ� ���� ����
extern HANDLE console;

//���� �޴����� ���� �޴� ������
extern int current_menu_item;

//������ ���� ����
extern int num_objective_questions;

//�ְ��� ���� ����
extern int num_subjective_questions;

//���� ������ Ű ���� ����
extern char key_pressed;

//Ʋ�� ������ �� ���� �ڿ� ������ ���ϴ� ����
extern int interval_failed_questions;

extern int rand_id[100];

extern int color_mode;

extern int color_mode_preset[];

extern int best_streak;
extern int current_streak;
extern int faltcount;
extern int changecolor[3];
extern int solved_questions;

extern int total_tried_objective;

extern int total_right_objective;

extern int total_tried_subjective;

extern int total_right_subjective;



#endif // GLOBALS_H