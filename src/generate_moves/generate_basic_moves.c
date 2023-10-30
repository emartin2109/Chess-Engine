#include "generate_moves.h"
#include "struct.h"
#include "include.h"
#include "utils.h"
#include "global.h"
#include "move.h"
#include "test.h"

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

void generate_moves_and_captures_by_offset(long long unsigned int piece, int offset, int distance_to_edge, recursive_params_t *recursive_params, moves_t *already_generated_moves)
{
    for (int i = 0; i < distance_to_edge; i++) {
        if (offset > 0) piece = piece << offset;
        if (offset < 0) piece = piece >> -offset;
        if (piece & recursive_params->allies) return;
        if (piece & recursive_params->enemies) {
            already_generated_moves[0].captures += piece;
            return;
        }
        already_generated_moves[0].moves += piece;
    }
}

void generate_rook_moves(int piece_nbr, recursive_params_t recursive_params, moves_t *moves)
{
    moves->moves |= lookup_table_rook[piece_nbr][(((recursive_params.allies | recursive_params.enemies) & rook_mask[piece_nbr]) * RookMagics[piece_nbr]) >> RookShifts[piece_nbr]] & ~recursive_params.allies;;
}

void generate_bishop_moves(int piece_nbr, recursive_params_t recursive_params, moves_t *moves)
{
    moves->moves |= lookup_table_bishop[piece_nbr][(((recursive_params.allies | recursive_params.enemies) & bishop_mask[piece_nbr]) * BishopMagics[piece_nbr]) >> BishopShifts[piece_nbr]] & ~recursive_params.allies;
}

void generate_queen_moves(int piece_nbr, recursive_params_t recursive_params, moves_t *moves)
{
    generate_rook_moves(piece_nbr, recursive_params, moves);
    generate_bishop_moves(piece_nbr, recursive_params, moves);
}

moves_t generate_sliding_moves(long long unsigned int piece, bool diagonal, bool linear, recursive_params_t *recursive_params)
{
    moves_t result;
    int piece_nbr = __builtin_ctzll(piece);

    result.moves = 0;
    result.captures = 0;
    result.en_passant = 0;

    if (linear) {
        generate_moves_and_captures_by_offset(piece, 8, precomputed_values.distances[piece_nbr].north, recursive_params, &result);
        generate_moves_and_captures_by_offset(piece, -8, precomputed_values.distances[piece_nbr].south, recursive_params, &result);
        generate_moves_and_captures_by_offset(piece, -1, precomputed_values.distances[piece_nbr].west, recursive_params, &result);
        generate_moves_and_captures_by_offset(piece, 1, precomputed_values.distances[piece_nbr].east, recursive_params, &result);
    }

    if (diagonal) {
        generate_moves_and_captures_by_offset(piece, 7, precomputed_values.distances[piece_nbr].north_west, recursive_params, &result);
        generate_moves_and_captures_by_offset(piece, 9, precomputed_values.distances[piece_nbr].north_east, recursive_params, &result);
        generate_moves_and_captures_by_offset(piece, -9, precomputed_values.distances[piece_nbr].south_west, recursive_params, &result);
        generate_moves_and_captures_by_offset(piece, -7, precomputed_values.distances[piece_nbr].south_east, recursive_params, &result);
    }

    return result;
}

