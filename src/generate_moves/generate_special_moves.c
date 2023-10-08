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
            // print_bitboard(pawn >> 32);
            printf("%llu\n", pawn >> 32);
            printf("right = %d\n\n", already_generated_moves->en_passant);
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
            // print_bitboard(pawn >> 32);
            printf("%llu\n", pawn >> 24);
            printf("right = %d\n\n", already_generated_moves->en_passant);
        }
    }
    if (precomputed_values.power[piece_nbr + 1] & global_fen_meta_data.en_passant) {
        if (precomputed_values.distances[piece_nbr].east && !(precomputed_values.power[piece_nbr - 7] & (global_bitboards.black_pieces | global_bitboards.white_pieces))) {
            already_generated_moves->captures += precomputed_values.power[piece_nbr - 7];
            already_generated_moves->en_passant += pawn >> 24;
        }
    }
}