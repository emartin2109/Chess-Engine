/*
** EPITECH PROJECT, 2023
** chess bot number 2
** File description:
** initialize
*/

#include "chess.h"

/*
void initializePiecePointers(char** chessboard)
{
    piece_t ****piece_coord = malloc(2 * sizeof(piece_t***));  // Allocate memory for black and white pieces
    
    for (int color = 0; color < 2; color++) {
        piece_coord[color] = malloc(6 * sizeof(piece_t**));  // Allocate memory for each piece type

        for (int piece = 0; piece < 6; piece++) {
            piece_coord[color][piece] = malloc(64 * sizeof(piece_t*));  // Allocate memory for each piece instance
            piece_coord[color][piece][0] = NULL;
        }
    }
    
    int ** piece_count = create_piece_count(); // Counter for each piece instance found
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            char piece = chessboard[i][j];

            if (piece >= 'a' && piece <= 'z') {  // Piece is black
                int piece_type = 0;
                if (piece == 'p') piece_type = PAWN;
                if (piece == 'r') piece_type = ROOK;
                if (piece == 'n') piece_type = KNIGHT;
                if (piece == 'b') piece_type = BISHOP;
                if (piece == 'q') piece_type = QUEEN;
                if (piece == 'k') piece_type = KING;
                int instance = piece_count[1][piece_type];
                piece_coord[1][piece_type][instance] = malloc(sizeof(piece_t));
                piece_coord[1][piece_type][instance]->pos.x = j;
                piece_coord[1][piece_type][instance]->pos.y = i;
                piece_coord[1][piece_type][instance]->turn_moved = 0;
                piece_coord[1][piece_type][instance + 1] = NULL;
                piece_count[1][piece_type]++;
            }
            else if (piece >= 'A' && piece <= 'Z') {  // Piece is white
                int piece_type = 0;
                if (piece == 'P') piece_type = PAWN;
                if (piece == 'R') piece_type = ROOK;
                if (piece == 'N') piece_type = KNIGHT;
                if (piece == 'B') piece_type = BISHOP;
                if (piece == 'Q') piece_type = QUEEN;
                if (piece == 'K') piece_type = KING;
                int instance = piece_count[0][piece_type];
                piece_coord[0][piece_type][instance] = malloc(sizeof(piece_t));
                piece_coord[0][piece_type][instance]->pos.x = j;
                piece_coord[0][piece_type][instance]->pos.y = i;
                piece_coord[0][piece_type][instance]->turn_moved = 0;
                piece_coord[0][piece_type][instance + 1] = NULL;
                piece_count[0][piece_type]++;
            }
        }
    }
    global_board_info.piece_count = piece_count;
    return piece_coord;
}
*/

void initialize_global_board_info (case_t **chessboard)
{
    int piece_index = 0;
    int i = 0;
    int ** piece_count = malloc(sizeof(int *) * 2);
    piece_t ***piece_list = malloc(sizeof(piece_t **) * 33);

    piece_count[0] = malloc(sizeof(int) * 6);
    memset(piece_count[0], 0, sizeof(int) * 6);
    piece_count[1] = malloc(sizeof(int) * 6);
    memset(piece_count[1], 0, sizeof(int) * 6);

    for (i = 0; i < 8; i++) {
        int j = 0;
        for (j = 0; j < 8; j++) {
            char piece_char = chessboard[i][j].piece;
            if (piece_char != '0') {
                int type = 0;
                int color = 0;
                piece_t piece;
                piece.pos = (coord_t) {j, i};
                piece.turn_moved = 0;

                if (piece_char == 'p' || piece_char == 'P') type = PAWN;
                else if (piece_char == 'r' || piece_char == 'R') type = ROOK;
                else if (piece_char == 'n' || piece_char == 'N') type = KNIGHT;
                else if (piece_char == 'b' || piece_char == 'B') type = BISHOP;
                else if (piece_char == 'k' || piece_char == 'K') type = KING;
                else if (piece_char == 'q' || piece_char == 'Q') type = QUEEN;

                if (piece_char <= 'z' && piece_char >= 'a') color = 1;

                piece.type = type;

                piece.color = color;

                piece_list[piece_index] = malloc(sizeof(piece_t *));
                piece_list[piece_index][0] = malloc(sizeof(piece_t));
                piece_list[piece_index++][0][0] = piece;
                piece_list[piece_index] = NULL;
                piece_count[color][type]++;
                if (piece_char == 'k') global_board_info.king_b = &piece;
                if (piece_char == 'K') global_board_info.king_w = &piece;
            }
        }
    }

    global_board_info.piece_list = piece_list;

    global_board_info.piece_in_square = malloc(sizeof(piece_t ***) * 8);
    i = 0;
    for (i = 0; i < 8; i++) {
        global_board_info.piece_in_square[i] = malloc(sizeof(piece_t **) * 8);
        for (int j = 0; j < 8; j++) {
            global_board_info.piece_in_square[i][j] = malloc(sizeof(piece_t *));
            global_board_info.piece_in_square[i][j][0] = NULL;
        }
    }
    i = 0;
    for (i = 0; piece_list[i]; i++) {
        global_board_info.piece_in_square[piece_list[i][0]->pos.y][piece_list[i][0]->pos.x][0] = piece_list[i][0];
    }

}
/*
    global_board_info.piece_attack_square = malloc(sizeof (coord_t ***) * 9);
    global_board_info.pieces_pointers[8] = NULL;
    int i = -1;
    while (i++ < 8) {
        global_board_info.pieces_pointers[i] = malloc(sizeof(coord_t *) * 8);
        int y = -1;
        while (++y < 8) {
            global_board_info.pieces_pointers[i][y] = NULL;
        }
    }
    int one = -1;
    while (++one < 2) {
        int two = -1;
        while (++two < 6) {
            int three = -1;
            while (global_board_info.pieces_position[one][two][++three] != NULL)
                global_board_info.pieces_pointers[global_board_info.pieces_position[one][two][three]->pos.y][global_board_info.pieces_position[one][two][three]->pos.x] = global_board_info.pieces_position[one][two][three];
        }
    }
}
*/

