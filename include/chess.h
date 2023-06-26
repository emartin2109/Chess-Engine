/*
** EPITECH PROJECT, 2022
** pushswap.h
** File description:
** .h
*/

#ifndef PUSHSWAP_H_
    #define PUSHSWAP_H_

    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <ctype.h>
    #include <string.h>

    #define CHESS_BOARD_SIZE 8

    #define SET_COLOR_GREEN "\033[0;32m"
    #define SET_COLOR_CYAN "\033[0;36m"
    #define SET_COLOR_WHITE "\033[0;37m"
    #define SET_COLOR_BLACK "\033[0;30m"
    #define SET_COLOR_DEFAULT "\033[0m"
    #define SET_COLOR_PURPLE "\033[0;35m"
    #define SET_COLOR_RED "\033[0;31m"

    #define WHITE 0
    #define BLACK 1

    #define PAWN 0
    #define ROOK 1
    #define KNIGHT 2
    #define BISHOP 3
    #define QUEEN 4
    #define KING 5

    #define NO_CASTLE 0
    #define NORMAL_MOVE 0
    #define CASTLE_RIGHT 1
    #define CASTLE_LEFT 2
    #define EN_PASSANT 3

    #define MAX_DEPTH 6

    typedef enum chess_case_name_s {
        HEIGHT = 0,
        SEVEN = 1,
        SIX = 2,
        FIVE = 3,
        FOUR = 4,
        THREE = 5,
        TWO = 6,
        ONE = 7,
        A = 0,
        B = 1,
        C = 2,
        D = 3,
        E = 4,
        F = 5,
        G = 6,
        H = 7
    } chess_case_name_t;

    typedef enum encode_value_s {
        WHITE_PAWN = 0,
        WHITE_ROOK = 1,
        WHITE_KNIGHT = 2,
        WHITE_BISHOP = 3,
        WHITE_QUEEN = 4,
        WHITE_KING = 5,

        BLACK_PAWN = 6,
        BLACK_ROOK = 7,
        BLACK_KNIGH = 8,
        BLACK_BISHOP = 9,
        BLACK_QUEEN = 10,
        BLACK_KING = 11,

        WHITE_CASTLE_RIGHT = 12,
        WHITE_CASTLE_LEFT = 13,
        BLACK_CASTLE_RIGHT = 14,
        BLACK_CASTLE_LEFT = 15
    } encode_value_t;

    typedef struct coord_s {
        int x;
        int y;
    } coord_t;

    typedef struct piece_s {
        coord_t pos;
        coord_t *moves;
        int type;
        int castle_allowed;
        int turn_moved;
        int color;
    } piece_t;

    typedef struct case_s {
        char piece;
        int is_attacked;
    } case_t;

    typedef struct global_board_info_s {
        piece_t *** piece_list;
        piece_t **** piece_in_square;
        int **piece_count;
        int turn_number;
        piece_t * king_w;
        piece_t * king_b;
    } global_board_info_t;

    typedef struct node_s {
        int special_move_type;
        coord_t move_dest;
        coord_t move_origin;
    } node_t;

    extern global_board_info_t global_board_info;

// chess.c
void main_loop(void);

// get_board.c
case_t ** createChessBoard(const char* boardString);

// printer.c
void print_board (case_t **board);

// utils.c
char *get_input (void);

// move.c
void move_human (case_t **board, bool is_white);
int count_moves (int depth, case_t **board, bool is_white, node_t *current_node);

// initialize.c
void initialize_global_board_info (case_t **chessboard);

// generate_moves.c
coord_t * generate_rook_moves(coord_t* rookCoord, case_t** chessboard, bool is_white);
coord_t * generate_knight_moves(coord_t* knightCoord, case_t** chessboard, bool is_white);
coord_t * generate_bishop_moves(coord_t* bishopCoord, case_t** chessboard, bool is_white);
coord_t * generate_queen_moves(coord_t* queenCoord, case_t** chessboard, bool is_white);
coord_t * generate_pawn_moves(coord_t *pawn, case_t **board, bool is_white);
coord_t * generate_king_moves(coord_t* kingCoord, case_t** chessboard, bool is_white);


#endif /*!PUSHSWAP_H_ */
