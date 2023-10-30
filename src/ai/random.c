#include "struct.h"
#include "test.h"

int random_number(int min, int max) {
    if (max <= 0) return 0;
    return rand() % (max + 1 - min) + min;
}

recursive_params_t randy(int number_of_moves, recursive_params_t *move_list) 
{
    int move = random_number(0, number_of_moves - 1);
    return prepare_recursive_params(move_list[move]);
}