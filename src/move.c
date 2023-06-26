/*
** EPITECH PROJECT, 2023
** chess bot number 2
** File description:
** move
*/

#include "chess.h"

coord_t *get_board_translated_pos (char y, char x)
{
    if (x < 'a' || y < '1' || x > 'h' || y > '8') return NULL;
    int new_y = y - '1';
    int new_x = x - 'a';
    new_y = 7 - new_y;
    coord_t *result = malloc (sizeof (coord_t));
    result->x = new_x;
    result->y = new_y;
    return result;
}

bool piece_is_valid (char piece, bool is_white)
{
    if (piece == '\0') {
        printf("wrong format was given\n");
        return false;
    }
    if (piece == '0') {
        printf("there is no piece here\n");
        return false;
    }
    if (is_white) {
        if (piece < 'A' || piece > 'Z') {
            printf("You can't move a black piece since this is white's turn\n");
            return false;
        }
    } else {
        if (piece < 'a' || piece > 'z') {
            printf("You can't move a white piece since this is black's turn\n");
            return false;
        }
    }
    return true;
}

int count_moves(int depth, register case_t** board, bool is_white, node_t* current_node)
{
    if (depth >= MAX_DEPTH) return 1;


    int number_of_moves = 0;
    if (current_node != NULL) {
        board[current_node->move_dest.y][current_node->move_dest.x].piece = board[current_node->move_origin.y][current_node->move_origin.x].piece;
        board[current_node->move_origin.y][current_node->move_origin.x].piece = '0';
        if (global_board_info.piece_in_square[current_node->move_dest.y][current_node->move_dest.x][0] != NULL) global_board_info.piece_in_square[current_node->move_dest.y][current_node->move_dest.x][0]->pos.x = -1;
        global_board_info.piece_in_square[current_node->move_dest.y][current_node->move_dest.x][0] = global_board_info.piece_in_square[current_node->move_origin.y][current_node->move_origin.x][0];
        global_board_info.piece_in_square[current_node->move_origin.y][current_node->move_origin.x][0]->pos = current_node->move_dest;
        global_board_info.piece_in_square[current_node->move_origin.y][current_node->move_origin.x][0] = NULL;
        if (current_node->special_move_type == EN_PASSANT) {
            global_board_info.piece_in_square[current_node->move_origin.y][current_node->move_dest.x][0]->pos.x = -1;
            global_board_info.piece_in_square[current_node->move_origin.y][current_node->move_dest.x][0] = NULL;
            board[current_node->move_origin.y][current_node->move_dest.x].piece = '0';
        }
    }

    for (int i = 0; i < 32; i++) {
        if (global_board_info.piece_list[i][0] == NULL || global_board_info.piece_list[i][0]->color == is_white || global_board_info.piece_list[i][0]->pos.x < 0) continue;

        piece_t piece = **(global_board_info.piece_list[i]);

        switch (piece.type) {
            case PAWN:
                piece.moves = generate_pawn_moves(&(piece.pos), board, is_white);
                break;
            case ROOK:
                piece.moves = generate_rook_moves(&(piece.pos), board, is_white);
                break;
            case KNIGHT:
                piece.moves = generate_knight_moves(&(piece.pos), board, is_white);
                break;
            case BISHOP:
                piece.moves = generate_bishop_moves(&(piece.pos), board, is_white);
                break;
            case QUEEN:
                piece.moves = generate_queen_moves(&(piece.pos), board, is_white);
                break;
            case KING:
                piece.moves = generate_king_moves(&(piece.pos), board, is_white);
                break;
            default:
                piece.moves = NULL;
                break;
        }

        if (piece.moves != NULL) {
            char origin_char = board[piece.pos.y][piece.pos.x].piece;
            piece_t *origin_piece = global_board_info.piece_in_square[piece.pos.y][piece.pos.x][0];

            for (int j = 0; piece.moves[j].x != -1; j++) {
                char dest_char = board[piece.moves[j].y][piece.moves[j].x].piece;
                piece_t* dest_piece = global_board_info.piece_in_square[piece.moves[j].y][piece.moves[j].x][0];

                node_t new_node;
                new_node.move_origin = piece.pos;
                // printf("y = %d, x = %d\n", piece.pos.y, piece.pos.x);
                new_node.move_dest = piece.moves[j];
                new_node.special_move_type = NORMAL_MOVE;
                // printf("%d\n", origin_piece);
                if (origin_piece == NULL) {
                    print_board(board);
                    printf("pos = %d%d, origin_char = %c, type = %d, depth = %d, location: y = %d, x = %d\n", global_board_info.piece_in_square[2][1][0]->pos.y, global_board_info.piece_in_square[2][1][0]->pos.y, origin_char, piece.type, depth, piece.pos.y, piece.pos.x);
                }
                if (origin_piece->type == PAWN && piece.moves[j].x != origin_piece->pos.x && dest_char == '0') {
                    new_node.special_move_type = EN_PASSANT;
                    dest_char = board[piece.pos.y][piece.moves[j].x].piece;
                    dest_piece = global_board_info.piece_in_square[piece.pos.y][piece.moves[j].x][0];
                }
                number_of_moves += count_moves(depth + 1, board, !is_white, &new_node);


                if (depth == MAX_DEPTH - 1) continue;

                if (new_node.special_move_type == EN_PASSANT) {
                    board[piece.pos.y][piece.pos.x].piece = origin_char;
                    board[piece.pos.y][piece.moves[j].x].piece = dest_char;
                    board[piece.moves[j].y][piece.moves[j].x].piece = '0';

                    origin_piece->pos = piece.pos;
                    dest_piece->pos.x = piece.pos.x;

                    global_board_info.piece_in_square[piece.pos.y][piece.pos.x][0] = origin_piece;
                    global_board_info.piece_in_square[piece.pos.y][piece.moves[j].x][0] = dest_piece;
                    global_board_info.piece_in_square[piece.moves[j].y][piece.moves[j].x][0] = NULL;
                } else {
                    board[piece.pos.y][piece.pos.x].piece = origin_char;
                    board[piece.moves[j].y][piece.moves[j].x].piece = dest_char;

                    origin_piece->pos = piece.pos;
                    if (dest_piece != NULL) dest_piece->pos.x = piece.moves[j].x;

                    global_board_info.piece_in_square[piece.pos.y][piece.pos.x][0] = origin_piece;
                    global_board_info.piece_in_square[piece.moves[j].y][piece.moves[j].x][0] = dest_piece;
                }
                // if (dest_piece != NULL) dest_piece->pos = *piece.moves[j];
            }
        }
        free(piece.moves);
    }
    return number_of_moves;
}


