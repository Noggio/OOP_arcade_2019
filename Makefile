##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## generic Makefile
##

SRC	=	main.cpp	\
		Core.cpp

CC	=	g++

NAME	=	arcade

OBJ	=	$(SRC:.cpp=.o)

CFLAGS	=	-Wall -Wextra -ldl -g3

all:	core	games	graphicals

core:
	$(CC) -o $(NAME) $(SRC) $(CFLAGS)

.PHONY: games
games:
	cd games/Nibbler && make
	cd games/Pacman && make

graphicals:
	cd lib/ && make

clean:
	rm -f $(OBJ)
	cd lib/ && rm -f *.o && rm -f *.so
	cd games/Nibbler && rm -f *.o && rm -f *.so
	cd games/Pacman && rm -f *.o && rm -f *.so

fclean:	clean
	rm -f $(NAME)

re:	fclean all

