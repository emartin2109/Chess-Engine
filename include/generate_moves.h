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
    moves_t get_action_from_bitboard (long long unsigned int piece, recursive_params_t *recursive_params);
    
    // generate_special_moves.c
    void genearte_pawn_double_moves (long long unsigned int move, long long unsigned int single_move, recursive_params_t *recursive_params ,moves_t *already_generated_moves);
    void generate_en_passant_moves_white (long long unsigned int pawn, int piece_nbr, moves_t *already_generated_moves, recursive_params_t *recursive_params);
    void generate_en_passant_moves_black (long long unsigned int pawn, int piece_nbr, moves_t *already_generated_moves, recursive_params_t *recursive_params);
    void generate_castle (int piece_nbr, moves_t *already_generated_moves, recursive_params_t *recursive_params);


#endif /* !GENERATE_MOVES_H_ */