void move_human (case_t **board, bool is_white)
{
    /*
    for (int i = 0; global_board_info.piece_list[i] != NULL; i++) {
        piece_t *piece = global_board_info.piece_list[i];
        if (piece->color == is_white) continue;
        if (piece->type == PAWN) piece->moves = generate_pawn_moves(&(piece->pos), board, is_white);
        else if (piece->type == ROOK) piece->moves = generate_rook_moves(&(piece->pos), board, is_white);
        else if (piece->type == KNIGHT) piece->moves = generate_knight_moves(&(piece->pos), board, is_white);
        else if (piece->type == BISHOP) piece->moves = generate_bishop_moves(&(piece->pos), board, is_white);
        else if (piece->type == QUEEN) piece->moves = generate_queen_moves(&(piece->pos), board, is_white);
        else piece->moves = NULL;
    }
    sleep(2);
    */
    /*
    bool move_is_done = false;
    char *input = NULL;
    coord_t *piece = NULL;
    coord_t *square = NULL;
    coord_t **moves = NULL;
    while (!move_is_done) {

        if (piece != NULL) {
            free(piece);
            piece = NULL;
        }

        if (square != NULL) {
            free(square);
            square = NULL;
        }

        printf(SET_COLOR_DEFAULT);
        printf("\nplease enter the piece coordinate at format [a - h][1 - 8], for example a7 is a valid input\n");
        input = get_input();

        printf(SET_COLOR_RED);
        printf("\n");
        if (input == NULL) {
            printf("that is not a valid input\n");
            continue;
        }
        piece = get_board_translated_pos (input[1], input[0]);
        if (piece == NULL) {
            printf("wrong format was given\n");
            continue;
        }
        if (!piece_is_valid(board[piece->y][piece->x], is_white)) continue;
        printf(SET_COLOR_GREEN);
        printf("Valid Piece\n");
        printf(SET_COLOR_DEFAULT);

        if (tolower(board[piece->y][piece->x]) == 'p') moves = generate_pawn_moves(piece, board, is_white);
        if (tolower(board[piece->y][piece->x]) == 'r') moves = generate_rook_moves(piece, board, is_white);
        if (tolower(board[piece->y][piece->x]) == 'n') moves = generate_knight_moves(piece, board, is_white);
        if (tolower(board[piece->y][piece->x]) == 'b') moves = generate_bishop_moves(piece, board, is_white);
        if (tolower(board[piece->y][piece->x]) == 'q') moves = generate_queen_moves(piece, board, is_white);

        printf(SET_COLOR_RED);
        if (moves == NULL) {
            printf("selected piece have nowhere to move\n");
            continue;
        }
        printf(SET_COLOR_DEFAULT);

        int i = -1;
        while (moves[++i]) {
            char char1 = moves[i]->x + 'a';
            char char2 = 8 - moves[i]->y + '0';
            printf("%d    %c%c\n", i + 1, char1, char2);
        }

        printf("please give the number of the move you wish to select, if you don't want to do any of them just enter a number below 0\n");
        int number_given  = atoi(get_input());

        printf(SET_COLOR_RED);

        if (number_given < 0) continue;
        if (number_given == 0) {
            printf("Invalid Format!\n");
            continue;
        }

        printf(SET_COLOR_GREEN);
        printf("Valid Input!\n");
        printf(SET_COLOR_DEFAULT);

        coord_t *square_to_go = moves[number_given - 1];
        if (board[piece->y][piece->x] == 'p' || board[piece->y][piece->x] == 'P') {
            if ((square_to_go->x == piece->x + 1 || square_to_go->x == piece->x - 1) && (square_to_go->y == piece->y + 1 || square_to_go->y == piece->y - 1)) {
                if (board[square_to_go->y][square_to_go->x] == '0') {
                    board[piece->y][square_to_go->x] = '0';
                    global_board_info.pieces_pointers[piece->y][square_to_go->x]->pos.x = -1;
                    global_board_info.pieces_pointers[piece->y][square_to_go->x]->pos.y = -1;
                    global_board_info.pieces_pointers[piece->y][square_to_go->x] = NULL;
                }
            }
            if (square_to_go->y == 7 || square_to_go->y == 0) {
                printf("\nplease chose the piece you wish to transform the pawn, 1 = rook, 2 = knight, 3 = bishop, 4 = queen\n");
                number_given  = atoi(get_input());
                if (number_given == 1) board[piece->y][piece->x] += 2;
                else if (number_given == 2) board[piece->y][piece->x] -= 2;
                else if (number_given == 3) board[piece->y][piece->x] -= 14;
                else if (number_given == 4) board[piece->y][piece->x] += 1;
                else continue;
            }
        }
        board[square_to_go->y][square_to_go->x] = board[piece->y][piece->x];
        board[piece->y][piece->x] = '0';
        if (global_board_info.pieces_pointers[square_to_go->y][square_to_go->x] != NULL) {
            global_board_info.pieces_pointers[square_to_go->y][square_to_go->x]->pos.x = -1;
            global_board_info.pieces_pointers[square_to_go->y][square_to_go->x]->pos.y = -1;
            global_board_info.pieces_pointers[square_to_go->y][square_to_go->x] = NULL;
        }
        piece_t *temp;
        temp = global_board_info.pieces_pointers[piece->y][piece->x];
    
        temp->pos.x = square_to_go->x;
        temp->pos.y = square_to_go->y;
        if (temp->turn_moved == 0)
            temp->turn_moved = global_board_info.turn_number;
        global_board_info.pieces_pointers[square_to_go->y][square_to_go->x] = temp;
        global_board_info.pieces_pointers[piece->y][piece->x] = NULL;
        move_is_done = true;
    }
    */
}
