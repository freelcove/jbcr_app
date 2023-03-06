#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mbstring.h>
#include <time.h>

#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 30

#pragma once

#ifndef GLOBALS_H
#define GLOBALS_H

extern COORD cursorPosition;

extern int current_menu_item;

extern HANDLE console;

extern int num_questions;

extern char key_pressed;

#endif // GLOBALS_H