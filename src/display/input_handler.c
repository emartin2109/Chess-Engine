#include "generate_moves.h"
#include "include.h"
#include "display.h"
#include "define.h"
#include "global.h"
#include "utils.h"
#include "board.h"
#include "move.h"
#include "test.h"

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

            recursive_params_glo = make_move(selectedPiece, selectedSquare, recursive_params_glo);

            printf("moved: %c%d\n\n", squareX + 'A', squareY + 1);
            // rewind_chess_board(true, true);
            selectedSquare = 0;
            selectedPiece = 0;
            if (recursive_params_glo.actual_white_turn) {
                recursive_params_glo.actual_en_passant = recursive_params_glo.actual_en_passant & precomputed_values.filter_upper_piecies;
                recursive_params_glo.actual_white_turn = false;
                recursive_params_glo.local_bitboard_black = recursive_params_glo.enemies;
                recursive_params_glo.local_bitboard_white = recursive_params_glo.allies;
            }
            else {
                recursive_params_glo.actual_en_passant = recursive_params_glo.actual_en_passant & precomputed_values.filter_lower_piecies;
                recursive_params_glo.actual_white_turn = true;
                recursive_params_glo.local_bitboard_black = recursive_params_glo.allies;
                recursive_params_glo.local_bitboard_white = recursive_params_glo.enemies;
            }
            long long unsigned int temp = recursive_params_glo.allies;
            recursive_params_glo.allies = recursive_params_glo.enemies;
            recursive_params_glo.enemies = temp;
            display();
        }
        else if (((recursive_params_glo.local_bitboard_white & precomputed_values.power[selectedSquareIndex]) && recursive_params_glo.actual_white_turn) || (recursive_params_glo.local_bitboard_black & precomputed_values.power[selectedSquareIndex] && !recursive_params_glo.actual_white_turn)) {
            // If no piece is selected, check if there is a piece on the selected square
            printf("seleted: %c%d\n", squareX + 'A', squareY + 1);
            current_moves = get_action_from_bitboard(precomputed_values.power[selectedSquareIndex], &recursive_params_glo);
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