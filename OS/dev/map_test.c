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

/**
 *
 * Map test:
 *
 * 1 => insert
 * 2 => delete
 * 3 => find
 * 4 => size
 *
*/

int map_test(int _cases) {
    int c = _cases;

    struct Map* map = malloc(sizeof(struct Map));
    map_init(map);

    while (c--) {
        int type;

        scanf("%d", &type);

        switch (type) {
        case 1: // insert 
        {
            int index, value;
            scanf("%d %d", &index, &value);
            map_insert_at(map, index, value);

            break;
        }
        case 2:  // delete
        {
            int index;
            scanf("%d", &index);
            map_delete_at(map, index);

            break;
        }
        case 3: {
            int index;
            scanf("%d", &index);
            int value = map_find_at(map, index);

            printf("at: %d  value: %d\n", index, value);

            break;
        }
        case 4: {
            int size = map_size(map);
            printf("size: %d\n", size);

            break;
        }

        default: {
            break;
        }
        };

    }
}

int main(int argc, char* argv[]) {
    map_test(15);
}