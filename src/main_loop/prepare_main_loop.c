#include "board.h"
#include "display.h"
#include "define.h"
#include "precompute.h"
#include "global.h"

void prepare_main_loop(int ac, char **av)
{
    global_fen_meta_data.white_turn = 1;
    global_fen_meta_data.en_passant = 0;
    global_fen_meta_data.castle_right = 15;

    precompute_filter();
    precompute_distance_to_edge();
    precompute_power();
    create_board(START_POS);
    init_display(ac, av);
}