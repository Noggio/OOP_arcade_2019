/*
** EPITECH PROJECT, 2020
** Apple.hpp
** File description:
** Apple
*/

#include <vector>
#include <string>
#include "../ICharacter.hpp"

class Apple : public ICharacter
{
	private:
	public:
		Apple();
		Apple(int x, int y);
		std::vector<int> getPosition();
		void setPosition(int x, int y);
		~Apple();
		Apple &operator=(Apple const &copy) {
			if (&copy != this) {
                this->position = copy.position;
				this->size = copy.size;
				this->texture = copy.texture;
			}
            return *this;
		}
};