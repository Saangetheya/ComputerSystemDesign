#include "map.h"

#include <stdio.h>

void map_init(struct Map* map) {

    if (map == 0) return;

    for (int i = 0;i < _INTERNAL_MAP_SIZE;i++) {
        map->_map[i] = -1;
    }

    map->_size = 0;
}

int map_insert_at(struct Map* map, int index, int value) {
    if (map == 0) return 1;

    if (index < 0 || index >= _INTERNAL_MAP_SIZE) {
        return 1;
    }

    int prev = map->_map[index];
    map->_map[index] = value;
    if (prev == -1) map->_size++;

    return 0;
}
/**
 * \brief to find value at index
 * \note returns >=0 value if no error , else it returns -1
*/
int map_find_at(struct Map* map, int index) {
    if (map == 0) return -1;

    if (index < 0 || index >= _INTERNAL_MAP_SIZE) {
        return -1;
    }

    return map->_map[index];
}

int  map_delete_at(struct Map* map, int index) {
    if (map == 0) return 1;

    if (index < 0 || index >= _INTERNAL_MAP_SIZE) {
        return 1;
    }

    int prev = map->_map[index];
    map->_map[index] = -1;

    if (prev != -1) map->_size--;
    return 0;
}

int map_size(struct Map* map) {
    if (map == 0) return 1;

    return map->_size;
}

int map_capacity() {
    return _INTERNAL_MAP_SIZE;
}

void print_map(struct Map* map) {
    for (int index = 0;index < _INTERNAL_MAP_SIZE; index++) {
        printf("index: %d value: %d\n", index, map->_map[index]);
    }
}