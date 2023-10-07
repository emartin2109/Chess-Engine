#include "global.h"
#include "utils.h"

void precompute_power()
{
    for (int i = 0; i < 64; i++) {
        precomputed_values.power[i] = power(2, i);
    }
}