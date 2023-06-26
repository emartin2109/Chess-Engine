##
## EPITECH PROJECT, 2022
## make file
## File description:
## make file
##

SRC	=	src/main.c	\
		src/utils.c \
        src/chess.c \
        src/get_board.c \
        src/printer.c	\
		src/move.c	\
		src/generate_moves.c	\
		src/initialize.c


OBJ	=	$(SRC:.c=.o)

NAME	=	chess_bot

CFLAGS += -g -W -Wall -Wextra -Wshadow -Wimplicit

CPPFLAGS += -I./include

all:	$(NAME)
PHONY	+= all

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)
PHONY	+= clean

fclean:	clean
	rm -f $(NAME)

PHONY	+= fclean

re:	fclean all
PHONY	+= re

.PHONY:	$(PHONY)
