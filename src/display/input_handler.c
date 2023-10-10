#include "generate_moves.h"
#include "include.h"
#include "display.h"
#include "define.h"
#include "global.h"
#include "utils.h"
#include "board.h"
#include "move.h"

// shitty opengl global variable
long long unsigned int selectedPiece = 0; // Currently selected piece (initially none)
long long unsigned int selectedSquare = 0; // Square where the piece will be moved

// Mouse callback function to handle piece selection and movement
void onMouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        global_highlighted_squares = 0;
        printf("cancelled, (%d, %d)\n", x, y);
        selectedPiece = 0; // Cancel the selection
        selectedSquare = 0;
        display();
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Calculate the square clicked
        int squareX = (WINDOWWIDTH - x) / GRIDSIZE; // Flip the X-coordinate
        int squareY = (WINDOWHEIGHT - y) / GRIDSIZE; // Flip the Y-coordinate

        // Calculate the index of the selected square
        int selectedSquareIndex = squareX + squareY * 8;


        if (precomputed_values.power[selectedSquareIndex] & global_highlighted_squares) {
            global_highlighted_squares = 0;
            // If a piece is already selected, set the destination square
            selectedSquare = precomputed_values.power[selectedSquareIndex];

            long long unsigned int *allies = NULL;
            long long unsigned int *enemies = NULL;

            if (global_fen_meta_data.white_turn) {
                allies = &global_bitboards.white_pieces;
                enemies = &global_bitboards.black_pieces;
            } else {
                allies = &global_bitboards.black_pieces;
                enemies = &global_bitboards.white_pieces;
            }
            if (selectedSquare == precomputed_values.power[0]) global_fen_meta_data.castle_right &= 0b1101;
            if (selectedSquare == precomputed_values.power[7]) global_fen_meta_data.castle_right &= 0b1110;
            if (selectedSquare == precomputed_values.power[56]) global_fen_meta_data.castle_right &= 0b0111;
            if (selectedSquare == precomputed_values.power[63]) global_fen_meta_data.castle_right &= 0b1011;
            global_bitboards.king = update_bitboard_king(selectedSquare, selectedPiece, allies, enemies);
            global_bitboards.pawn = update_bitboard_pawn(selectedSquare, selectedPiece, allies, enemies);
            global_bitboards.rook = update_bitboard(global_bitboards.rook, selectedPiece, selectedSquare, allies, enemies);
            global_bitboards.knight = update_bitboard(global_bitboards.knight, selectedPiece, selectedSquare, allies, enemies);
            global_bitboards.bishop = update_bitboard(global_bitboards.bishop, selectedPiece, selectedSquare, allies, enemies);
            global_bitboards.queen = update_bitboard(global_bitboards.queen, selectedPiece, selectedSquare, allies, enemies);

            printf("moved: %c%d\n\n", squareX + 'A', squareY + 1);
            rewind_chess_board(true, true);
            selectedSquare = 0;
            selectedPiece = 0;
            if (global_fen_meta_data.white_turn) {
                global_fen_meta_data.en_passant = global_fen_meta_data.en_passant & precomputed_values.filter_upper_piecies;
                global_fen_meta_data.white_turn = false;
            }
            else {
                global_fen_meta_data.en_passant = global_fen_meta_data.en_passant & precomputed_values.filter_lower_piecies;
                global_fen_meta_data.white_turn = true;
            }
            printf("\n");
            display();
        }
        else if (((global_bitboards.white_pieces & precomputed_values.power[selectedSquareIndex]) && global_fen_meta_data.white_turn) || (global_bitboards.black_pieces & precomputed_values.power[selectedSquareIndex] && !global_fen_meta_data.white_turn)) {
            // If no piece is selected, check if there is a piece on the selected square
            printf("seleted: %c%d\n", squareX + 'A', squareY + 1);
            current_moves = get_action_from_bitboard(precomputed_values.power[selectedSquareIndex]);
            global_highlighted_squares = current_moves.captures | current_moves.moves;
            selectedPiece = precomputed_values.power[selectedSquareIndex];
            display();
        } 
    }
}

// Keyboard callback function to cancel the selection
void onKeyPress(unsigned char key, int x, int y)
{
    if (key == 'c') { // 27 is the ASCII code for the Escape key
        global_highlighted_squares = 0;
        printf("cancelled, (%d, %d)\n", x, y);
        selectedPiece = 0; // Cancel the selection
        selectedSquare = 0;
        display();
    }
    if (key == 'd') {
        rewind_chess_board(false, true);
        display();
    }
    if (key == 'q') {
        rewind_chess_board(false, false);
        display();
    }
}