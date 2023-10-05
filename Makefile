##
## EPITECH PROJECT, 2022
## make file
## File description:
## make file
##

SRC	=	src/main.c	                        \
		src/utils.c                         \
        src/main_loop/prepare_main_loop.c   \
        src/board/create_board.c            \
		src/display/draw_board.c 			\
		src/display/input_handler.c


OBJ	=	$(SRC:.c=.o)

NAME	=	ChessEngine

CFLAGS += -W -Wall -Wextra -Wshadow -Wimplicit -Werror -g

CPPFLAGS += -I./include

all:	$(NAME)
PHONY	+= all

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) -lGL -lGLU -lglut -lSOIL

clean:
	rm -f $(OBJ)
PHONY	+= clean

fclean:	clean
	rm -f $(NAME)

PHONY	+= fclean

re:	fclean all
PHONY	+= re

.PHONY:	$(PHONY)
