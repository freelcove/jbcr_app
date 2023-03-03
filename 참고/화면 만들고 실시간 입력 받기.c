#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24

// Function to clear the console screen
void clear_screen() {

    COORD cursor_pos = {0, 0};
    DWORD chars_written;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD console_size;

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    // Hide the cursor
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(console, &cursor_info);
    cursor_info.bVisible = FALSE;
    SetConsoleCursorInfo(console, &cursor_info);

    // Get the number of characters in the current buffer
    GetConsoleScreenBufferInfo(console, &csbi);
    console_size = csbi.dwSize.X * csbi.dwSize.Y;

    // Set the entire buffer to spaces with the current attributes
    FillConsoleOutputCharacter(console, TEXT(' '), console_size, cursor_pos, &chars_written);

    // Reset the cursor position to the top-left corner of the buffer
    SetConsoleCursorPosition(console, cursor_pos);
}

// Function to draw the screen
void draw_screen(int x, int y) {
    int i, j;

    // Clear the console screen
    clear_screen();

    // Draw the screen contents
    for (i = 0; i < SCREEN_HEIGHT; i++) {
        for (j = 0; j < SCREEN_WIDTH; j++) {
            if (i == y && j == x) {
                printf("@");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main() {
    int x = 0, y = 0;
    char input;

    // Draw the initial screen
    draw_screen(x, y);

    // Wait for user input and update the screen accordingly
    while (1) {
        input = getch();
        if (input == 'w') {
            y--;
        }
        else if (input == 'a') {
            x--;
        }
        else if (input == 's') {
            y++;
        }
        else if (input == 'd') {
            x++;
        }
        else if (input == 'q') {
            break; // Quit the program when 'q' is pressed
        }

        // Clamp the player's position to within the screen bounds
        x = (x + SCREEN_WIDTH) % SCREEN_WIDTH;
        y = (y + SCREEN_HEIGHT) % SCREEN_HEIGHT;

        // Redraw the screen
        draw_screen(x, y);
    }

    return 0;
}
