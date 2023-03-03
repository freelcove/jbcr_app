#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#ifndef INTERFACE_H
#define INTERFACE_H

//콘솔창 깨끗이 빈 화면으로
void ClearScreen();

//콘솔 창 깜빡이는 커서 켜고 끄기 (parameter 1: 보임, 0: 안 보임.)
void SetCursorVisibility(int visible);

#endif