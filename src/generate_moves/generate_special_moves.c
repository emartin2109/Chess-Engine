#include "include.h"
#include "struct.h"
#include "global.h"
#include "utils.h"

void genearte_pawn_double_moves (long long unsigned int move, long long unsigned int allies, long long unsigned int enemies ,moves_t *already_generated_moves)
{
    if (!(move & (allies | enemies))) {
        already_generated_moves[0].moves += move;
        global_fen_meta_data.en_passant += move;
    }
}

void generate_en_passant_moves_white (long long unsigned int pawn, int piece_nbr, moves_t *already_generated_moves)
{
    if (precomputed_values.power[piece_nbr + 1] & global_fen_meta_data.en_passant) {
        if (precomputed_values.distances[piece_nbr].east && !(precomputed_values.power[piece_nbr + 9] & (global_bitboards.black_pieces | global_bitboards.white_pieces))) {
            already_generated_moves->captures += precomputed_values.power[piece_nbr + 9];
            already_generated_moves->en_passant += pawn >> 32;
        }
    }
    if (precomputed_values.power[piece_nbr - 1] & global_fen_meta_data.en_passant) {
        if (precomputed_values.distances[piece_nbr].west && !(precomputed_values.power[piece_nbr + 7] & (global_bitboards.black_pieces | global_bitboards.white_pieces))) {
            already_generated_moves->captures += precomputed_values.power[piece_nbr + 7];
            already_generated_moves->en_passant += pawn >> 32;
        }
    }
}

void generate_en_passant_moves_black (long long unsigned int pawn, int piece_nbr, moves_t *already_generated_moves)
{
    if (precomputed_values.power[piece_nbr - 1] & global_fen_meta_data.en_passant) {
        if (precomputed_values.distances[piece_nbr].west && !(precomputed_values.power[piece_nbr - 9] & (global_bitboards.black_pieces | global_bitboards.white_pieces))) {
            already_generated_moves->captures += precomputed_values.power[piece_nbr - 9];
            already_generated_moves->en_passant += pawn >> 24;
        }
    }
    if (precomputed_values.power[piece_nbr + 1] & global_fen_meta_data.en_passant) {
        if (precomputed_values.distances[piece_nbr].east && !(precomputed_values.power[piece_nbr - 7] & (global_bitboards.black_pieces | global_bitboards.white_pieces))) {
            already_generated_moves->captures += precomputed_values.power[piece_nbr - 7];
            already_generated_moves->en_passant += pawn >> 24;
        }
    }
}

void generate_castle (int piece_nbr, moves_t *already_generated_moves)
{
    if (piece_nbr == 3) {
        if (global_bitboards.rook & precomputed_values.power[7]) {
            if (!((global_bitboards.white_pieces | global_bitboards.black_pieces) & precomputed_values.power[2]) && !((global_bitboards.white_pieces | global_bitboards.black_pieces) & precomputed_values.power[1])) {
                if (global_fen_meta_data.castle_right & precomputed_values.power[1]) {
                    already_generated_moves->moves += precomputed_values.power[0];
                }
            }
        }
        if (global_bitboards.rook & precomputed_values.power[0]) {
            if (!((global_bitboards.white_pieces | global_bitboards.black_pieces) & precomputed_values.power[4]) && !((global_bitboards.white_pieces | global_bitboards.black_pieces) & precomputed_values.power[5]) && !((global_bitboards.white_pieces | global_bitboards.black_pieces) & precomputed_values.power[6])) {
                if (global_fen_meta_data.castle_right & precomputed_values.power[0]) {
                    already_generated_moves->moves += precomputed_values.power[7];
                }
            }
        }
    }
    if (piece_nbr == 59) {
        if (global_bitboards.rook & precomputed_values.power[56]) {
            if (!((global_bitboards.white_pieces | global_bitboards.black_pieces) & precomputed_values.power[57]) && !((global_bitboards.white_pieces | global_bitboards.black_pieces) & precomputed_values.power[58])) {
                if (global_fen_meta_data.castle_right & precomputed_values.power[3]) {
                    already_generated_moves->moves += precomputed_values.power[56];
                }
            }
        }
        if (global_bitboards.rook & precomputed_values.power[63]) {
            if (!((global_bitboards.white_pieces | global_bitboards.black_pieces) & precomputed_values.power[62]) && !((global_bitboards.white_pieces | global_bitboards.black_pieces) & precomputed_values.power[61]) && !((global_bitboards.white_pieces | global_bitboards.black_pieces) & precomputed_values.power[60])) {
                if (global_fen_meta_data.castle_right & precomputed_values.power[2]) {
                    already_generated_moves->moves += precomputed_values.power[63];
                }
            }
        }
    }

}