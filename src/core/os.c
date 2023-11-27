/**
 * OS: Operating System which can execute the a terminal based user program
 *
*/

#ifndef OS_H
#define OS_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "global.h"
#include "register.c"
#include "init.c"

#include "../faces/face_0.h"
#include "../faces/face_1.h"
#include "../faces/face_2.h"

// #include "../driver/display_driver.c"
#include "../games/tic_tac_toe.c"

void os_start() {
    // initialize the kernel
    minit();
}

// current path in the OS
char path[20];
int path_len = 0;

void snake_game() {
    clear_screen();

    write_string("Welcome to Snake Game\n\n", 23);
    write_string("Press 'w' to move up\n", 21);
    write_string("Press 'a' to move left\n", 23);
    write_string("Press 's' to move down\n", 23);
    write_string("Press 'd' to move right\n", 24);
    write_string("Press 'q' to exit game\n", 23);

    write_string("\n\n", 2);

    write_string("Press any key to start the game\n", 32);
    // char in = keyboard_get_input();

    // if (in == 'q') {
    //     return;
    // }

    clear_screen();
    write_string("Game Started\n", 13);

    int pos[2];
    int base_x, base_y;
    get_cursor_pos(pos);
    base_x = pos[0];
    base_y = pos[1];

    int width = 60;
    int height = 40;

    int score_base_x = base_x + (width - 25);
    int score_base_y = base_y + 20;

    // snake game size = height * width (200)
    int snake[height][width]; // 0: background, 1, border, 2: snake, 3: food, 4: snake head
    int snake_size = 4;
    int snake_dir = 0; // 0: east, 1: north, 2: west, 3: south
    int snake_speed = 3; // at each step, the snake moves 1 unit
    int snake_pos[2] = { 5, 5 }; // row, col relative to the top left corner (0, 0)
    int snake_food[2] = { 10, 10 }; // row, col relative to the top left corner (0, 0)

    // snake[0][0] = 0;
    // snake[0][1] = 0;

    // draw the border
    for (int i = 0;i < height;i++) {
        for (int j = 0;j < width;j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                snake[i][j] = 1;
            }
            else {
                snake[i][j] = 0;
            }
        }
    }

    set_seed(5);
    while (true) {
        // get input from keyboard
        char input = keyboard_get_input();

        if (input == 'd') {
            snake_dir = 0;
        }
        else if (input == 'w') {
            snake_dir = 1;
        }
        else if (input == 'a') {
            snake_dir = 2;
        }
        else if (input == 's') {
            snake_dir = 3;
        }
        else if (input == 'q') {
            break;
        }

        // calculate food pos using random 
        int xfood = own_rand() % width;
        int yfood = own_rand() % height;

        if (xfood == 0) {
            xfood = 1;
        }
        else if (xfood == width - 1) {
            xfood = width - 2;
        }

        if (yfood == 0) {
            yfood = 1;
        }
        else if (yfood == height - 1) {
            yfood = height - 2;
        }

        snake_food[0] = xfood;
        snake_food[1] = yfood;

        snake[snake_pos[1]][snake_pos[0]] = 2;

        // update the snake position
        if (snake_dir == 0) {
            int xold = snake_pos[0];
            int yold = snake_pos[1];

            for (int i = 0;i < snake_speed;i++) {
                xold++;
                snake[yold][xold] = 2;
                if (snake[yold][xold] == 1) {
                    break;
                }
            }

            snake_pos[0] = xold;
            snake_pos[1] = yold;
        }
        else if (snake_dir == 1) {
            snake_pos[1] -= snake_speed;
            int xold = snake_pos[0];
            int yold = snake_pos[1];

            for (int i = 0;i < snake_speed;i++) {
                yold--;
                snake[yold][xold] = 2;
                if (snake[yold][xold] == 1) {
                    break;
                }
            }

            snake_pos[0] = xold;
            snake_pos[1] = yold;
        }
        else if (snake_dir == 2) {
            int xold = snake_pos[0];
            int yold = snake_pos[1];

            for (int i = 0;i < snake_speed;i++) {
                xold--;
                snake[yold][xold] = 2;
                if (snake[yold][xold] == 1) {
                    break;
                }
            }

            snake_pos[0] = xold;
            snake_pos[1] = yold;
        }
        else if (snake_dir == 3) {
            int xo = snake_pos[0];
            int yo = snake_pos[1];

            for (int i = 0;i < snake_speed;i++) {
                yo++;
                snake[yo][xo] = 2;
                if (snake[yo][xo] == 1) {
                    break;
                }
            }

            snake_pos[0] = xo;
            snake_pos[1] = yo;
        }

        snake_size++;

        // update the snake
        snake[snake_pos[1]][snake_pos[0]] = 4;
        snake[snake_food[1]][snake_food[0]] = 3;

        // check if the snake has hit the border
        if (snake_pos[0] < 0 || snake_pos[0] >= height || snake_pos[1] < 0 || snake_pos[1] >= width) {
            break;
        }

        set_cursor_pos(base_x, base_y);

        for (int i = 0;i < height;i++) {
            for (int j = 0;j < width;j++) {
                if (snake[i][j] == 0) {
                    write_char(' ');
                }
                else if (snake[i][j] == 1) {
                    write_char('#');
                }
                else if (snake[i][j] == 2) {
                    write_char('*');
                }
                else if (snake[i][j] == 3) {
                    write_char('X');
                }
                else if (snake[i][j] == 4) {
                    write_char('O');
                }
            }
            write_char('\n');
        }

        // write score
        set_cursor_pos(score_base_y, score_base_x);
        write_string("Score: ", 7);
        write_int(snake_size);
        set_cursor_pos(base_x, base_y);
    }
}

