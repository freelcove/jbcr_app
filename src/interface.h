#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#ifndef INTERFACE_H
#define INTERFACE_H

//�ܼ�â ������ �� ȭ������
void ClearScreen();

//�ܼ� â �����̴� Ŀ�� �Ѱ� ���� (parameter 1: ����, 0: �� ����.)
void SetCursorVisibility(int visible);

//�ܼ� ȭ�� Initialization.
void InitScreen();


#endif