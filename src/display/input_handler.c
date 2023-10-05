#include "include.h"
#include "define.h"
#include "display.h"
#include "global.h"
#include "utils.h"
#include "board.h"

// shitty opengl global variable
long long unsigned int selectedPiece = 0; // Currently selected piece (initially none)
long long unsigned int selectedSquare = 0; // Square where the piece will be moved

const char pieceChars[] = "prnbqkPRNBQK";

char *load_fen_string()
{
    char* fen = malloc(71); // Maximum possible size
    char* fen_temp = fen;

    int square = 0;
    int emptyCount = 0;
    
    for (int rank = 0; rank <= 7; rank++) {
        for (int file = 0; file <= 7; file++) {
            square = rank * 8 + file;
            
            char piece = ' ';
            int color = 0;
            
            if (global_bitboards.black_pieces & power(2, square)) color += 6;
            else if (global_bitboards.white_pieces & power(2, square)) color += 0;

            if (global_bitboards.pawn & power(2, square)) piece = *(pieceChars + 0 + color);
            else if (global_bitboards.rook & power(2, square)) piece = *(pieceChars + 1 + color);
            else if (global_bitboards.knight & power(2, square)) piece = *(pieceChars + 2 + color);
            else if (global_bitboards.bishop & power(2, square)) piece = *(pieceChars + 3 + color);
            else if (global_bitboards.queen & power(2, square)) piece = *(pieceChars + 4 + color);
            else if (global_bitboards.king & power(2, square)) piece = *(pieceChars + 5 + color);
            
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

    printf("%s\n", fen_temp);
    
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


long long unsigned int update_bitboard (long long unsigned int piece_bitboard, long long unsigned int Piece, long long unsigned int Square)
{
    if (piece_bitboard & Square) {
        piece_bitboard = piece_bitboard ^ Square;
    }
    if ((piece_bitboard ^ Piece) < piece_bitboard) {
        piece_bitboard = piece_bitboard ^ Piece;
        piece_bitboard = piece_bitboard | Square;
    }
    return piece_bitboard;
}

// Mouse callback function to handle piece selection and movement
void onMouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Calculate the square clicked
        int squareX = x / GRIDSIZE;
        int squareY = y / GRIDSIZE; // Flip the Y-coordinate

        // Calculate the index of the selected square
        int selectedSquareIndex = squareX + squareY * 8;


        if (selectedPiece == 0) {
            // If no piece is selected, check if there is a piece on the selected square
            printf("seleted: %c%d\n", squareX + 'A', 8 - squareY);
            if (((global_bitboards.white_pieces | global_bitboards.black_pieces) & power(2, selectedSquareIndex)) != 0) {
                selectedPiece = power(2, selectedSquareIndex);
            }
        } else {
            // If a piece is already selected, set the destination square
            selectedSquare = power(2, selectedSquareIndex);
    
            global_bitboards.white_pieces = update_bitboard(global_bitboards.white_pieces, selectedPiece, selectedSquare);
            global_bitboards.black_pieces = update_bitboard(global_bitboards.black_pieces, selectedPiece, selectedSquare);
            global_bitboards.rook = update_bitboard(global_bitboards.rook, selectedPiece, selectedSquare);
            global_bitboards.knight = update_bitboard(global_bitboards.knight, selectedPiece, selectedSquare);
            global_bitboards.bishop = update_bitboard(global_bitboards.bishop, selectedPiece, selectedSquare);
            global_bitboards.queen = update_bitboard(global_bitboards.queen, selectedPiece, selectedSquare);
            global_bitboards.king = update_bitboard(global_bitboards.king, selectedPiece, selectedSquare);
            global_bitboards.pawn = update_bitboard(global_bitboards.pawn, selectedPiece, selectedSquare);

            printf("moved: %c%d\n", squareX + 'A', 8 - squareY);
            rewind_chess_board(true, true);
            selectedSquare = 0;
            selectedPiece = 0;
            display();
        }
    }
}

// Keyboard callback function to cancel the selection
void onKeyPress(unsigned char key, int x, int y)
{
    if (key == 'c') { // 27 is the ASCII code for the Escape key
        printf("cancelled, (%d, %d)\n", x, y);
        selectedPiece = 0; // Cancel the selection
        selectedSquare = 0;
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