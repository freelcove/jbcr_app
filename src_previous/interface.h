#pragma once
#include "globals.h"

#ifndef INTERFACE_H
#define INTERFACE_H

//�ܼ�â ������ �� ȭ������
void ClearScreen();

//�ܼ� â �����̴� Ŀ�� �Ѱ� ���� (parameter 1: ����, 0: �� ����.)
void SetCursorVisibility(int visible);

//��Ʈ ������ ����
void set_console_font_size(int size);


//�ܼ�â �����ʿ� ��ũ�ѹٸ� ���ֱ� ���ؼ� ��ũ�� ���� ����� ����
void fit_console_screen_buffer_size();

// �÷� �ٲٱ�
void set_color_theme(int color_mode);

//�ܼ� ȭ�� Initialization.
void InitScreen();

//draw ���� �޴� ȭ�� 
void draw_menu();

//Ÿ��Ʋ �׸���
void draw_title();




#endif

