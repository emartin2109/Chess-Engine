#include "generate_moves.h"
#include "define.h"
#include "board.h"
#include "global.h"
#include "move.h"
#include "utils.h"
#include "display.h"

recursive_params_t get_recursive_params_glo()
{
    recursive_params_t result;

    result.local_bitboard_white = global_bitboards.white_pieces;
    result.local_bitboard_black = global_bitboards.black_pieces;

    result.local_bitboard_rook = global_bitboards.rook;
    result.local_bitboard_knight = global_bitboards.knight;
    result.local_bitboard_bishop = global_bitboards.bishop;
    result.local_bitboard_queen = global_bitboards.queen;
    result.local_bitboard_king = global_bitboards.king;
    result.local_bitboard_pawn = global_bitboards.pawn;

    result.actual_catle_right = global_fen_meta_data.castle_right;
    result.actual_en_passant = global_fen_meta_data.en_passant;

    result.actual_white_turn = global_fen_meta_data.white_turn;

    result.attacked_square_b = 0;
    result.attacked_square_w = 0;

    if (result.actual_white_turn) {
        result.allies = result.local_bitboard_white;
        result.enemies = result.local_bitboard_black;
    } else {
        result.allies = result.local_bitboard_black;
        result.enemies = result.local_bitboard_white;
    }

    return result;
}

recursive_params_t get_recursive_params()
{
    recursive_params_t result;

    result.local_bitboard_white = recursive_params_glo.local_bitboard_white;
    result.local_bitboard_black = recursive_params_glo.local_bitboard_black;

    result.local_bitboard_rook = recursive_params_glo.local_bitboard_rook;
    result.local_bitboard_knight = recursive_params_glo.local_bitboard_knight;
    result.local_bitboard_bishop = recursive_params_glo.local_bitboard_bishop;
    result.local_bitboard_queen = recursive_params_glo.local_bitboard_queen;
    result.local_bitboard_king = recursive_params_glo.local_bitboard_king;
    result.local_bitboard_pawn = recursive_params_glo.local_bitboard_pawn;

    result.actual_catle_right = recursive_params_glo.actual_catle_right;
    result.actual_en_passant = recursive_params_glo.actual_en_passant;

    result.actual_white_turn = recursive_params_glo.actual_white_turn;

    result.attacked_square_b = 0;
    result.attacked_square_w = 0;

    if (result.actual_white_turn) {
        result.allies = result.local_bitboard_white;
        result.enemies = result.local_bitboard_black;
    } else {
        result.allies = result.local_bitboard_black;
        result.enemies = result.local_bitboard_white;
    }

    return result;
}

recursive_params_t prepare_recursive_params(recursive_params_t recursive_params)
{
    if (recursive_params.actual_white_turn) {
        recursive_params.actual_en_passant = recursive_params.actual_en_passant & precomputed_values.filter_upper_piecies;
        recursive_params.local_bitboard_white = recursive_params.allies;
        recursive_params.local_bitboard_black = recursive_params.enemies;
        recursive_params.attacked_square_b = 0;
    } else {
        recursive_params.actual_en_passant = recursive_params.actual_en_passant & precomputed_values.filter_lower_piecies;
        recursive_params.local_bitboard_black = recursive_params.allies;
        recursive_params.local_bitboard_white = recursive_params.enemies;
        recursive_params.attacked_square_w = 0;
    }
    recursive_params.actual_white_turn = !recursive_params.actual_white_turn;
    long long unsigned int temp = recursive_params.allies;
    recursive_params.allies = recursive_params.enemies;
    recursive_params.enemies = temp;

    return recursive_params;
}

long long unsigned int count_moves_at_depth (int depth, recursive_params_t recursive_params)
{

    long long unsigned int result = 0;
    long long unsigned int temp_allies = (recursive_params.allies | recursive_params.local_bitboard_king) ^ recursive_params.local_bitboard_king;

    if (depth >= MAX_DEPTH) return 1;

    result = 0;

    while (temp_allies != 0) {
        int a_index = __builtin_ffsll(temp_allies) - 1;
        temp_allies -= precomputed_values.power[a_index];
        current_moves = get_action_from_bitboard(precomputed_values.power[a_index], &recursive_params);
        long long unsigned int moves = current_moves.moves | current_moves.captures;
        while (moves != 0) {
            int m_index = __builtin_ffsll(moves) - 1;
            moves -= precomputed_values.power[m_index];
            recursive_params_t temp_recursive = make_move(precomputed_values.power[a_index], precomputed_values.power[m_index], recursive_params);
            long long unsigned int temp_result = result;
            result += count_moves_at_depth(depth + 1, prepare_recursive_params(temp_recursive));
            if (depth == 0) {
                // recursive_params_glo = temp_recursive;
                // display();
                printf("%c%d%c%d: %llu\n", 'h' - a_index%8, a_index/8 + 1, 'h' - m_index%8, m_index/8 + 1, result - temp_result);
            }
        }
    }

    int k_index = __builtin_ffsl(recursive_params.local_bitboard_king & recursive_params.allies);
    current_moves = generate_king_moves (precomputed_values.power[k_index], &recursive_params);
    long long unsigned int moves = current_moves.moves | current_moves.captures;
    while (moves != 0) {
        int m_index = __builtin_ffsll(moves) - 1;
        moves -= precomputed_values.power[m_index];
        recursive_params_t temp_recursive = make_move(precomputed_values.power[k_index], precomputed_values.power[m_index], recursive_params);
        result += count_moves_at_depth(depth + 1, prepare_recursive_params(temp_recursive));
    }

    return result;
}

void run_test_move_nbr(unsigned char key, int x, int y)
{
    key = key;
    x = x;
    y = y;
    printf("%llu\n", count_moves_at_depth(0, get_recursive_params()));
    create_board(START_POS);
    recursive_params_glo = get_recursive_params();
}