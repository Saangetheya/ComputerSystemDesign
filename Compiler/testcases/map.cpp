int _INTERNAL_MAP_SIZE;

struct Map
{
  int _map[_INTERNAL_MAP_SIZE];
  int _size;
};

int map_init(struct Map *map)
{
  if (map == NULL)
  {
    return 0;
  }
  int i;
  for (i = 0; i < _INTERNAL_MAP_SIZE; i++)
  {
    map->_map[i] = -1;
  }

  map->_size = 0;
  return 1;
}

int map_insert_at(struct Map *map, int index, int value)
{
  if (map == NULL)
  {
    return 1;
  }

  if (index < 0 || index >= _INTERNAL_MAP_SIZE)
  {
    return 1;
  }

  int prev;
  prev = map->_map[index];
  map->_map[index] = value;
  if (prev == -1)
  {
    map->_size++;
  }

  return 0;
}

int map_find_at(struct Map *map, int index)
{
  if (map == NULL)
  {
    return -1;
  }

  if (index < 0 || index >= _INTERNAL_MAP_SIZE)
  {
    return -1;
  }

  return map->_map[index];
}

int map_delete_at(struct Map *map, int index)
{
  if (map == NULL)
  {
    return -1;
  }

  if (index < 0 || index >= _INTERNAL_MAP_SIZE)
  {
    return 1;
  }

  int prev;
  prev = map->_map[index];
  map->_map[index] = -1;

  if (prev != -1)
  {
    map->_size--;
  }
  return 0;
}

int map_size(struct Map *map)
{
  if (map == NULL)
  {
    return 1;
  }

  return map->_size;
}

int map_capacity()
{
  return _INTERNAL_MAP_SIZE;
}

int print_map(struct Map *map)
{
  int index;
  for (index = 0; index < _INTERNAL_MAP_SIZE; index++)
  {
    // print("index: %d value: %d\n", index, map->_map[index]);
  }
  return 1;
}
