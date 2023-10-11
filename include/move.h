/*
** EPITECH PROJECT, 2023
** Chess-Engine
** File description:
** move
*/

#ifndef MOVE_H_
    #define MOVE_H_

    #include "struct.h"

    // update_bitboards.c
    long long unsigned int update_bitboard (long long unsigned int piece_bitboard, long long unsigned int Piece, long long unsigned int Square, recursive_params_t *recursive_params);
    long long unsigned int update_bitboard_pawn (long long unsigned int piece_bitboard, long long unsigned int Piece, long long unsigned int Square, recursive_params_t *recursive_params);
    long long unsigned int update_bitboard_king (long long unsigned int piece_bitboard, long long unsigned int Piece, long long unsigned int Square, recursive_params_t *recursive_params);
    // make_move.c
    recursive_params_t make_move(long long unsigned int start, long long unsigned int dest, recursive_params_t recursive_params);

#endif /* !MOVE_H_ */
