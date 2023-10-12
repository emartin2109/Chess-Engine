#include "move.h"
#include "global.h"

recursive_params_t make_move(long long unsigned int start, long long unsigned int dest, recursive_params_t recursive_params)
{
    if (dest == precomputed_values.power[0]) recursive_params.actual_catle_right &= 0b1101;
    if (dest == precomputed_values.power[7]) recursive_params.actual_catle_right &= 0b1110;
    if (dest == precomputed_values.power[56]) recursive_params.actual_catle_right &= 0b0111;
    if (dest == precomputed_values.power[63]) recursive_params.actual_catle_right &= 0b1011;
    recursive_params.local_bitboard_king = update_bitboard_king(recursive_params.local_bitboard_king, start, dest, &recursive_params);
    recursive_params.local_bitboard_pawn = update_bitboard_pawn(recursive_params.local_bitboard_pawn, start, dest, &recursive_params);
    recursive_params.local_bitboard_rook = update_bitboard(recursive_params.local_bitboard_rook, start, dest, &recursive_params);
    recursive_params.local_bitboard_knight = update_bitboard(recursive_params.local_bitboard_knight, start, dest, &recursive_params);
    recursive_params.local_bitboard_bishop = update_bitboard(recursive_params.local_bitboard_bishop, start, dest, &recursive_params);
    recursive_params.local_bitboard_queen = update_bitboard(recursive_params.local_bitboard_queen, start, dest, &recursive_params);

    return recursive_params;
}