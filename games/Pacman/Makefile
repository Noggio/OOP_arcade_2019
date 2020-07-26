##
## EPITECH PROJECT, 2020
## Repos
## File description:
## Makefile
##

CPP	=	g++

PACMAN	=	Pacman

all:	$(PACMAN)

$(PACMAN):
	$(CPP) -fPIC -c Ghost.cpp Pacman.cpp Nomnom.cpp Pacgums.cpp
	$(CPP) -shared -o lib_arcade_pacman.so Ghost.o Pacman.o Nomnom.o Pacgums.o
	mv lib_arcade_pacman.so ../

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all