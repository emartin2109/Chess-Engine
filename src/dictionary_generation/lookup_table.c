#include "global.h"
#include "utils.h"
#include "generate_moves.h"
#include "global.h"

void generate_lookup_mask(void)
{
    recursive_params_t recursive_params;

    recursive_params.actual_white_turn = true;
    recursive_params.allies = 0;
    recursive_params.enemies = 0;

    for (int i = 0; i < 64; i++) {
        moves_t moves = generate_sliding_moves(precomputed_values.power[i], false, true, &recursive_params);
        printf("index = %d\n", i);
        print_bitboard(moves.moves);
    }
}

void generate_rook_lookup_table(void)
{
    recursive_params_t recursive_params;

    lookup_table_rook = malloc(64 * sizeof(long long unsigned int));
    int indexes[64];
    for (int i = 0; i < 64; i++) {
        unsigned long long int max_index_in_lookup = 0;
        recursive_params.enemies = 0;
        recursive_params.allies = 0;
        lookup_table_rook[i] = NULL;
        int number_of_ones = 0;
    
        moves_t moves = generate_sliding_moves(precomputed_values.power[i], false, true, &recursive_params);
    
        long long unsigned int mask = moves.moves;
        if (precomputed_values.power[i] & precomputed_values.filter_edge_up) mask &= precomputed_values.filter_edge_up;
        if (precomputed_values.power[i] & precomputed_values.filter_edge_down) mask &= precomputed_values.filter_edge_down;
        if (precomputed_values.power[i] & precomputed_values.filter_edge_right) mask &= precomputed_values.filter_edge_right;
        if (precomputed_values.power[i] & precomputed_values.filter_edge_left) mask &= precomputed_values.filter_edge_left;
        long long unsigned int temp_mask = mask;
        rook_mask[i] = mask;

        while (temp_mask) {
            int index_of_first_one = __builtin_ffsll(temp_mask) - 1;
            temp_mask -= precomputed_values.power[index_of_first_one];
            indexes[number_of_ones] = index_of_first_one;
            number_of_ones++;
        }

        int nbr_of_patterns = 1 << number_of_ones;

        for (int pattern_index = 0; pattern_index < nbr_of_patterns; pattern_index++) {
            long long unsigned int move = 0;
            recursive_params.enemies = 0;
            for (int bit_index = 0; bit_index < number_of_ones; bit_index++) {
                int bit = (pattern_index >> bit_index) & 1;
                move |= (unsigned long long int)bit << indexes[bit_index];
            }
            // print_bitboard(generate_sliding_moves(precomputed_values.power[i], false, true, &recursive_params).moves);
            // printf("\n");
            unsigned long long int index_in_lookup = (move * RookMagics[i]) >> RookShifts[i];
            if (index_in_lookup >= max_index_in_lookup) {
                max_index_in_lookup = index_in_lookup;
                lookup_table_rook[i] = realloc(lookup_table_rook[i], (max_index_in_lookup + 1) * sizeof(long long unsigned int));
            }
            recursive_params.enemies = move;
            moves = generate_sliding_moves(precomputed_values.power[i], false, true, &recursive_params);
            lookup_table_rook[i][index_in_lookup] = moves.moves | moves.captures;
        }
    }
}