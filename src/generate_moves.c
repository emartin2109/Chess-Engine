/*
** EPITECH PROJECT, 2023
** chess bot number 3
** File description:
** generate_moves
*/

#include "chess.h"

coord_t* generate_rook_moves(coord_t* rookCoord, register case_t** chessboard, bool is_white)
{
    int rookX = rookCoord->y;
    int rookY = rookCoord->x;
    char letter_low = 'A';
    char letter_high = 'Z';

    if (is_white) {
        letter_low = 'a';
        letter_high = 'z';
    }

    int maxMoves = 14 + 1;  // 14 = Maximum possible moves for a rook
    coord_t* moves = (coord_t*)malloc(maxMoves * sizeof(coord_t*));

    int moveCount = 0;

    // Check horizontally to the right
    for (int i = rookY + 1; i < 8; i++) {
        if (chessboard[rookX][i].piece != '0' && !(chessboard[rookX][i].piece >= letter_low && chessboard[rookX][i].piece <= letter_high)) {
            break;
        }

        moves[moveCount].y = rookX;
        moves[moveCount].x = i;
        moveCount++;

        if (chessboard[rookX][i].piece != '0')
            break;
    }

    // Check horizontally to the left
    for (int i = rookY - 1; i >= 0; i--) {
        if (chessboard[rookX][i].piece != '0' && !(chessboard[rookX][i].piece >= letter_low && chessboard[rookX][i].piece <= letter_high))
            break;

        moves[moveCount].y = rookX;
        moves[moveCount].x = i;
        moveCount++;

        if (chessboard[rookX][i].piece != '0')
            break;
    }

    // Check vertically upwards
    for (int i = rookX - 1; i >= 0; i--) {
        if (chessboard[i][rookY].piece != '0' && !(chessboard[i][rookY].piece >= letter_low && chessboard[i][rookY].piece <= letter_high))
            break;

        moves[moveCount].y = i;
        moves[moveCount].x = rookY;
        moveCount++;

        if (chessboard[i][rookY].piece != '0')
            break;
    }

    // Check vertically downwards
    for (int i = rookX + 1; i < 8; i++) {
        if (chessboard[i][rookY].piece != '0' && !(chessboard[i][rookY].piece >= letter_low && chessboard[i][rookY].piece <= letter_high))
            break;

        moves[moveCount].y = i;
        moves[moveCount].x = rookY;
        moveCount++;

        if (chessboard[i][rookY].piece != '0')
            break;
    }

    moves[moveCount].x = -1;

    if (moveCount == 0) {
        free(moves);
        moves = NULL;
    }

    return moves;
}


coord_t* generate_knight_moves(coord_t* knightCoord, register case_t** chessboard, bool is_white)
{
    int knightX = knightCoord->y;
    int knightY = knightCoord->x;
    char letter_low = 'a';
    char letter_high = 'z';

    if (!is_white) {
        letter_low = 'A';
        letter_high = 'Z';
    }

    int maxMoves = 8 + 1;  // 8 = Maximum possible moves for a knight
    coord_t* moves = (coord_t*)malloc(maxMoves * sizeof(coord_t*));

    int moveCount = 0;

    // Generate all possible knight moves
    int offsetX[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int offsetY[] = {1, 2, 2, 1, -1, -2, -2, -1};

    for (int i = 0; i < 8; i++) {
        int newX = knightX + offsetX[i];
        int newY = knightY + offsetY[i];

        // Check if the new position is within the chessboard and can be attacked
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 && 
            (chessboard[newX][newY].piece == '0' || 
            (chessboard[newX][newY].piece >= letter_low && chessboard[newX][newY].piece <= letter_high))) {
            
            moves[moveCount].y = newX;
            moves[moveCount].x = newY;
            moveCount++;
        }
    }

    moves[moveCount].x = -1;

    if (moveCount == 0) {
        free(moves);
        moves = NULL;
    }

    return moves;
}

