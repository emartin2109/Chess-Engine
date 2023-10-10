/*
** EPITECH PROJECT, 2023
** stumper02
** File description:
** main
*/

#include "main_loop.h"
#include "global.h"
#include "include.h"
#include "utils.h"
#include "define.h"
#include "struct.h"

bitboards_t global_bitboards;
fen_meta_data_t global_fen_meta_data;
flags_t global_flags;
precomputed_values_t precomputed_values;
long long int global_highlighted_squares;
moves_t current_moves = {0, 0, 0};

int main (int argc, char **argv)
{
    prepare_main_loop(argc, argv);
    return 0;
}