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
        if (i == 0 || i == 56) precomputed_values.right_corners += power(2, i);
        if (i == 7 || i == 63) precomputed_values.left_corners += power(2, i);
    }
    precomputed_values.filter_pawn_double_squares =     0b0000000000000000000000001111111111111111000000000000000000000000;
    precomputed_values.filter_pawns_strating_squares =  0b0000000011111111000000000000000000000000000000001111111100000000;
    precomputed_values.filter_edge_up =                 0b0000000011111111111111111111111111111111111111111111111111111111;
    precomputed_values.filter_edge_down =               0b1111111111111111111111111111111111111111111111111111111100000000;
    precomputed_values.filter_edge_left =               0b0111111101111111011111110111111101111111011111110111111101111111;
    precomputed_values.filter_edge_right =              0b1111111011111110111111101111111011111110111111101111111011111110;
}