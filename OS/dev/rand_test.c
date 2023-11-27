#include <stdio.h>
#include "rand_gen.h"

void rand_cases(int seed, char* outputfile) {
    set_seed(seed);
    freopen(outputfile, "w", stdout);

    // printf("seed: %d\n", seed);

    for (int i = 0; i < 1000; i++) {
        printf("%d\n", rand());
    }

    printf("\n");
}

int main(int argc, char* argv[]) {
    for (int i = 0; i< 10;i++) {
        char outputfile[100];
        sprintf(outputfile, "./traces/rand_test_%d.txt", i);
        rand_cases(i, outputfile);
    }
}