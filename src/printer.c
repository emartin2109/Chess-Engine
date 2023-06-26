/*
** EPITECH PROJECT, 2023
** chess bot number 2
** File description:
** printer
*/

#include "chess.h"

void print_board (case_t **board)
{
    bool green = false;
    int y = -1;

    printf("\n\n\n\n\n");
    while (board[++y]) {
        int x = -1;
        printf(SET_COLOR_PURPLE);
        printf("%d   ", 8 - y);
        while (board[y][++x].piece) {

            if (green) printf(SET_COLOR_GREEN);
            else printf(SET_COLOR_CYAN);

            if (board[y][x].piece >= 'A' && board[y][x].piece <= 'Z') {
                printf(SET_COLOR_WHITE);
                printf("%c ", board[y][x].piece);
            } else if (board[y][x].piece >= 'a' && board[y][x].piece <= 'z') {
                printf(SET_COLOR_BLACK);
                printf("%c ", board[y][x].piece - 32);
            } else {
                printf("%c ", board[y][x].piece);
            }

            green = !green;

        }
        green = !green;
        printf("\n");
    }
    printf("\n");
    printf(SET_COLOR_PURPLE);
    printf("    a b c d e f g h\n");
    printf(SET_COLOR_DEFAULT);
}