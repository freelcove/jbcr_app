#pragma once
#include "globals.h"

#ifndef INTERFACE_H
#define INTERFACE_H

// �ܼ�â ������ �� ȭ������
void clearScreen();

// �ܼ� â �����̴� Ŀ�� �Ѱ� ���� (parameter 1: ����, 0: �� ����.)
void SetCursorVisibility(int visible);

// ��Ʈ ������ ����
void set_console_font_size(int size);

// �ܼ�â �����ʿ� ��ũ�ѹٸ� ���ֱ� ���ؼ� ��ũ�� ���� ����� ����
void fit_console_screen_buffer_size();

// �÷� �ٲٱ�
void set_color_theme(int color_mode);

// �ܼ� ȭ�� Initialization.
void initScreen();

// Menu �׸���
void drawMenu();

// ���θ޴� ��Ʈ��
int processUserInput(int num_menu_items);

// Ÿ��Ʋ �׸���
void drawTitle();

void controlMainMenu(int input);

void controlOptions(int input);
void controlInfo(int input);

#endif
