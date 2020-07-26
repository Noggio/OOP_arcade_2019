/*
** EPITECH PROJECT, 2020
** Repos
** File description:
** Ghost
*/

#ifndef GHOST_HPP_
#define GHOST_HPP_

#include "../ICharacter.hpp"

class Ghost : public ICharacter {
    public:
        Ghost();
        Ghost(int x, int y);
        ~Ghost();
        std::vector<int> getPosition();
		void setPosition(int x, int y);
        bool isEatable = false;
    protected:
    private:
};

#endif /* !GHOST_HPP_ */
