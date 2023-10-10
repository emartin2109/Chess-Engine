#include "generate_moves.h"
#include "include.h"
#include "display.h"
#include "define.h"
#include "global.h"
#include "utils.h"
#include "board.h"

// shitty opengl global variable
long long unsigned int selectedPiece = 0; // Currently selected piece (initially none)
long long unsigned int selectedSquare = 0; // Square where the piece will be moved
moves_t current_moves = {0, 0, 0};

const char pieceChars[] = "prnbqkPRNBQK";

char *load_fen_string()
{
    char* fen = malloc(71); // Maximum possible size
    char* fen_temp = fen;

    int square = 0;
    int emptyCount = 0;
    
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 7; file >= 0; file--) {
            square = rank * 8 + file;
            
            char piece = ' ';
            int color = 0;
            
            if (global_bitboards.black_pieces & precomputed_values.power[square]) color += 0;
            else if (global_bitboards.white_pieces & precomputed_values.power[square]) color += 6;

            if (global_bitboards.pawn & precomputed_values.power[square]) piece = *(pieceChars + 0 + color);
            else if (global_bitboards.rook & precomputed_values.power[square]) piece = *(pieceChars + 1 + color);
            else if (global_bitboards.knight & precomputed_values.power[square]) piece = *(pieceChars + 2 + color);
            else if (global_bitboards.bishop & precomputed_values.power[square]) piece = *(pieceChars + 3 + color);
            else if (global_bitboards.queen & precomputed_values.power[square]) piece = *(pieceChars + 4 + color);
            else if (global_bitboards.king & precomputed_values.power[square]) piece = *(pieceChars + 5 + color);
            
            if (piece == ' ') {
                emptyCount++;
            } else {
                if (emptyCount > 0) {
                    *fen++ = '0' + emptyCount;
                    emptyCount = 0;
                }
                *fen++ = piece;
            }
        }
        
        if (emptyCount > 0) {
            *fen++ = '0' + emptyCount;
            emptyCount = 0;
        }
        
        if (rank > 0) {
            *fen++ = '/';
        }
    }
    
    *fen++ = ' ';
    *fen++ = 'w'; // Assuming it's white's turn
    *fen++ = ' ';
    
    // You can add castling rights, en passant square, halfmove clock, and fullmove number here
    
    *fen++ = '\0'; // Null-terminate the string
    
    return fen_temp;
}

void rewind_chess_board(bool is_add, bool is_forward)
{
    static char* history[REWIND_MEMORY] = { NULL };
    static int cursor = -1;

    if (is_add == true)
    {
        // Save the current FEN string to history
        cursor++;
        if (history[cursor])
        {
            free(history[cursor]);
        }
        history[cursor] = load_fen_string();
        create_board(history[cursor]);

        // Free any future history beyond the current cursor
        for (int i = cursor + 1; i < REWIND_MEMORY; i++)
        {
            if (history[i])
            {
                free(history[i]);
                history[i] = NULL;
            }
        }
    }
    else if (is_forward == true && history[cursor + 1])
    {
        // Move forward in history if possible
        cursor++;
        create_board(history[cursor]);
    }
    else if (is_forward == false && cursor > 0)
    {
        // Move backward in history if possible
        cursor--;
        create_board(history[cursor]);
    }
}


long long unsigned int update_bitboard (long long unsigned int piece_bitboard, long long unsigned int Piece, long long unsigned int Square, long long unsigned int *allies, long long unsigned int *enemies)
{
    if (piece_bitboard & Square) {
        piece_bitboard ^= Square;
        *enemies ^= Square;
    }
    if ((piece_bitboard ^ Piece) < piece_bitboard) {
        piece_bitboard = piece_bitboard ^ Piece;
        piece_bitboard = piece_bitboard | Square;
        *allies ^= Piece;
        *allies |= Square;
    }
    return piece_bitboard;
}

long long unsigned int update_bitboard_pawn (long long unsigned int Square, long long unsigned int Piece, long long unsigned int *allies, long long unsigned int *enemies)
{
    if (global_bitboards.pawn & Square) {
        global_bitboards.pawn ^= Square;
        *enemies ^= Square;
    }
    if ((global_bitboards.pawn ^ Piece) < global_bitboards.pawn) {
        if (global_fen_meta_data.white_turn == true && (current_moves.en_passant & ((global_bitboards.pawn >> 32) & precomputed_values.filter_everything_exept_lowest_rank))) {
            global_bitboards.pawn ^= Square >> 8;
            *enemies ^= Square >> 8;
        }
        if (global_fen_meta_data.white_turn == false && (current_moves.en_passant & ((global_bitboards.pawn >> 24) & precomputed_values.filter_everything_exept_lowest_rank))) {
            global_bitboards.pawn  ^= Square << 8;
            *enemies ^= Square << 8;
        }
        global_bitboards.pawn = global_bitboards.pawn ^ Piece;
        global_bitboards.pawn = global_bitboards.pawn | Square;
        *allies ^= Piece;
        *allies |= Square;
    }
    return global_bitboards.pawn;
}

long long unsigned int update_bitboard_king (long long unsigned int Square, long long unsigned int Piece, long long unsigned int *allies, long long unsigned int *enemies)
{
    if (global_bitboards.king & Square) {
        global_bitboards.king ^= Square;
        *enemies ^= Square;
    }
    if ((global_bitboards.king ^ Piece) < global_bitboards.king) {
        if (Square & global_bitboards.rook & precomputed_values.right_corners) {
            global_bitboards.king += Square << 1;
            global_bitboards.rook += Square << 2;
            global_bitboards.rook -= Square;
            *allies += Square << 1;
            *allies += Square << 2;
            *allies -= Square;
        } else if (Square & global_bitboards.rook & precomputed_values.left_corners) {
            global_bitboards.king += Square >> 1;
            global_bitboards.rook += Square >> 2;
            global_bitboards.rook -= Square;
            *allies += Square >> 1;
            *allies += Square >> 2;
            *allies -= Square;
        } else {
            global_bitboards.king = global_bitboards.king | Square;
            *allies |= Square;
        }
        global_bitboards.king = global_bitboards.king ^ Piece;
        *allies ^= Piece;
        if (Piece & global_bitboards.white_pieces) global_fen_meta_data.castle_right &= 0b1100;
        if (Piece & global_bitboards.black_pieces) global_fen_meta_data.castle_right &= 0b0011;
    }
    return global_bitboards.king;
}

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