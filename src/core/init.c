/**
 * Initialize the kernel.
*/

#ifndef INIT_H
#define INIT_H

#include <stdint.h>
#include <stdbool.h>

#include "global.h"
#include "memory.c"
#include "register.c"

void init_memory()
{
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        mwrite(0, i);
    }
}


#endif