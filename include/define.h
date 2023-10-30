/*
** EPITECH PROJECT, 2023
** chess
** File description:
** define
*/

#ifndef DEFINE_H_
    #define DEFINE_H_

    // the AI you wich to challlenge
    #define AI "nerd"

    // personalizable stuffs
    #define START_POS "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
    #define REWIND_MEMORY 50
    #define MAX_DEPTH 7

    // OPENGL stuffs
    #define WINDOWWIDTH 1000
    #define WINDOWHEIGHT 1000
    #define GRIDSIZE 125

    // Quality of life stuffs
    #define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

    // flags for special moves
    #define NO_FLAG 0b0000
    #define EN_PASSANT_FLAG 0b0001
    #define CASTLE_FLAG 0b0010
    #define PROMOTE_QUEEN_FLAG 0b0011
    #define PROMOTE_NIGHT_FLAG 0b0100
    #define PROMOTE_ROOK_FLAG 0b0101
    #define PROMOTE_BISHOP_FLAG 0b0110

    // Monte Carlo settings
    #define UCT_CONST 0.5
    #define SIMULATIONS 100000


#endif /* !DEFINE_H_ */
