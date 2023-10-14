#include "dictionary_generation.h"
#include "precompute.h"
#include "display.h"
#include "define.h"
#include "global.h"
#include "board.h"
#include "test.h"

void prepare_main_loop(int ac, char **av)
{
    // initialize variables manually until i update the create board_function
    global_fen_meta_data.white_turn = 1;
    global_fen_meta_data.en_passant = 0;
    global_fen_meta_data.castle_right = 15;

    // precompute stuff
    precompute_filter();
    precompute_distance_to_edge();
    precompute_power();
    generate_rook_lookup_table();

    // create board
    create_board(START_POS);

    recursive_params_glo = get_recursive_params_glo();
    // init_display(ac, av);
    printf("%llu\n", count_moves_at_depth(0, get_recursive_params()));

    // stuff so that werror stop annoying me
    ac = ac;
    av = av;
}