coord_t* generate_bishop_moves(coord_t* bishopCoord, register case_t** chessboard, bool is_white)
{
    int bishopX = bishopCoord->y;
    int bishopY = bishopCoord->x;
    char letter_low = 'A';
    char letter_high = 'Z';

    if (is_white) {
        letter_low = 'a';
        letter_high = 'z';
    }

    int maxMoves = 13 + 1;  // 13 = Maximum possible moves for a bishop
    coord_t* moves = (coord_t*)malloc(maxMoves * sizeof(coord_t*));

    int moveCount = 0;

    // Check diagonally to the top-right
    for (int i = 1; bishopX - i >= 0 && bishopY + i < 8; i++) {
        int newX = bishopX - i;
        int newY = bishopY + i;

        if (chessboard[newX][newY].piece == '0' || (chessboard[newX][newY].piece >= letter_low && chessboard[newX][newY].piece <= letter_high)) {
            moves[moveCount].y = newX;
            moves[moveCount].x = newY;
            moveCount++;

            if (chessboard[newX][newY].piece != '0')
                break;
        } else {
            break;
        }
    }

    // Check diagonally to the top-left
    for (int i = 1; bishopX - i >= 0 && bishopY - i >= 0; i++) {
        int newX = bishopX - i;
        int newY = bishopY - i;

        if (chessboard[newX][newY].piece == '0' || (chessboard[newX][newY].piece >= letter_low && chessboard[newX][newY].piece <= letter_high)) {
            moves[moveCount].y = newX;
            moves[moveCount].x = newY;
            moveCount++;

            if (chessboard[newX][newY].piece != '0')
                break;
        } else {
            break;
        }
    }

    // Check diagonally to the bottom-right
    for (int i = 1; bishopX + i < 8 && bishopY + i < 8; i++) {
        int newX = bishopX + i;
        int newY = bishopY + i;

        if (chessboard[newX][newY].piece == '0' || (chessboard[newX][newY].piece >= letter_low && chessboard[newX][newY].piece <= letter_high)) {
            moves[moveCount].y = newX;
            moves[moveCount].x = newY;
            moveCount++;

            if (chessboard[newX][newY].piece != '0')
                break;
        } else {
            break;
        }
    }

    // Check diagonally to the bottom-left
    for (int i = 1; bishopX + i < 8 && bishopY - i >= 0; i++) {
        int newX = bishopX + i;
        int newY = bishopY - i;

        if (chessboard[newX][newY].piece == '0' || (chessboard[newX][newY].piece >= letter_low && chessboard[newX][newY].piece <= letter_high)) {
            moves[moveCount].y = newX;
            moves[moveCount].x = newY;
            moveCount++;

            if (chessboard[newX][newY].piece != '0')
                break;
        } else {
            break;
        }
    }

    moves[moveCount].x = -1;

    if (moveCount == 0) {
        free(moves);
        moves = NULL;
    }

    return moves;
}


