#include "global.h"
#include "org_memory.h"

// char => to bits 
void __load_char_as_bits(char c, char* out) {
    int g = c;
    for (int i = 0; i < 8;i++) {
        out[i] = (g & 1) + '0';
        g >>= 1;
    }
}

char mread_char(int addr) {
    return memory[addr];
}

void mwrite(char c, int addr) {
    memory[addr] = c;
}

/**
 * @brief initialize the memory. just create a memory file filled with zeroes
 *
*/
void minit() {
    for (int i = 0;i < MEMORY_SIZE;i++) {
        memory[i] = 0;
    }
}

