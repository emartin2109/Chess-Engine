/*
** EPITECH PROJECT, 2023
** chess bot number 2
** File description:
** get_board
*/

#include "chess.h"

void place_pieces (char **board)
{
    board[ONE][A] = 'R';
    board[ONE][B] = 'N';
    board[ONE][C] = 'B';
    board[ONE][D] = 'Q';
    board[ONE][E] = 'K';
    board[ONE][F] = 'B';
    board[ONE][G] = 'N';
    board[ONE][H] = 'R';
    board[TWO][A] = 'P';
    board[TWO][B] = 'P';
    board[TWO][C] = 'P';
    board[TWO][D] = 'P';
    board[TWO][E] = 'P';
    board[TWO][F] = 'P';
    board[TWO][G] = 'P';
    board[TWO][H] = 'P';

    board[HEIGHT][A] = 'r';
    board[HEIGHT][B] = 'n';
    board[HEIGHT][C] = 'b';
    board[HEIGHT][D] = 'q';
    board[HEIGHT][E] = 'k';
    board[HEIGHT][F] = 'b';
    board[HEIGHT][G] = 'n';
    board[HEIGHT][H] = 'r';
    board[SEVEN][A] = 'p';
    board[SEVEN][B] = 'p';
    board[SEVEN][C] = 'p';
    board[SEVEN][D] = 'p';
    board[SEVEN][E] = 'p';
    board[SEVEN][F] = 'p';
    board[SEVEN][G] = 'p';
    board[SEVEN][H] = 'p';
}

case_t ** createChessBoard(const char* boardString)
{
    case_t** board = malloc(9 * sizeof(case_t*));
    board[8] = NULL;

    for (int i = 0; i < 8; i++) {
        board[i] = malloc(9 * sizeof(case_t));
        memset(board[i], ' ', 8 * sizeof(case_t));
        board[i][8].piece = '\0';
        board[i][8].is_attacked = false;
    }

    int rank = 0;
    int file = 0;

    for (int i = 0; boardString[i] != '\0'; i++) {
        if (boardString[i] == '/') {
            rank++;
            file = 0;
        } else if (boardString[i] >= '1' && boardString[i] <= '8') {
            int emptySquares = boardString[i] - '0';
            for (int j = 0; j < emptySquares; j++) {
                board[rank][file].is_attacked = false;
                board[rank][file++].piece = '0';
            }
        } else {
            board[rank][file].is_attacked = false;
            board[rank][file++].piece = boardString[i];
        }
    }

    return board;
}