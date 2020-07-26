/*
** EPITECH PROJECT, 2020
** ICharacter.hpp
** File description:
** ICharacters
*/

#ifndef ICHARACTERS_HPP_
#define ICHARACTERS_HPP_
#include <vector>
#include <list>
#include <string>

class ICharacter {
    public:
        std::string texture;
        virtual std::vector<int> getPosition() = 0;
		virtual void setPosition(int x, int y) = 0;
        virtual ~ICharacter() = default;
        int size;
        std::vector<int> position;

    protected:
    private:
};

#endif /* !ICHARACTERS_HPP_ */
