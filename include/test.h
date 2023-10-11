/*
** EPITECH PROJECT, 2023
** Chess-Engine
** File description:
** test
*/

#ifndef TEST_H_
    #define TEST_H_

    #include "struct.h"

    recursive_params_t get_recursive_params();
    recursive_params_t get_recursive_params_glo();
    long long unsigned int count_moves_at_depth (int depth, recursive_params_t recursive_params);
    void run_test_move_nbr(unsigned char key, int x, int y);


#endif /* !TEST_H_ */
