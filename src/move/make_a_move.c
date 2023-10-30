#include "move.h"
#include "generate_moves.h"
#include "global.h"
#include "utils.h"
#include "test.h"
#include "define.h"
#include "ai.h"

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
    recursive_params_t result = recursive_params;

    recursive_params_t *move_list = get_all_moves(recursive_params);

    if (move_list == NULL) return (get_recursive_params_glo());

    if (recursive_params.actual_white_turn) result = nerd();
    else result = randy(global_nbr_moves, move_list);

    free(move_list);

    return result;
}