void int_input() {
    clear_screen();
    keyboard_clear_input();

    write_string("Enter an integer: \n", 19);
    int input = keyboard_get_int();
    printf("The integer is: %d\n", input);
    write_string("The integer is: ", 16);
    write_int(input);
    write_char('\n');
}

/**
 *
 * flexos:/> [ls| cd <dir> | cat <file> | mkdir <dir> | pwd | clear | exit]
 *
 * dir1\
 *      file1
 *      file2
 * dir2\
 *      file1
 *      file2
*/

void set_path(char* new_path, int len) {
    if (len >= 20) return;

    for (int i = 0;i < len;i++) {
        path[i] = new_path[i];
    }

    path_len = len;
}

void print_new_path() {
    write_char('\n');
    write_string(path, path_len);
}

void ls_on_dir1() {
    write_string("file1 file2", 11);
}

void ls_on_dir2() {
    write_string("file1 file2", 11);
}

void cat_on_dir1_file1() {
    write_string("This is file1 content in dir1", 29);
}

void cat_on_dir1_file2() {
    write_string("This is file2 content in dir1", 29);
}

void cat_on_dir2_file1() {
    write_string("This is file1 content in dir2", 29);
}

void cat_on_dir2_file2() {
    write_string("This is file2 content in dir2", 29);
}

void clear_path() {
    for (int i = 0;i < 20;i++) {
        path[i] = '\0';
    }
}

void terminal() {
    clear_screen();
    set_path("flexos:/> ", 11);
    print_new_path();

    char preinput[20];
    int len = 0;

    while (true) {
        char input = keyboard_get_input();

        if (input == '.') {

            printf("preinput: %s\n", preinput);

            if (len == 0) {
                print_new_path();
                continue;
            }

            if (preinput[0] == 'l' && preinput[1] == 's') {
                if (len >= 7 && preinput[3] == 'd' && preinput[4] == 'i' && preinput[5] == 'r' && preinput[6] == '1') {
                    write_char('\n');
                    ls_on_dir1();

                    set_path("flexos:/> ", 11);
                    len = 0;
                    print_new_path();
                }
                else if (len >= 7 && preinput[3] == 'd' && preinput[4] == 'i' && preinput[5] == 'r' && preinput[6] == '2') {
                    write_char('\n');
                    ls_on_dir2();

                    set_path("flexos:/> ", 11);
                    len = 0;
                    print_new_path();
                }
                else {
                    write_string("\nInvalid directory\n", 19);
                }
            }
            else if (preinput[0] == 'c' && preinput[1] == 'd') {
                if (preinput[3] == 'd' && preinput[4] == 'i' && preinput[5] == 'r' && preinput[6] == '1') {
                    set_path("flexos:dir1/> ", 14);
                    print_new_path();
                    len = 0;
                }
                else if (preinput[3] == 'd' && preinput[4] == 'i' && preinput[5] == 'r' && preinput[6] == '2') {
                    set_path("flexos:dir2/> ", 14);
                    print_new_path();
                    len = 0;
                }
                else if (preinput[3] == '/') {
                    set_path("flexos:/> ", 11);
                    print_new_path();
                    len = 0;
                }
                else {
                    write_string("Invalid directory\n", 18);
                }
            }
            else if (preinput[0] == 'c' && preinput[1] == 'a' && preinput[2] == 't') {
                write_string("cat\n", 4);
            }
            else if (preinput[0] == 'm' && preinput[1] == 'k' && preinput[2] == 'd' && preinput[3] == 'i' && preinput[4] == 'r') {
                write_string("mkdir\n", 6);
            }
            else if (preinput[0] == 'p' && preinput[1] == 'w' && preinput[2] == 'd') {
                write_string("pwd\n", 4);
            }
            else if (preinput[0] == 'e' && preinput[1] == 'x' && preinput[2] == 'i' && preinput[3] == 't') {
                write_string("exit\n", 5);
                break;
            }
            else if (preinput[0] == 'c' && preinput[1] == 'l' && preinput[2] == 'e' && preinput[3] == 'a' && preinput[4] == 'r') {
                clear_screen();
                print_new_path();
            }
            else {
                write_string("\nInvalid command\n", 17);
                print_new_path();
                len = 0;
            }
        }
        else {
            preinput[len] = input;
            len++;
            write_char(input);
        }
    }

}

int main() {
    os_start();
    terminal();
    // snake_game();
    return 0;
}

#endif