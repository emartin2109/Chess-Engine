/*
** EPITECH PROJECT, 2022
** pushswap.h
** File description:
** .h
*/

#ifndef PUSHSWAP_H_
    #define PUSHSWAP_H_

    typedef struct global_bitboards_s {
        long long unsigned int black_pieces;
        long long unsigned int white_pieces;

        long long unsigned int pawn;
        long long unsigned int rook;
        long long unsigned int knight;
        long long unsigned int bishop;
        long long unsigned int queen;
        long long unsigned int king;
    } global_bitboards_t;

    extern global_bitboards_t global_bitboards;

#endif /* !PUSHSWAP_H_ */
