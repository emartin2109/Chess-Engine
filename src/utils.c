/*
** EPITECH PROJECT, 2023
** chess bot number 2
** File description:
** utils
*/

#include "chess.h"

char *get_input (void)
{
    char *line = NULL;
    size_t len = 0;
    int read = 0;
    read = getline(&line, &len, stdin);
    if (read == -1) {
        if (line != NULL)
            free(line);
        return NULL;
    }
    return line;
}