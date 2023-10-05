#include "utils.h"
#include "global.h"
#include "define.h"
#include "include.h"

void create_board (char *fen)
{
    unsigned long long int cursor = 0;
    unsigned long long int power_value = 2;
    global_bitboards.white_pieces = 0;
    global_bitboards.black_pieces = 0;
    global_bitboards.pawn  = 0;
    global_bitboards.rook = 0;
    global_bitboards.knight = 0;
    global_bitboards.bishop = 0;
    global_bitboards.queen = 0;
    global_bitboards.king = 0;
    for (int i = 0; fen[i] != '\0'; i++) {
        if (fen[i] >= '1' && fen[i] <= '8') {
            int emptySquares = fen[i] - '0';

            cursor += emptySquares;
        } else if (fen[i] != '/') {
            if (fen[i] > 'a' && fen[i] < 'z')
                global_bitboards.white_pieces += power(power_value, cursor);
            if (fen[i] > 'A' && fen[i] < 'Z')
                global_bitboards.black_pieces += power(power_value, cursor);

            if (fen[i] == 'p' || fen[i] == 'P')
                global_bitboards.pawn += power(power_value, cursor);
            if (fen[i] == 'r' || fen[i] == 'R')
                global_bitboards.rook += power(power_value, cursor);
            if (fen[i] == 'n' || fen[i] == 'N')
                global_bitboards.knight += power(power_value, cursor);
            if (fen[i] == 'b' || fen[i] == 'B')
                global_bitboards.bishop += power(power_value, cursor);
            if (fen[i] == 'q' || fen[i] == 'Q')
                global_bitboards.queen += power(power_value, cursor);
            if (fen[i] == 'k' || fen[i] == 'K')
                global_bitboards.king += power(power_value, cursor);
    
            cursor++;
        }
    }
}