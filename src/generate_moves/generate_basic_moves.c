#include "generate_moves.h"
#include "struct.h"
#include "include.h"
#include "utils.h"
#include "global.h"


void generate_moves_by_bitboard(long long unsigned int move, long long unsigned int allies, long long unsigned int enemies, moves_t *already_generated_moves)
{
    if (!(move & (allies | enemies))) {
        already_generated_moves[0].moves += move;
    }
}

void generate_captures_by_bitboard(long long unsigned int move, long long unsigned int enemies, moves_t *already_generated_moves)
{
    if (move & enemies) {
        already_generated_moves[0].captures += move;
    }
}

void generate_moves_and_captures_by_bitboard(long long unsigned int move, long long unsigned int allies, long long unsigned int enemies, moves_t *already_generated_moves)
{
    generate_moves_by_bitboard(move, allies, enemies, already_generated_moves);
    generate_captures_by_bitboard(move, enemies, already_generated_moves);
}

void generate_moves_and_captures_by_offset(long long unsigned int piece, int offset, int distance_to_edge, long long unsigned int allies, long long unsigned int enemies, moves_t *already_generated_moves)
{
    for (int i = 0; i < distance_to_edge; i++) {
        if (offset > 0) piece = piece << offset;
        if (offset < 0) piece = piece >> -offset;
        if (piece & allies) return;
        if (piece & enemies) {
            already_generated_moves[0].captures += piece;
            return;
        }
        already_generated_moves[0].moves += piece;
    }
}


moves_t generate_sliding_moves(long long unsigned int piece, bool diagonal, bool linear, long long unsigned int allies, long long unsigned int enemies)
{
    moves_t result;
    int piece_nbr = __builtin_ctzll(piece);

    result.moves = 0;
    result.captures = 0;
    result.en_passant = 0;

    if (linear) {
        generate_moves_and_captures_by_offset(piece, 8, precomputed_values.distances[piece_nbr].north, allies, enemies, &result);
        generate_moves_and_captures_by_offset(piece, -8, precomputed_values.distances[piece_nbr].south, allies, enemies, &result);
        generate_moves_and_captures_by_offset(piece, -1, precomputed_values.distances[piece_nbr].west, allies, enemies, &result);
        generate_moves_and_captures_by_offset(piece, 1, precomputed_values.distances[piece_nbr].east, allies, enemies, &result);
    }

    if (diagonal) {
        generate_moves_and_captures_by_offset(piece, 7, precomputed_values.distances[piece_nbr].north_west, allies, enemies, &result);
        generate_moves_and_captures_by_offset(piece, 9, precomputed_values.distances[piece_nbr].north_east, allies, enemies, &result);
        generate_moves_and_captures_by_offset(piece, -9, precomputed_values.distances[piece_nbr].south_west, allies, enemies, &result);
        generate_moves_and_captures_by_offset(piece, -7, precomputed_values.distances[piece_nbr].south_east, allies, enemies, &result);
    }

    return result;
}

moves_t generate_pawn_moves (long long unsigned int piece)
{
    moves_t result;
    int piece_nbr = __builtin_ctzll(piece);

    result.moves = 0;
    result.captures = 0;
    result.en_passant = 0;

    if (global_fen_meta_data.white_turn) {
        // double moves
        if (piece_nbr < 17) genearte_pawn_double_moves(precomputed_values.power[piece_nbr + 16], global_bitboards.white_pieces, global_bitboards.black_pieces, &result);

        // en passant
        generate_en_passant_moves_white(piece, piece_nbr, &result);

        // basic moves
        if (precomputed_values.distances[piece_nbr].north && precomputed_values.distances[piece_nbr].west) generate_captures_by_bitboard(precomputed_values.power[piece_nbr + 7], global_bitboards.black_pieces, &result);
        if (precomputed_values.distances[piece_nbr].north) generate_moves_by_bitboard(precomputed_values.power[piece_nbr + 8], global_bitboards.white_pieces, global_bitboards.black_pieces, &result);
        if (precomputed_values.distances[piece_nbr].north && precomputed_values.distances[piece_nbr].east) generate_captures_by_bitboard(precomputed_values.power[piece_nbr + 9], global_bitboards.black_pieces, &result);
    }
    
    else {
        if (piece_nbr > 47) genearte_pawn_double_moves(precomputed_values.power[piece_nbr - 16], global_bitboards.black_pieces, global_bitboards.white_pieces, &result);

        generate_en_passant_moves_black(piece, piece_nbr, &result);

        if (precomputed_values.distances[piece_nbr].south && precomputed_values.distances[piece_nbr].east) generate_captures_by_bitboard(precomputed_values.power[piece_nbr - 7], global_bitboards.white_pieces, &result);
        if (precomputed_values.distances[piece_nbr].south) generate_moves_by_bitboard(precomputed_values.power[piece_nbr - 8], global_bitboards.black_pieces, global_bitboards.white_pieces, &result);
        if (precomputed_values.distances[piece_nbr].south && precomputed_values.distances[piece_nbr].west) generate_captures_by_bitboard(precomputed_values.power[piece_nbr - 9], global_bitboards.white_pieces, &result);
    }

    return result;
}

