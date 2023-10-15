/*
** EPITECH PROJECT 2022
** pushswap.h
** File description:
** .h
*/

#ifndef PUSHSWAP_H_
    #define PUSHSWAP_H_

    #include "include.h"
    #include "struct.h"


    extern const int RookShifts[];
    extern const int BishopShifts[];
    extern const long long unsigned int RookMagics[];
    extern const long long unsigned int BishopMagics[];


    extern long long unsigned int **lookup_table_rook;
    extern long long unsigned int **lookup_table_bishop;
    extern long long unsigned int rook_mask[64];
    extern long long unsigned int bishop_mask[64];


    extern long long unsigned int global_highlighted_squares;
    extern fen_meta_data_t global_fen_meta_data;
    extern flags_t global_flags;
    extern precomputed_values_t precomputed_values;
    extern moves_t current_moves;
    extern recursive_params_t recursive_params_glo;
    extern bitboards_t global_bitboards;

#endif /* !PUSHSWAP_H_ */
