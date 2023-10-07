/*
** EPITECH PROJECT, 2023
** .type_repo
** File description:
** utils
*/

#include "include.h"
#include "global.h"

long long unsigned int power (long long unsigned int number, long long unsigned int power)
{
    long long unsigned int result = 1;
    for (long long unsigned int i = 0; i < power; i++)
        result *= number;
    return result;
}

void print_bitboard(long long unsigned int n)
{
    int i = 0;
    long long unsigned int power_value = 63;
    while (power_value < 64) {
        if (n >= power(2, power_value)) {
            n -= power(2, power_value);
            printf("1");
        } else {
            printf("0");
        }
        if (++i == 8) {
            printf("\n");
            i = 0;
        }
        power_value--;
    }
}

