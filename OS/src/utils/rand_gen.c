#include <stdint.h>

int rand_lfsr;
int rand_bit;

int rand_engine = 0xACE1u;

void set_seed(int seed) {
    rand_engine = (((seed | rand_engine) * 7621) + 1) % 32768;
    rand_lfsr = rand_engine;
}

int own_rand() {
    rand_bit = ((rand_lfsr >> 0) ^ (rand_lfsr >> 2) ^ (rand_lfsr >> 3) ^ (rand_lfsr >> 5)) & 1;
    rand_lfsr = (rand_lfsr >> 1) | (rand_bit << 15);

    return rand_lfsr % 100;
}