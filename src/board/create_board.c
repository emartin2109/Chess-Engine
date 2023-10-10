#include "utils.h"
#include "global.h"
#include "define.h"
#include "include.h"

int convert_coord_to_number (char *fen)
{
    if (fen == NULL) return 0;
    int row = fen[0] - 'a';
    int column = 7 - fen[1];
    int result = row * 8 + column;
    return result;
}

void create_board (char *fen)
{
    int i = -1;
    int x = 7;
    int y = 7;

    global_bitboards.white_pieces = 0;
    global_bitboards.black_pieces = 0;
    global_bitboards.pawn  = 0;
    global_bitboards.rook = 0;
    global_bitboards.knight = 0;
    global_bitboards.bishop = 0;
    global_bitboards.queen = 0;
    global_bitboards.king = 0;
    // global_fen_meta_data.castle_right = 0;
    // global_fen_meta_data.en_passant = 0;
    // global_fen_meta_data.white_turn = true;
    global_highlighted_squares = 0;

    if (fen == NULL) return;

    while (fen[++i] != '\0' && fen[i] != ' ') {
        if (x == -1) x = 7;
        if (fen[i] >= '1' && fen[i] <= '8') {
            int emptySquares = fen[i] - '0';
            x -= emptySquares;
        } else if (fen[i] != '/') {
            if (fen[i] > 'A' && fen[i] < 'Z')
                global_bitboards.white_pieces += precomputed_values.power[y * 8 + x];
            if (fen[i] > 'a' && fen[i] < 'z')
                global_bitboards.black_pieces += precomputed_values.power[y * 8 + x];

            if (fen[i] == 'p' || fen[i] == 'P')
                global_bitboards.pawn += precomputed_values.power[y * 8 + x];
            if (fen[i] == 'r' || fen[i] == 'R')
                global_bitboards.rook += precomputed_values.power[y * 8 + x];
            if (fen[i] == 'n' || fen[i] == 'N')
                global_bitboards.knight += precomputed_values.power[y * 8 + x];
            if (fen[i] == 'b' || fen[i] == 'B')
                global_bitboards.bishop += precomputed_values.power[y * 8 + x];
            if (fen[i] == 'q' || fen[i] == 'Q')
                global_bitboards.queen += precomputed_values.power[y * 8 + x];
            if (fen[i] == 'k' || fen[i] == 'K')
                global_bitboards.king += precomputed_values.power[y * 8 + x];
            x--;
        }
        else if (fen[i] == '/') {
            y--;
        }
    }
    /*
    if (fen[i] != '\0' && fen[++i] == 'b') global_fen_meta_data.white_turn = false;
    while (fen[++i] != '\0' && fen[i] != ' ') {
        if (fen[i] == 'Q') global_fen_meta_data.castle_right += precomputed_values.power[0];
        if (fen[i] == 'K') global_fen_meta_data.castle_right += precomputed_values.power[1];
        if (fen[i] == 'q') global_fen_meta_data.castle_right += precomputed_values.power[2];
        if (fen[i] == 'k') global_fen_meta_data.castle_right += precomputed_values.power[3];
    }
    */
    /*
    while (fen[++i] != '\0' && fen[i] != ' ') {
        global_fen_meta_data.en_passant += precomputed_values.power[convert_coord_to_number(fen + i)];
        if (fen[++i] == '\0' || fen[i] == ' ') break;
    }
    */
}