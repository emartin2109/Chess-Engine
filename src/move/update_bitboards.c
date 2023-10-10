#include "global.h"

long long unsigned int update_bitboard (long long unsigned int piece_bitboard, long long unsigned int Piece, long long unsigned int Square, long long unsigned int *allies, long long unsigned int *enemies)
{
    if (piece_bitboard & Square) {
        piece_bitboard ^= Square;
        *enemies ^= Square;
    }
    if ((piece_bitboard ^ Piece) < piece_bitboard) {
        piece_bitboard = piece_bitboard ^ Piece;
        piece_bitboard = piece_bitboard | Square;
        *allies ^= Piece;
        *allies |= Square;
    }
    return piece_bitboard;
}

long long unsigned int update_bitboard_pawn (long long unsigned int Square, long long unsigned int Piece, long long unsigned int *allies, long long unsigned int *enemies)
{
    if (global_bitboards.pawn & Square) {
        global_bitboards.pawn ^= Square;
        *enemies ^= Square;
    }
    if ((global_bitboards.pawn ^ Piece) < global_bitboards.pawn) {
        if (global_fen_meta_data.white_turn == true && (current_moves.en_passant & ((global_bitboards.pawn >> 32) & precomputed_values.filter_everything_exept_lowest_rank))) {
            global_bitboards.pawn ^= Square >> 8;
            *enemies ^= Square >> 8;
        }
        if (global_fen_meta_data.white_turn == false && (current_moves.en_passant & ((global_bitboards.pawn >> 24) & precomputed_values.filter_everything_exept_lowest_rank))) {
            global_bitboards.pawn  ^= Square << 8;
            *enemies ^= Square << 8;
        }
        global_bitboards.pawn = global_bitboards.pawn ^ Piece;
        global_bitboards.pawn = global_bitboards.pawn | Square;
        *allies ^= Piece;
        *allies |= Square;
    }
    return global_bitboards.pawn;
}

long long unsigned int update_bitboard_king (long long unsigned int Square, long long unsigned int Piece, long long unsigned int *allies, long long unsigned int *enemies)
{
    if (global_bitboards.king & Square) {
        global_bitboards.king ^= Square;
        *enemies ^= Square;
    }
    if ((global_bitboards.king ^ Piece) < global_bitboards.king) {
        if (Square & global_bitboards.rook & precomputed_values.right_corners) {
            global_bitboards.king += Square << 1;
            global_bitboards.rook += Square << 2;
            global_bitboards.rook -= Square;
            *allies += Square << 1;
            *allies += Square << 2;
            *allies -= Square;
        } else if (Square & global_bitboards.rook & precomputed_values.left_corners) {
            global_bitboards.king += Square >> 1;
            global_bitboards.rook += Square >> 2;
            global_bitboards.rook -= Square;
            *allies += Square >> 1;
            *allies += Square >> 2;
            *allies -= Square;
        } else {
            global_bitboards.king = global_bitboards.king | Square;
            *allies |= Square;
        }
        global_bitboards.king = global_bitboards.king ^ Piece;
        *allies ^= Piece;
        if (Piece & global_bitboards.white_pieces) global_fen_meta_data.castle_right &= 0b1100;
        if (Piece & global_bitboards.black_pieces) global_fen_meta_data.castle_right &= 0b0011;
    }
    return global_bitboards.king;
}