#include "include.h"
#include "struct.h"
#include "global.h"
#include "utils.h"

void genearte_pawn_double_moves (long long unsigned int move, long long unsigned int single_move, recursive_params_t *recursive_params ,moves_t *already_generated_moves)
{
    if (!(move & (recursive_params->allies | recursive_params->enemies)) && !(single_move & (recursive_params->allies | recursive_params->enemies))) {
        already_generated_moves[0].moves += move;
    }
}

void generate_en_passant_moves_white (long long unsigned int pawn, int piece_nbr, moves_t *already_generated_moves, recursive_params_t *recursive_params)
{
    if (precomputed_values.power[piece_nbr + 1] & recursive_params->actual_en_passant) {
        if (precomputed_values.distances[piece_nbr].east && !(precomputed_values.power[piece_nbr + 9] & (recursive_params->local_bitboard_black | recursive_params->local_bitboard_white))) {
            already_generated_moves->captures += precomputed_values.power[piece_nbr + 9];
            already_generated_moves->en_passant += pawn >> 32;
        }
    }
    if (precomputed_values.power[piece_nbr - 1] & recursive_params->actual_en_passant) {
        if (precomputed_values.distances[piece_nbr].west && !(precomputed_values.power[piece_nbr + 7] & (recursive_params->local_bitboard_black | recursive_params->local_bitboard_white))) {
            already_generated_moves->captures += precomputed_values.power[piece_nbr + 7];
            already_generated_moves->en_passant += pawn >> 32;
        }
    }
}

void generate_en_passant_moves_black (long long unsigned int pawn, int piece_nbr, moves_t *already_generated_moves, recursive_params_t *recursive_params)
{
    if (precomputed_values.power[piece_nbr - 1] & recursive_params->actual_en_passant) {
        if (precomputed_values.distances[piece_nbr].west && !(precomputed_values.power[piece_nbr - 9] & (recursive_params->local_bitboard_black | recursive_params->local_bitboard_white))) {
            already_generated_moves->captures += precomputed_values.power[piece_nbr - 9];
            already_generated_moves->en_passant += pawn >> 24;
        }
    }
    if (precomputed_values.power[piece_nbr + 1] & recursive_params->actual_en_passant) {
        if (precomputed_values.distances[piece_nbr].east && !(precomputed_values.power[piece_nbr - 7] & (recursive_params->local_bitboard_black | recursive_params->local_bitboard_white))) {
            already_generated_moves->captures += precomputed_values.power[piece_nbr - 7];
            already_generated_moves->en_passant += pawn >> 24;
        }
    }
}

void generate_castle (int piece_nbr, moves_t *already_generated_moves, recursive_params_t *recursive_params)
{
    if (piece_nbr == 3) {
        if (global_bitboards.rook & precomputed_values.power[7]) {
            if (!((recursive_params->local_bitboard_white | recursive_params->local_bitboard_black) & precomputed_values.power[2]) && !((recursive_params->local_bitboard_white | recursive_params->local_bitboard_black) & precomputed_values.power[1])) {
                if (global_fen_meta_data.castle_right & precomputed_values.power[1]) {
                    already_generated_moves->moves += precomputed_values.power[0];
                }
            }
        }
        if (global_bitboards.rook & precomputed_values.power[0]) {
            if (!((recursive_params->local_bitboard_white | recursive_params->local_bitboard_black) & precomputed_values.power[4]) && !((recursive_params->local_bitboard_white | recursive_params->local_bitboard_black) & precomputed_values.power[5]) && !((recursive_params->local_bitboard_white | recursive_params->local_bitboard_black) & precomputed_values.power[6])) {
                if (global_fen_meta_data.castle_right & precomputed_values.power[0]) {
                    already_generated_moves->moves += precomputed_values.power[7];
                }
            }
        }
    }
    if (piece_nbr == 59) {
        if (global_bitboards.rook & precomputed_values.power[56]) {
            if (!((recursive_params->local_bitboard_white | recursive_params->local_bitboard_black) & precomputed_values.power[57]) && !((recursive_params->local_bitboard_white | recursive_params->local_bitboard_black) & precomputed_values.power[58])) {
                if (global_fen_meta_data.castle_right & precomputed_values.power[3]) {
                    already_generated_moves->moves += precomputed_values.power[56];
                }
            }
        }
        if (global_bitboards.rook & precomputed_values.power[63]) {
            if (!((recursive_params->local_bitboard_white | recursive_params->local_bitboard_black) & precomputed_values.power[62]) && !((recursive_params->local_bitboard_white | recursive_params->local_bitboard_black) & precomputed_values.power[61]) && !((recursive_params->local_bitboard_white | recursive_params->local_bitboard_black) & precomputed_values.power[60])) {
                if (global_fen_meta_data.castle_right & precomputed_values.power[2]) {
                    already_generated_moves->moves += precomputed_values.power[63];
                }
            }
        }
    }

}