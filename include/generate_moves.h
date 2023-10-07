/*
** EPITECH PROJECT, 2023
** Chess-Engine
** File description:
** generate_moves
*/

#ifndef GENERATE_MOVES_H_
    #define GENERATE_MOVES_H_

    #include "struct.h"

    long long unsigned int get_action_from_bitboard (long long unsigned int piece);
    
    moves_t generade_sliding_moves(long long unsigned int piece, bool diagonal, bool linear, long long unsigned int allies, long long unsigned int enemies);
    moves_t generate_knight_moves (long long unsigned int piece, long long unsigned int allies, long long unsigned int enemies);
    moves_t generate_king_moves (long long unsigned int piece, long long unsigned int allies, long long unsigned int enemies);
    moves_t generate_paw_moves (long long unsigned int piece);


#endif /* !GENERATE_MOVES_H_ */
