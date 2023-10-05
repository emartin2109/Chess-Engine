#include "board.h"
#include "display.h"
#include "define.h"

void prepare_main_loop(int ac, char **av)
{
    create_board(START_POS);
    init_display(ac, av);
}