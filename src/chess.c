/*
** EPITECH PROJECT, 2023
** chess bot number 2
** File description:
** chess
*/

#include "chess.h"

#define POSITION "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"

void main_loop(void)
{
    case_t **board = createChessBoard(POSITION);
    bool game_is_finish = false;
    bool is_white = true;
    initialize_global_board_info(board);
    global_board_info.turn_number = 1;
    while (!game_is_finish) {
        // print_board(board);
        int number_of_moves = count_moves(0, board, is_white, NULL);
        printf("\nNumber of moves = %d, color = %d, depth = %d\n", number_of_moves, !is_white, MAX_DEPTH);
        game_is_finish = true;
        global_board_info.turn_number++;
        is_white = !is_white;
    }
}