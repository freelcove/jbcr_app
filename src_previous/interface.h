#pragma once
#include "globals.h"

#ifndef INTERFACE_H
#define INTERFACE_H

//콘솔창 깨끗이 빈 화면으로
void ClearScreen();

//콘솔 창 깜빡이는 커서 켜고 끄기 (parameter 1: 보임, 0: 안 보임.)
void SetCursorVisibility(int visible);

//폰트 사이즈 조정
void set_console_font_size(int size);


//콘솔창 오른쪽에 스크롤바를 없애기 위해서 스크린 버퍼 사이즈를 조정
void fit_console_screen_buffer_size();

// 컬러 바꾸기
void set_color_theme(int color_mode);

//콘솔 화면 Initialization.
void InitScreen();

//draw 메인 메뉴 화면 
void draw_menu();

//타이틀 그리기
void draw_title();




#endif

