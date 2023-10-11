#include "board.h"
#include "display.h"
#include "define.h"
#include "precompute.h"
#include "global.h"
#include "test.h"

void prepare_main_loop(int ac, char **av)
{
    global_fen_meta_data.white_turn = 1;
    global_fen_meta_data.en_passant = 0;
    global_fen_meta_data.castle_right = 15;

    precompute_filter();
    precompute_distance_to_edge();
    precompute_power();
    create_board(START_POS);

    recursive_params_glo = get_recursive_params_glo();
    // init_display(ac, av);
    printf("%llu\n", count_moves_at_depth(0, get_recursive_params()));
    ac = ac;
    av = av;
}