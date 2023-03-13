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
#include "convert.h"
#include "filecontrol.h"
#include "comment.h"
#include "utilities.h"



#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 30

void init_globals();


extern char user_name[50];

extern int font_size;

//커서 위치 관련
extern COORD cursorPosition;

//콘솔 조작 관련
extern HANDLE console;

//메인 메뉴에서 현재 메뉴 아이템
extern int app_menu_item;
extern char app_mode[20];
extern char app_input;

//객관식 문제 개수
extern int num_objective_questions;

//주관식 문제 개수
extern int num_subjective_questions;

//현재 눌러진 키 저장 변수


//틀린 문제가 몇 문제 뒤에 나올지 정하는 변수
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