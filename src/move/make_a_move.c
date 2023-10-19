#include "move.h"
#include "generate_moves.h"
#include "global.h"
#include "utils.h"
#include "test.h"

recursive_params_t make_move(long long unsigned int start, long long unsigned int dest, recursive_params_t recursive_params)
{
    if (dest & recursive_params.local_bitboard_king) recursive_params.local_bitboard_king = update_bitboard_king(recursive_params.local_bitboard_king, start, dest, &recursive_params);
    else if (dest & recursive_params.local_bitboard_pawn) recursive_params.local_bitboard_pawn = update_bitboard_pawn(recursive_params.local_bitboard_pawn, start, dest, &recursive_params);
    else if (dest & recursive_params.local_bitboard_rook) recursive_params.local_bitboard_rook = update_bitboard(recursive_params.local_bitboard_rook, start, dest, &recursive_params);
    else if (dest & recursive_params.local_bitboard_knight) recursive_params.local_bitboard_knight = update_bitboard(recursive_params.local_bitboard_knight, start, dest, &recursive_params);
    else if (dest & recursive_params.local_bitboard_bishop) recursive_params.local_bitboard_bishop = update_bitboard(recursive_params.local_bitboard_bishop, start, dest, &recursive_params);
    else if (dest & recursive_params.local_bitboard_queen) recursive_params.local_bitboard_queen = update_bitboard(recursive_params.local_bitboard_queen, start, dest, &recursive_params);

    if (start & recursive_params.local_bitboard_king) recursive_params.local_bitboard_king = update_bitboard_king(recursive_params.local_bitboard_king, start, dest, &recursive_params);
    else if (start & recursive_params.local_bitboard_pawn) recursive_params.local_bitboard_pawn = update_bitboard_pawn(recursive_params.local_bitboard_pawn, start, dest, &recursive_params);
    else if (start & recursive_params.local_bitboard_rook) recursive_params.local_bitboard_rook = update_bitboard(recursive_params.local_bitboard_rook, start, dest, &recursive_params);
    else if (start & recursive_params.local_bitboard_knight) recursive_params.local_bitboard_knight = update_bitboard(recursive_params.local_bitboard_knight, start, dest, &recursive_params);
    else if (start & recursive_params.local_bitboard_bishop) recursive_params.local_bitboard_bishop = update_bitboard(recursive_params.local_bitboard_bishop, start, dest, &recursive_params);
    else if (start & recursive_params.local_bitboard_queen) recursive_params.local_bitboard_queen = update_bitboard(recursive_params.local_bitboard_queen, start, dest, &recursive_params);

    return recursive_params;
}

recursive_params_t make_move_ia(recursive_params_t recursive_params)
{
    recursive_params_t move_list[218];
    int number_of_moves = 0;
    long long unsigned int temp_allies = (recursive_params.allies | recursive_params.local_bitboard_king) ^ recursive_params.local_bitboard_king;

    if (!(recursive_params.local_bitboard_king & recursive_params.allies) || !(recursive_params.local_bitboard_king & recursive_params.enemies)) {
        recursive_params = get_recursive_params_glo();
        return recursive_params;
    }

    while (temp_allies != 0) {
        int a_index = __builtin_ffsll(temp_allies) - 1;
        temp_allies -= precomputed_values.power[a_index];

        moves_t current_moves = get_action_from_bitboard(precomputed_values.power[a_index], &recursive_params);
        long long unsigned int moves = current_moves.moves | current_moves.captures;

        while (moves != 0) {
            int m_index = __builtin_ffsll(moves) - 1;
            moves -= precomputed_values.power[m_index];
            if (m_index < 56 && m_index > 7) move_list[number_of_moves++] = make_move(precomputed_values.power[a_index], precomputed_values.power[m_index], recursive_params);
        }
    }

    int k_index = __builtin_ffsl(recursive_params.local_bitboard_king & recursive_params.allies) - 1;
    current_moves = generate_king_moves (precomputed_values.power[k_index], &recursive_params);
    long long unsigned int moves = current_moves.moves | current_moves.captures;

    while (moves != 0) {
        int m_index = __builtin_ffsll(moves) - 1;
        moves -= precomputed_values.power[m_index];
        if (m_index < 56 && m_index > 7) {
            move_list[number_of_moves++] = make_move(precomputed_values.power[k_index], precomputed_values.power[m_index], recursive_params);
        }
    }

    if (number_of_moves == 0) return (recursive_params);

    int move = rand() % number_of_moves;

    recursive_params_t result = prepare_recursive_params(move_list[move]);
    return result;


}