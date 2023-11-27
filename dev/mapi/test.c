#include <stdio.h>

#include <mem.c>

int main() {
    init();

    write('0', 0);
    write('1', 1);
    write('2', 2);

    // char buffer[9];
    // read(1, buffer);
    // printf("%s\n", buffer);
    // read(2, buffer);
    // printf("%s\n", buffer);
    // read(3, buffer);
    // printf("%s\n", buffer);

    write('3', 3);

    return 0;
}