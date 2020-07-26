/*
** EPITECH PROJECT, 2020
** Repos
** File description:
** Nomnom
*/

#ifndef NOMNOM_HPP_
#define NOMNOM_HPP_

#include "../ICharacter.hpp"

class Nomnom : public ICharacter {
    private:
        enum Direction {
			UP = 0,
			DOWN = 1,
			LEFT = 2,
			RIGHT = 3
		};
    public:
		int current_dir;
		bool canEat;
        Nomnom();
		void movement(int dir);
		void setPosition(int x, int y);
		std::vector<int> getPosition() {
			return this->position;
		};
        ~Nomnom();

    protected:
};

#endif /* !NOMNOM_HPP_ */
