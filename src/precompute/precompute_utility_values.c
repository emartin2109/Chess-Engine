#include "global.h"
#include "utils.h"

void precompute_power()
{
    for (int i = 0; i < 64; i++) {
        precomputed_values.power[i] = power(2, i);
    }
}

void precompute_filter()
{
    precomputed_values.filter_upper_piecies = 0;
    precomputed_values.filter_lower_piecies = 0;
    for (int i = 0; i < 64; i++) {
        if (i < 32) precomputed_values.filter_upper_piecies += power(2, i);
        else precomputed_values.filter_lower_piecies += power(2, i);
        if (i < 8) precomputed_values.filter_everything_exept_lowest_rank += power(2, i);
    }
}