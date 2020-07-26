##
## EPITECH PROJECT, 2020
## Repos
## File description:
## Makefile
##

CPP	=	g++

NIBBLER	=	nibbler

all:	$(NIBBLER)

$(NIBBLER):
	g++ -fPIC -c Apple.cpp Nibbler.cpp Snake.cpp
	g++ -shared -o lib_arcade_nibbler.so Apple.o Nibbler.o Snake.o
	mv lib_arcade_nibbler.so ../

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all