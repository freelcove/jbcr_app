#include "globals.h"

HANDLE console = NULL;
COORD cursorPosition = { 0, 0 };
int current_menu_item = 0;
char key_pressed = ' ';

void init_globals() {
    console = GetStdHandle(STD_OUTPUT_HANDLE);
}
