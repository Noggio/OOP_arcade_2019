/*
** EPITECH PROJECT, 2020
** Snake.hpp
** File description:
** Snake
*/

#include <vector>
#include <string>
#include <iostream>
#include "../ICharacter.hpp"

class Snake : public ICharacter
{
	private:
		enum Direction {
			UP = 0,
			DOWN = 1,
			LEFT = 2,
			RIGHT = 3
		};
	public:
		int current_dir;
		Snake();
		Snake(int x , int y, int dir);
		bool isAlive();
		bool isEating(int pos_x, int pos_y);
		void hasEaten();
		void movement(int dir);
		void setPosition(int x, int y);
		std::vector<int> getPosition();
		~Snake();
		Snake &operator=(Snake const &copy) {
			if (&copy != this) {
                this->position = copy.position;
				this->size = copy.size;
				this->texture = copy.texture;
				this->current_dir = copy.current_dir;
			}
			std::cout << "Snake copied" << std::endl;
            return *this;
		}
};