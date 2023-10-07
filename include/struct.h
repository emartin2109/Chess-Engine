/*
** EPITECH PROJECT, 2023
** Chess-Engine
** File description:
** struct
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

    #include "include.h"

    typedef struct moves_s {
        long long unsigned int moves;
        long long unsigned int captures;
    } moves_t;

    typedef struct bitboards_s {
        long long unsigned int black_pieces;
        long long unsigned int white_pieces;

        long long unsigned int pawn;
        long long unsigned int rook;
        long long unsigned int knight;
        long long unsigned int bishop;
        long long unsigned int queen;
        long long unsigned int king;
    } bitboards_t;

    typedef struct fen_meta_data_s {
        bool white_turn;
        int castle_right;
        long long unsigned int en_passant;
    } fen_meta_data_t;

    typedef struct flags_s {
        bool rewind;
        bool no_ai;
    } flags_t;

    typedef struct distance_to_edge_s {
        int north;
        int south;
        int east;
        int west;
        int north_east;
        int north_west;
        int south_east;
        int south_west;
    } distance_to_edge_t;

    typedef struct precomputed_values_s {
        distance_to_edge_t distances[64];
        long long unsigned int power[64];
    } precomputed_values_t;


#endif /* !STRUCT_H_ */
