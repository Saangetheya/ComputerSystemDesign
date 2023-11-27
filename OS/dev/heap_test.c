#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "map.h"

/**
 * heap allocation based on linked list implementation => best fit algorithm
 * no use of internal malloc function
 *
 * assume some memory allocation
 * initialize various size blocks
 *
 * take two types of input:
 * 1 => to show the present condition of our heap
 * 2 => take another input regarding the size of the memory block to allocate, also print the unique id
 * 3 => free the memory
 * 4 => end the program
*/

void heap_test(int _cases) {
    int c = _cases;

    while (c--) {
        int type;

        printf("%d", &type);

        switch (type) {
        case 1: {
            
        }

        case 2: {

        }

        case 3: {

        }

        case 4: {

        }

        default: {

        }
        }
    }
}

int main(int argc, char* argv[]) {
    heap_test(20);
}