coord_t* generate_queen_moves(coord_t* queenCoord, register case_t** chessboard, bool is_white)
{
    int queenX = queenCoord->y;
    int queenY = queenCoord->x;
    char letter_low = 'A';
    char letter_high = 'Z';

    if (is_white) {
        letter_low = 'a';
        letter_high = 'z';
    }

    int maxMoves = 27 + 1;  // 17 = Maximum possible moves for a queen
    coord_t* moves = (coord_t*)malloc(maxMoves * sizeof(coord_t*));

    int moveCount = 0;

    // Check horizontally to the right
    for (int i = queenY + 1; i < 8; i++) {
        if (chessboard[queenX][i].piece == '0' || (chessboard[queenX][i].piece >= letter_low && chessboard[queenX][i].piece <= letter_high)) {
            moves[moveCount].y = queenX;
            moves[moveCount].x = i;
            moveCount++;            
            if (chessboard[queenX][i].piece != '0') break;
        } else {
            break;
        }
    }

    // Check horizontally to the left
    for (int i = queenY - 1; i >= 0; i--) {
        if (chessboard[queenX][i].piece == '0' || (chessboard[queenX][i].piece >= letter_low && chessboard[queenX][i].piece <= letter_high)) {
            moves[moveCount].y = queenX;
            moves[moveCount].x = i;
            moveCount++;            
            if (chessboard[queenX][i].piece != '0') break;
        } else {
            break;
        }
    }

    // Check vertically upwards
    for (int i = queenX - 1; i >= 0; i--) {
        if (chessboard[i][queenY].piece == '0' || (chessboard[i][queenY].piece >= letter_low && chessboard[i][queenY].piece <= letter_high)) {
            moves[moveCount].y = i;
            moves[moveCount].x = queenY;
            moveCount++;            
            if (chessboard[i][queenY].piece != '0') break;
        } else {
            break;
        }
    }

    // Check vertically downwards
    for (int i = queenX + 1; i < 8; i++) {
        if (chessboard[i][queenY].piece == '0' || (chessboard[i][queenY].piece >= letter_low && chessboard[i][queenY].piece <= letter_high)) {
            moves[moveCount].y = i;
            moves[moveCount].x = queenY;
            moveCount++;            
            if (chessboard[i][queenY].piece != '0') break;
        } else {
            break;
        }
    }

    // Check diagonally to the top-right
    for (int i = 1; queenX - i >= 0 && queenY + i < 8; i++) {
        if (chessboard[queenX - i][queenY + i].piece == '0' || (chessboard[queenX - i][queenY + i].piece >= letter_low && chessboard[queenX - i][queenY + i].piece <= letter_high)) {
            moves[moveCount].y = queenX - i;
            moves[moveCount].x = queenY + i;
            moveCount++;            
            if (chessboard[queenX - i][queenY + i].piece != '0') break;
        } else {
            break;
        }
    }

    // Check diagonally to the top-left
    for (int i = 1; queenX - i >= 0 && queenY - i >= 0; i++) {
        if (chessboard[queenX - i][queenY - i].piece == '0' || (chessboard[queenX - i][queenY - i].piece >= letter_low && chessboard[queenX - i][queenY - i].piece <= letter_high)) {
            moves[moveCount].y = queenX - i;
            moves[moveCount].x = queenY - i;
            moveCount++;            
            if (chessboard[queenX - i][queenY - i].piece != '0') break;
        } else {
            break;
        }
    }

    // Check diagonally to the bottom-right
    for (int i = 1; queenX + i < 8 && queenY + i < 8; i++) {
        if (chessboard[queenX + i][queenY + i].piece == '0' || (chessboard[queenX + i][queenY + i].piece >= letter_low && chessboard[queenX + i][queenY + i].piece <= letter_high)) {
            moves[moveCount].y = queenX + i;
            moves[moveCount].x = queenY + i;
            moveCount++;            
            if (chessboard[queenX + i][queenY + i].piece != '0') break;
        } else {
            break;
        }
    }

    // Check diagonally to the bottom-left
    for (int i = 1; queenX + i < 8 && queenY - i >= 0; i++) {
        if (chessboard[queenX + i][queenY - i].piece == '0' || (chessboard[queenX + i][queenY - i].piece >= letter_low && chessboard[queenX + i][queenY - i].piece <= letter_high)) {
            moves[moveCount].y = queenX + i;
            moves[moveCount].x = queenY - i;
            moveCount++;            
            if (chessboard[queenX + i][queenY - i].piece != '0') break;
        } else {
            break;
        }
    }

    moves[moveCount].x = -1;

    if (moveCount == 0) {
        free(moves);
        moves = NULL;
    }

    return moves;
}

