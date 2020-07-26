##
## EPITECH PROJECT, 2020
## Repos
## File description:
## Makefile
##

CPP	=	g++

NCURSES	=	nCurses

SFML	= sfml

SDL = sdl

all:	$(NCURSES)	$(SDL)	$(SFML)

$(NCURSES):
	$(CPP) -fPIC -c nCurses.cpp -lncurses
	$(CPP) -shared -o lib_arcade_ncurses.so nCurses.o -lncurses

$(SFML):
	$(CPP) -fPIC -c SFML.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	$(CPP) -shared -o lib_arcade_sfml.so SFML.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

$(SDL):
	$(CPP) -fPIC -c SDL.cpp -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
	$(CPP) -shared -o lib_arcade_sdl.so SDL.o -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all