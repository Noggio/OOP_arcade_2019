/*
** EPITECH PROJECT, 2020
** IGame.hpp
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_
#include "../games/ICharacter.hpp"
#include <memory>
#include <list>

class IGame {
    public:
        virtual ~IGame() = default;
        virtual bool update(int event) = 0;
        virtual const std::string &getName() const = 0;
        virtual const std::vector<ICharacter *> *getChar() const = 0;
        virtual const std::string getWallPath() const = 0;
        virtual int getScore() const = 0;
    protected:
        int score;
    private:
        std::vector<ICharacter *> chars;
};

#endif /* !IGAME_HPP_ */