#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* some = "some people are not boys\n";
    char* filename = "meses.txt";
    FILE* file = fopen(filename, "w");
    int code = fwrite(some, sizeof(char), strlen(some), file);
    if (code == EOF) {
        printf("%s", "FK!");
    }

    char memory[3];
    memory[0] = 0;
    memory[1] = 1;
    memory[2] = 2;

    for (int i = 0;i < 3;i++) {
        char temp[8];
        for (int j = 0;j < 8;j++) {
            if ((memory[i] >> j) & 1) {
                temp[7 - j] = '1';
            }
            else {
                temp[7 - j] = '0';
            }
        }
        fwrite(temp, sizeof(char), strlen(temp), file);
        char* newline = "\n";
        fwrite(newline, sizeof(char), strlen(newline), file);
    }

    fclose(file);
}