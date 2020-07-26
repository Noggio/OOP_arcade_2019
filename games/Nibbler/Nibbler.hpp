/*
** EPITECH PROJECT, 2020
** Nibbler.hpp
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_
#include "../../Headers/IGame.hpp"
#include "./Snake.hpp"
#include "./Apple.hpp"
#include "../ICharacter.hpp"
#include <string>
#include <list>
#include <iostream>
#include <algorithm>

class Nibbler : public IGame {
    public:
        Nibbler();
        ~Nibbler();
        bool update(int event);
        void addNewCell();
        void movement(int dir);
        bool isEating();
        bool isAlive();
        const std::string getWallPath() const {
            return "./lib/img_nibbler/wall.png";
        }
        int getScore() const {
            return this->score;
        };
        void movement(std::vector<ICharacter *> block, int i);
        const std::string &getName() const {
            std::string *str = new std::string("snake");
            return *str;
        };
        const std::vector<ICharacter *> *getChar() const {
            return &this->chars;
        }
    protected:
    private:
        std::vector<std::string> paths;
        std::vector<ICharacter *> chars;
        Apple *apple;
        Snake *snake;
};

#endif /* !NIBBLER_HPP_ */
