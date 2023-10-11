#include "struct.h"
#include "global.h"

//replace allies-> and enemies-> with withe and black stuff 
long long unsigned int update_bitboard (long long unsigned int piece_bitboard, long long unsigned int Piece, long long unsigned int Square, recursive_params_t *recursive_params)
{
    if (piece_bitboard & Square) {
        piece_bitboard ^= Square;
        recursive_params->enemies ^= Square;
    }
    if ((piece_bitboard ^ Piece) < piece_bitboard) {
        piece_bitboard = piece_bitboard ^ Piece;
        piece_bitboard = piece_bitboard | Square;
        recursive_params->allies ^= Piece;
        recursive_params->allies |= Square;
    }
    return piece_bitboard;
}

long long unsigned int update_bitboard_pawn (long long unsigned int piece_bitboard, long long unsigned int Piece, long long unsigned int Square, recursive_params_t *recursive_params)
{
    if (piece_bitboard & Square) {
        piece_bitboard ^= Square;
        recursive_params->enemies ^= Square;
    }
    if ((piece_bitboard ^ Piece) < piece_bitboard) {
        if (recursive_params->actual_white_turn == true && (current_moves.en_passant & ((piece_bitboard >> 32) & precomputed_values.filter_everything_exept_lowest_rank))) {
            piece_bitboard ^= Square >> 8;
            recursive_params->enemies ^= Square >> 8;
        }
        if (recursive_params->actual_white_turn == false && (current_moves.en_passant & ((piece_bitboard >> 24) & precomputed_values.filter_everything_exept_lowest_rank))) {
            piece_bitboard  ^= Square << 8;
            recursive_params->enemies ^= Square << 8;
        }
        if ((Piece & precomputed_values.filter_pawns_strating_squares) && (Square & precomputed_values.filter_pawn_double_squares)) recursive_params->actual_en_passant += Square;
        piece_bitboard = piece_bitboard ^ Piece;
        piece_bitboard = piece_bitboard | Square;
        recursive_params->allies ^= Piece;
        recursive_params->allies |= Square;
    }
    return piece_bitboard;
}

long long unsigned int update_bitboard_king (long long unsigned int piece_bitboard, long long unsigned int Piece, long long unsigned int Square, recursive_params_t *recursive_params)
{
    if (piece_bitboard & Square) {
        piece_bitboard ^= Square;
        recursive_params->enemies ^= Square;
    }
    if ((piece_bitboard ^ Piece) < piece_bitboard) {
        if (Square & recursive_params->local_bitboard_rook & precomputed_values.right_corners) {
            piece_bitboard += Square << 1;
            recursive_params->local_bitboard_rook += Square << 2;
            recursive_params->local_bitboard_rook -= Square;
            recursive_params->allies += Square << 1;
            recursive_params->allies += Square << 2;
            recursive_params->allies -= Square;
        } else if (Square & recursive_params->local_bitboard_rook & precomputed_values.left_corners) {
            piece_bitboard += Square >> 1;
            recursive_params->local_bitboard_rook += Square >> 2;
            recursive_params->local_bitboard_rook -= Square;
            recursive_params->allies += Square >> 1;
            recursive_params->allies += Square >> 2;
            recursive_params->allies -= Square;
        } else {
            piece_bitboard = piece_bitboard | Square;
            recursive_params->allies |= Square;
        }
        piece_bitboard = piece_bitboard ^ Piece;
        recursive_params->allies ^= Piece;
        if (Piece & recursive_params->local_bitboard_white) recursive_params->actual_catle_right &= 0b1100;
        if (Piece & recursive_params->local_bitboard_black) recursive_params->actual_catle_right &= 0b0011;
    }
    return piece_bitboard;
}