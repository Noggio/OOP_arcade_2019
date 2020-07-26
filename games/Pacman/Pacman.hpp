/*
** EPITECH PROJECT, 2020
** Pacman.hpp
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "../../Headers/IGame.hpp"
#include "Ghost.hpp"
#include "Nomnom.hpp"
#include "Pacgums.hpp"
#include <iostream>
#include <fstream>

class Pacman : public IGame
{
	public:
		Pacman();
		~Pacman();
		bool update(int event);
        int getScore() const {
            return this->score;
        };
		const std::string getWallPath() const {
            return "./lib/img_nibbler/wall.png";
        }
        void movement(std::vector<ICharacter *> block, int i);
        const std::string &getName() const {
            std::string *str = new std::string("pacman");
            return *str;
        };
        const std::vector<ICharacter *> *getChar() const {
            return &this->chars;
        }
        void load_map();
        bool isWallHit();
        void pacman_movement(int dir);
        void ghost_movement();
        bool isEatingPacgum();
        bool isEatingGhost();
        void timerEat();
        bool ghost_WallHit(Ghost *ghost);
        int timer;
		protected:
		private:
			std::vector<std::string> paths;
			std::vector<ICharacter *> chars;
			Ghost *ghost;
			Nomnom *nomnom;
            std::vector<std::pair<int, int>> map;
};

#endif /* !PACMAN_HPP_ */