coord_t* generate_pawn_moves(coord_t* pawnCoord, register case_t** chessboard, bool is_white)
{
    int pawnX = pawnCoord->y;
    int pawnY = pawnCoord->x;
    char letter_low = 'a';
    char letter_high = 'z';

    if (!is_white) {
        letter_low = 'A';
        letter_high = 'Z';
    }

    int maxMoves = 5 + 1;  // 5 = Maximum possible moves for a pawn
    coord_t* moves = (coord_t*)malloc(maxMoves * sizeof(coord_t*));

    int moveCount = 0;

    // Generate all possible pawn moves
    int direction = is_white ? -1 : 1;  // Direction of pawn movement based on color
    int startX = is_white ? 6 : 1;  // Starting row of pawns based on color

    // Move one step forward
    int newX = pawnX + direction;
    int newY = pawnY;
    if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 && chessboard[newX][newY].piece == '0') {
        moves[moveCount].y = newX;
        moves[moveCount].x = newY;
        moveCount++;
    }

    // Move two steps forward from starting position
    if (pawnX == startX) {
        newX = pawnX + (2 * direction);
        newY = pawnY;
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 && chessboard[newX][newY].piece == '0' &&
            chessboard[newX - direction][newY].piece == '0') {
            moves[moveCount].y = newX;
            moves[moveCount].x = newY;
            moveCount++;
        }
    }

    // Capture diagonally to the left
    newX = pawnX + direction;
    newY = pawnY - 1;
    if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 &&
        (chessboard[newX][newY].piece >= letter_low && chessboard[newX][newY].piece <= letter_high)) {
        moves[moveCount].y = newX;
        moves[moveCount].x = newY;
        moveCount++;
    }

    // Capture diagonally to the right
    newX = pawnX + direction;
    newY = pawnY + 1;
    if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 &&
        (chessboard[newX][newY].piece >= letter_low && chessboard[newX][newY].piece <= letter_high)) {
        moves[moveCount].y = newX;
        moves[moveCount].x = newY;
        moveCount++;
    }

    int prevTurnNumber = global_board_info.turn_number;

    // En passant capture to the left
    if (pawnY - 1 >= 0 && chessboard[pawnX][pawnY - 1].piece >= letter_low &&
        chessboard[pawnX][pawnY - 1].piece <= letter_high &&
        global_board_info.piece_in_square[pawnX][pawnY - 1][0]->turn_moved == prevTurnNumber &&
        abs(global_board_info.piece_in_square[pawnX][pawnY - 1][0]->pos.y - pawnX) == 2) {
        moves[moveCount].y = pawnX + direction;
        moves[moveCount].x = pawnY - 1;
        moveCount++;
    }

    // En passant capture to the right
    if (pawnY + 1 < 8 && chessboard[pawnX][pawnY + 1].piece >= letter_low &&
        chessboard[pawnX][pawnY + 1].piece <= letter_high &&
        global_board_info.piece_in_square[pawnX][pawnY + 1][0]->turn_moved == prevTurnNumber &&
        abs(global_board_info.piece_in_square[pawnX][pawnY + 1][0]->pos.y - pawnX) == 2) {
        moves[moveCount].y = pawnX + direction;
        moves[moveCount].x = pawnY + 1;
        moveCount++;
    }

    moves[moveCount].x = -1;

    if (moveCount == 0) {
        free(moves);
        moves = NULL;
    }

    return moves;
}

coord_t* generate_king_moves(coord_t* kingCoord, register case_t** chessboard, bool is_white)
{
    int kingX = kingCoord->y;
    int kingY = kingCoord->x;
    char letter_low = 'a';
    char letter_high = 'z';

    if (!is_white) {
        letter_low = 'A';
        letter_high = 'Z';
    }

    int maxMoves = 8;  // Maximum possible moves for a king
    coord_t* moves = (coord_t*)malloc(maxMoves * sizeof(coord_t*));

    int moveCount = 0;

    // Generate all possible king moves
    int offsetX[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int offsetY[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++) {
        int newX = kingX + offsetX[i];
        int newY = kingY + offsetY[i];

        // Check if the new position is within the chessboard and can be attacked
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 && 
            (chessboard[newX][newY].piece == '0' || 
            (chessboard[newX][newY].piece >= letter_low && chessboard[newX][newY].piece <= letter_high))) {

            moves[moveCount].y = newX;
            moves[moveCount].x = newY;
            moveCount++;
        }
    }

    moves[moveCount].x = -1;

    if (moveCount == 0) {
        free(moves);
        moves = NULL;
    }

    return moves;
}
