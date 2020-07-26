/*
** EPITECH PROJECT, 2020
** Repos
** File description:
** nCurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include <ncurses.h>
#include <curses.h>
#include "../Headers/IDisplayModule.hpp"
#include "iostream"
#include "fstream"

class nCurses : public IDisplayModule
{
	public:
		nCurses();
		~nCurses();
		int menu();
		void drawMap(std::string, std::string gameName);
		void drawScore(int score);
        int gameover();
		void init() {
            std::cout << "NCurses Loaded !" << std::endl;
        };
        void stop() {
            std::cout << "NCurses deloaded !" << std::endl;
        };
		const std::string &getName() const {
            std::string *name = new std::string("nCurses");
            return *name;
        };
		const char *getPart(int) const;
		void drawCharacters(const std::vector<ICharacter *> *chars);
		const std::string &getScoreName() const {
			return this->scoreName;
		};
		std::string getScore() const;
		int getInput();
	protected:
		WINDOW *window;
	private:
};

#endif /* !NCURSES_HPP_ */
