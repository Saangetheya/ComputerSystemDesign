/**
 * Keyboard driver: Keyboard driver for the OS has only  one function,
 * that is to get the input from the keyboard.
 *
 * Presently, the keyboard driver is not capable of handling meta keys like capslock, numlock, etc.
 * but it can handle ctrl, alt, shift, etc.
 *
*/

#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

#include "../core/global.h"
#include "../core/memory.h"

#define INT_END_POINT 0x2E

/**
 * \brief Initializes keyboard
*/
void keyboard_init() {
    int start = IO_KEYBOARD_START;
    int end = IO_KEYBOARD_START + IO_KEYBOARD_SIZE;
    for (int i = start;i < end;i++) {
        mwrite('\0', i);
    }
}

int keyboard_clear_input() {
    mclose();
    minit();
    mwrite(0, IO_KEYBOARD_START);
    return 0;
}

char keyboard_get_input() {
    char input = 0;
    keyboard_clear_input();

    while (true) {
        mclose();
        minit();
        char f = mread_char(IO_KEYBOARD_START);
        // printf("Keyboard input: %c\n", f);
        if (f != 0) {
            input = f;
            mwrite(0, IO_KEYBOARD_START);
            break;
        }
    }

    // minit();
    // mclose();
    return input;
}

int keyboard_get_int() {

    int ans = 0;

    while (true) {
        mclose();
        minit();

        char f = mread_char(IO_KEYBOARD_START);
        mwrite(0, IO_KEYBOARD_START);

        if (f == INT_END_POINT) {
            printf("Keyboard int end\n", 17);
            break;
        }
        else if (f != 0) {
            printf("Keyboard input: %c\n", f);
            if (f >= '0' && f <= '9') {
                ans = ans * 10 + (f - '0');
            }
            else if (f == '\b') {
                ans /= 10;
            }
            else {
                break;
            }
        }
    }

    minit();
    // mclose();
    return ans;
}

void convert_keyinput_to_string(char input, char* out) {
    switch (input) {
    case CTRL_CODE_ENTER: {
        // ENTR
        out[0] = 'E';
        out[1] = 'N';
        out[2] = 'T';
        out[3] = 'R';
    }

    case CTRL_CODE_ALT: {
        // ALT
        out[0] = 'A';
        out[1] = 'L';
        out[2] = 'T';
        out[3] = '\0';
    }

    case CTRL_CODE_SHIFT: {
        // SHFT
        out[0] = 'S';
        out[1] = 'H';
        out[2] = 'F';
        out[3] = 'T';
    }

    default: {
        out[0] = input;
        out[1] = '\0';
    }
    }
}

char manipulate_input(char c) {
    return c;
}

bool isEscape(char input) {
    return input == 0x1B;
}

#endif // KEYBOARD_DRIVER_H