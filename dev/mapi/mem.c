#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

/**
 * @brief write into file at specific col, row
 *  read from file at specific row, col
*/

char* filename = "memory.txt";
#define MEMORY_SIZE 16000

FILE* fp;

// char => to bits 
void __load_char_as_bits(char c, char* out) {
    int g = c;
    for (int i = 0; i < 8;i++) {
        out[7 - i] = (g & 1) + '0';
        g >>= 1;
    }
}

// read a single character from file
// note: the file is a text file, so we need to convert the char to bits in out
void read(int addr, char* out) {

    assert(addr >= 0 && addr < MEMORY_SIZE);
    fseek(fp, addr * 9, SEEK_SET);
    fread(out, sizeof(char), 9, fp);

    // assert(out[8] == '\n');
}

char read_char(int addr) {
    char out[9];
    read(addr, out);

    char g;
    for (int i = 0;i < 8;i++) {
        g <<= 1;
        g |= out[i] - '0';
    }

    return g;
}

void write(char c, int addr) {
    assert(addr >= 0 && addr < MEMORY_SIZE);  // check if addr is valid
    fseek(fp, addr * 9, SEEK_SET);
    char line[9];
    line[8] = '\n';
    __load_char_as_bits(c, line);
    fwrite(line, sizeof(char), 9, fp);
    fflush(fp);
}

/**
 * @brief initialize the memory. just create a memory file filled with zeroes
 *
*/
void init() {

    fp = fopen(filename, "rw+");
    for (int i = 0;i < MEMORY_SIZE;i++) {
        char line[9];
        line[8] = '\n';
        __load_char_as_bits(0, line);

        fwrite(line, sizeof(char), 9, fp);
    }
}
