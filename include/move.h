/*
** EPITECH PROJECT, 2023
** Chess-Engine
** File description:
** move
*/

#ifndef MOVE_H_
    #define MOVE_H_

    // update_bitboards.c
    long long unsigned int update_bitboard (long long unsigned int piece_bitboard, long long unsigned int Piece, long long unsigned int Square, long long unsigned int *allies, long long unsigned int *enemies);
    long long unsigned int update_bitboard_pawn (long long unsigned int Square, long long unsigned int Piece, long long unsigned int *allies, long long unsigned int *enemies);
    long long unsigned int update_bitboard_king (long long unsigned int Square, long long unsigned int Piece, long long unsigned int *allies, long long unsigned int *enemies);


#endif /* !MOVE_H_ */
