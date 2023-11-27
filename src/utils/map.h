#ifndef INTERNAL_MAP
#define INTERNAL_MAP

#define _INTERNAL_MAP_SIZE 30

struct Map {
    int _map[_INTERNAL_MAP_SIZE];
    int _size;
};

void map_init(struct Map* map);
int map_insert_at(struct Map* map, int index, int value);
int map_find_at(struct Map* map, int index);
int  map_delete_at(struct Map* map, int index);
int map_size(struct Map* map);
int map_capacity();


#endif 