moves_t generate_knight_moves (long long unsigned int piece, long long unsigned int allies, long long unsigned int enemies)
{
    moves_t result;
    int piece_nbr = __builtin_ctzll(piece);

    result.moves = 0;
    result.captures = 0;
    result.en_passant = 0;

    if (precomputed_values.distances[piece_nbr].north > 1 && precomputed_values.distances[piece_nbr].east) generate_moves_and_captures_by_bitboard(precomputed_values.power[piece_nbr + 1 + 8 + 8], allies, enemies, &result);
    if (precomputed_values.distances[piece_nbr].south > 1 && precomputed_values.distances[piece_nbr].east) generate_moves_and_captures_by_bitboard(precomputed_values.power[piece_nbr + 1 - 8 - 8], allies, enemies, &result);

    if (precomputed_values.distances[piece_nbr].north && precomputed_values.distances[piece_nbr].east > 1) generate_moves_and_captures_by_bitboard(precomputed_values.power[piece_nbr + 1 + 1 + 8], allies, enemies, &result);
    if (precomputed_values.distances[piece_nbr].south && precomputed_values.distances[piece_nbr].east > 1) generate_moves_and_captures_by_bitboard(precomputed_values.power[piece_nbr + 1 + 1 - 8], allies, enemies, &result);

    if (precomputed_values.distances[piece_nbr].north > 1 && precomputed_values.distances[piece_nbr].west) generate_moves_and_captures_by_bitboard(precomputed_values.power[piece_nbr - 1 + 8 + 8], allies, enemies, &result);
    if (precomputed_values.distances[piece_nbr].south > 1 && precomputed_values.distances[piece_nbr].west) generate_moves_and_captures_by_bitboard(precomputed_values.power[piece_nbr - 1 - 8 - 8], allies, enemies, &result);

    if (precomputed_values.distances[piece_nbr].north && precomputed_values.distances[piece_nbr].west > 1) generate_moves_and_captures_by_bitboard(precomputed_values.power[piece_nbr - 1 - 1 + 8], allies, enemies, &result);
    if (precomputed_values.distances[piece_nbr].south && precomputed_values.distances[piece_nbr].west > 1) generate_moves_and_captures_by_bitboard(precomputed_values.power[piece_nbr - 1 - 1 - 8], allies, enemies, &result);

    return result;
}

moves_t generate_king_moves (long long unsigned int piece, long long unsigned int allies, long long unsigned int enemies)
{
    moves_t result;
    int piece_nbr = __builtin_ctzll(piece);

    result.moves = 0;
    result.captures = 0;
    result.en_passant = 0;

    if (precomputed_values.distances[piece_nbr].north && precomputed_values.distances[piece_nbr].west) generate_moves_and_captures_by_bitboard(precomputed_values.power[piece_nbr + 7], allies, enemies, &result);
    if (precomputed_values.distances[piece_nbr].north) generate_moves_and_captures_by_bitboard(precomputed_values.power[piece_nbr + 8], allies, enemies, &result);
    if (precomputed_values.distances[piece_nbr].north && precomputed_values.distances[piece_nbr].east) generate_moves_and_captures_by_bitboard(precomputed_values.power[piece_nbr + 9], allies, enemies, &result);

    if (precomputed_values.distances[piece_nbr].east) generate_moves_and_captures_by_bitboard(precomputed_values.power[piece_nbr + 1], allies, enemies, &result);
    if (precomputed_values.distances[piece_nbr].west) generate_moves_and_captures_by_bitboard(precomputed_values.power[piece_nbr - 1], allies, enemies, &result);

    if (precomputed_values.distances[piece_nbr].south && precomputed_values.distances[piece_nbr].east) generate_moves_and_captures_by_bitboard(precomputed_values.power[piece_nbr - 7], allies, enemies, &result);
    if (precomputed_values.distances[piece_nbr].south) generate_moves_and_captures_by_bitboard(precomputed_values.power[piece_nbr - 8], allies, enemies, &result);
    if (precomputed_values.distances[piece_nbr].south && precomputed_values.distances[piece_nbr].west) generate_moves_and_captures_by_bitboard(precomputed_values.power[piece_nbr - 9], allies, enemies, &result);

    return result;
}

moves_t get_action_from_bitboard (long long unsigned int piece)
{
    moves_t moves;
    long long unsigned int allies;
    long long unsigned int enemies;

    if (global_fen_meta_data.white_turn) {
        printf("withe turn !\n");
        allies = global_bitboards.white_pieces;
        enemies = global_bitboards.black_pieces;
    } else {
        printf("black turn !\n");
        allies = global_bitboards.black_pieces;
        enemies = global_bitboards.white_pieces;
    }

    if (piece & global_bitboards.pawn) moves = generate_pawn_moves(piece);

    if (piece & global_bitboards.rook) moves = generate_sliding_moves(piece, false, true, allies, enemies);

    if (piece & global_bitboards.knight) moves = generate_knight_moves(piece, allies, enemies);

    if (piece & global_bitboards.bishop) moves = generate_sliding_moves(piece, true, false, allies, enemies);

    if (piece & global_bitboards.queen) moves = generate_sliding_moves(piece, true, true, allies, enemies);

    if (piece & global_bitboards.king) moves = generate_king_moves(piece, allies, enemies);

    return moves;
}