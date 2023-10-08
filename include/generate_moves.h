/*
** EPITECH PROJECT, 2023
** Chess-Engine
** File description:
** generate_moves
*/

#ifndef GENERATE_MOVES_H_
    #define GENERATE_MOVES_H_

    #include "struct.h"

    // generate_basic_moves_.c
    moves_t get_action_from_bitboard (long long unsigned int piece);

    moves_t generade_sliding_moves(long long unsigned int piece, bool diagonal, bool linear, long long unsigned int allies, long long unsigned int enemies);
    moves_t generate_knight_moves (long long unsigned int piece, long long unsigned int allies, long long unsigned int enemies);
    moves_t generate_king_moves (long long unsigned int piece, long long unsigned int allies, long long unsigned int enemies);
    moves_t generate_paw_moves (long long unsigned int piece);
    
    // generate_special_moves.c
    void genearte_pawn_double_moves (long long unsigned int move, long long unsigned int allies, long long unsigned int enemies ,moves_t *already_generated_moves);
    void generate_en_passant_moves_white (long long unsigned int pawn, int piece_nbr, moves_t *already_generated_moves);
    void generate_en_passant_moves_black (long long unsigned int pawn, int piece_nbr, moves_t *already_generated_moves);


#endif /* !GENERATE_MOVES_H_ */