moves_t generate_pawn_moves (long long unsigned int piece, recursive_params_t *recursive_params)
{
    moves_t result;
    int piece_nbr = __builtin_ctzll(piece);

    result.moves = 0;
    result.captures = 0;
    result.en_passant = 0;

    if (piece_nbr < 8 || piece_nbr > 55) return result;

    if (recursive_params->actual_white_turn) {
        // double moves
        if (piece_nbr < 16) genearte_pawn_double_moves(precomputed_values.power[piece_nbr + 16], precomputed_values.power[piece_nbr + 8], recursive_params, &result);
        // en passant
        // else generate_en_passant_moves_white(piece, piece_nbr, &result, recursive_params);

        // basic moves
        if (precomputed_values.distances[piece_nbr].west) generate_captures_by_bitboard(precomputed_values.power[piece_nbr + 7], recursive_params->local_bitboard_black, &result);
        generate_moves_by_bitboard(precomputed_values.power[piece_nbr + 8], recursive_params->local_bitboard_white, recursive_params->local_bitboard_black, &result);
        if (precomputed_values.distances[piece_nbr].east) generate_captures_by_bitboard(precomputed_values.power[piece_nbr + 9], recursive_params->local_bitboard_black, &result);
    }
    
    else {
        if (piece_nbr > 47) genearte_pawn_double_moves(precomputed_values.power[piece_nbr - 16], precomputed_values.power[piece_nbr - 8], recursive_params, &result);
        // else generate_en_passant_moves_black(piece, piece_nbr, &result, recursive_params);

        if (precomputed_values.distances[piece_nbr].east) generate_captures_by_bitboard(precomputed_values.power[piece_nbr - 7], recursive_params->local_bitboard_white, &result);
        generate_moves_by_bitboard(precomputed_values.power[piece_nbr - 8], recursive_params->local_bitboard_black, recursive_params->local_bitboard_white, &result);
        if (precomputed_values.distances[piece_nbr].west) generate_captures_by_bitboard(precomputed_values.power[piece_nbr - 9], recursive_params->local_bitboard_white, &result);
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

moves_t generate_king_moves (long long unsigned int piece, recursive_params_t *recursive_params)
{
    moves_t result;
    int piece_nbr = __builtin_ctzll(piece);
    long long unsigned int allies = recursive_params->allies;
    long long unsigned int enemies = recursive_params->enemies;

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

    // generate_castle(piece_nbr, &result, recursive_params);

    return result;
}

moves_t get_action_from_bitboard (long long unsigned int piece, recursive_params_t *recursive_params)
{
    moves_t moves = {0, 0, 0};

    if (piece & recursive_params->local_bitboard_pawn) moves = generate_pawn_moves(piece, recursive_params);
    else if (piece & recursive_params->local_bitboard_knight) moves = generate_knight_moves(piece, recursive_params->allies, recursive_params->enemies);
    else if (piece & recursive_params->local_bitboard_rook) generate_rook_moves(__builtin_ctzll(piece), *recursive_params, &moves);
    else if (piece & recursive_params->local_bitboard_bishop) generate_bishop_moves(__builtin_ctzll(piece), *recursive_params, &moves);
    else if (piece & recursive_params->local_bitboard_queen) generate_queen_moves(__builtin_ctzll(piece), *recursive_params, &moves);

    return moves;
}

recursive_params_t *get_all_moves(recursive_params_t recursive_params)
{
    recursive_params_t *move_list = malloc(219 * sizeof(recursive_params_t));
    int number_of_moves = 0;
    long long unsigned int temp_allies = (recursive_params.allies | recursive_params.local_bitboard_king) ^ recursive_params.local_bitboard_king;

    if (!(recursive_params.local_bitboard_king & recursive_params.allies) || !(recursive_params.local_bitboard_king & recursive_params.enemies)) {
        free(move_list);
        return NULL;
    }

    while (temp_allies != 0) {
        int a_index = __builtin_ffsll(temp_allies) - 1;
        temp_allies -= precomputed_values.power[a_index];

        moves_t current_moves = get_action_from_bitboard(precomputed_values.power[a_index], &recursive_params);
        long long unsigned int moves = current_moves.moves | current_moves.captures;

        while (moves != 0) {
            int m_index = __builtin_ffsll(moves) - 1;
            moves -= precomputed_values.power[m_index];
            recursive_params_t move = make_move(precomputed_values.power[a_index], precomputed_values.power[m_index], recursive_params);
            if (move.allies & move.local_bitboard_king) move_list[number_of_moves++] = move;
            else {
                printf("JJJJJJJJJ\n");
                exit(0);
            }
        }
    }

    int k_index = __builtin_ffsl(recursive_params.local_bitboard_king & recursive_params.allies) - 1;
    current_moves = generate_king_moves (precomputed_values.power[k_index], &recursive_params);
    long long unsigned int moves = current_moves.moves | current_moves.captures;

    while (moves != 0) {
        int m_index = __builtin_ffsll(moves) - 1;
        moves -= precomputed_values.power[m_index];
        recursive_params_t move = make_move(precomputed_values.power[k_index], precomputed_values.power[m_index], recursive_params);
        if (move.allies & move.local_bitboard_king) move_list[number_of_moves++] = move;
        else {
            printf("GGGGGGGGGGGGGGG\n");
            exit(1);
        }
    }

    global_nbr_moves = number_of_moves;
    
    if (global_nbr_moves == 0) {
        free(move_list);
        printf("HHIJkazijoadzijpo\n");
        exit(1);
        return NULL;
    }

    return move_list;
}