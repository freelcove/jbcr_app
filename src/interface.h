#pragma once
#include "globals.h"

#ifndef INTERFACE_H
#define INTERFACE_H

// 콘솔창 깨끗이 빈 화면으로
void clearScreen();

// 콘솔 창 깜빡이는 커서 켜고 끄기 (parameter 1: 보임, 0: 안 보임.)
void SetCursorVisibility(int visible);

// 폰트 사이즈 조정
void set_console_font_size(int size);

// 콘솔창 오른쪽에 스크롤바를 없애기 위해서 스크린 버퍼 사이즈를 조정
void fit_console_screen_buffer_size();

// 컬러 바꾸기
void set_color_theme(int color_mode);

// 콘솔 화면 Initialization.
void initScreen();

// Menu 그리기
void drawMenu();

// 메인메뉴 컨트롤
int processUserInput(int num_menu_items);

// 타이틀 그리기
void drawTitle();

void controlMainMenu(int input);

void controlOptions(int input);
void controlInfo(int input);

#endif
