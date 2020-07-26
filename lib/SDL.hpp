/*
** EPITECH PROJECT, 2020
** SDL.hpp
** File description:
** SDL
*/

#include <iostream>
#include "../Headers/IDisplayModule.hpp"
#include "../games/ICharacter.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>

class SDL : public IDisplayModule
{
	public:
		SDL();
		~SDL();
		void init() {
            std::cout << "SDL Loaded !" << std::endl;
        };
        void stop() {
            std::cout << "SDL deloaded !" << std::endl;
        };
        const std::string &getName() const {
            std::string *name = new std::string("SDL");
            return *name;
        };
		const std::string &getScoreName() const {
			return this->scoreName;
		};
		int menu();
		void drawMap(std::string, std::string gameName);
		void drawCharacters(const std::vector<ICharacter *> *chars);
		void drawScore(int score);
		std::string getScore() const;
	    int getInput();
        int gameover();
		void init_button();
	protected:
	private:
		SDL_Window *window;
		SDL_Event event;
		bool run;
		int posx;
		int posy;
		int Secondposx;
		int Secondposy;
		bool pacman;
		bool nibbler;
		bool gameOver;
		int musicScore;
		SDL_Renderer *rend;
		SDL_Surface *img_pacman;
		SDL_Surface *img_nibbler;
		SDL_Surface *img_exit;
		SDL_Surface *img_wall;
		SDL_Surface *img_background;
		SDL_Surface *img_back_pacman;
		SDL_Surface *img_menu;
		SDL_Surface *img_restart;
		SDL_Surface *img_exit_over;
		SDL_Texture *txt_pacman;
		SDL_Texture *txt_nibbler;
		SDL_Texture *txt_exit;
		SDL_Texture *texture_wall;
		SDL_Texture *txt_background;
		SDL_Texture *txt_back_pacman;
		SDL_Texture *txt_menu;
		SDL_Texture *txt_restart;
		SDL_Texture *txt_exit_over;
		SDL_Rect destPac;
		SDL_Rect destNib;
		SDL_Rect destQuit;
		SDL_Rect destMenu;
		SDL_Rect destRestart;
		SDL_Rect destQuitOver;
		SDL_Rect destWall;
		std::vector<SDL_Rect> vect_walls;
        std::vector<SDL_Rect> vect_food;
		SDL_AudioSpec enter;
		Uint32 enterLength;
		Uint8 *enterBuffer;
		SDL_AudioDeviceID enterDevice;
		SDL_AudioSpec apple;
		Uint32 appleLength;
		Uint8 *appleBuffer;
		SDL_AudioDeviceID appleDevice;
		SDL_AudioSpec _menu;
		Uint32 menuLength;
		Uint8 *menuBuffer;
		SDL_AudioDeviceID menuDevice;
		SDL_AudioSpec eatPacman;
		Uint32 eatLength;
		Uint8 *eatBuffer;
		SDL_AudioDeviceID eatDevice;
		SDL_AudioSpec dead;
		Uint32 deadLength;
		Uint8 *deadBuffer;
		SDL_AudioDeviceID deadDevice;
		SDL_AudioSpec deadSnake;
		Uint32 deadSnakeLength;
		Uint8 *deadSnakeBuffer;
		SDL_AudioDeviceID deadSnakeDevice;
};