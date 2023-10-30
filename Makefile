##
## EPITECH PROJECT, 2022
## make file
## File description:
## make file
##

SRC	=	src/main.c	                        			\
		src/utils.c                         			\
        src/main_loop/prepare_main_loop.c   			\
        src/board/create_board.c            			\
		src/display/draw_board.c 						\
		src/display/input_handler.c						\
		src/generate_moves/generate_basic_moves.c		\
		src/generate_moves/generate_special_moves.c		\
		src/precompute/precompute_move_generation.c		\
		src/precompute/precompute_utility_values.c		\
		src/test/count_moves.c							\
		src/move/make_a_move.c							\
		src/move/update_bitboards.c						\
		src/dictionary_generation/lookup_table.c		\
		src/ai/random.c									\
		src/ai/mcts.c


OBJ	=	$(SRC:.c=.o)

NAME	=	ChessEngine

CFLAGS += -Wall -g

CPPFLAGS += -I./include

all:	$(NAME)
PHONY	+= all

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) -lGL -lGLU -lglut -lSOIL -lm

clean:
	rm -f $(OBJ)
PHONY	+= clean

fclean:	clean
	rm -f $(NAME)

PHONY	+= fclean

re:	fclean all
PHONY	+= re

.PHONY:	$(PHONY)
