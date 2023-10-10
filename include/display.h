/*
** EPITECH PROJECT, 2023
** ChessEngine
** File description:
** display
*/

#ifndef DISPLAY_H_
    #define DISPLAY_H_

    #include "include.h"

    void init_display(int ac, char **av);
    void display(void);
    void drawChessboard(void);
    void onMouseClick(int button, int state, int x, int y);
    void onKeyPress(unsigned char key, int x, int y);


#endif /* !DISPLAY_H_ */
