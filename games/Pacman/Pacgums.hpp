/*
** EPITECH PROJECT, 2020
** Pacgums.hpp
** File description:
** Pacgums
*/

#include "../ICharacter.hpp"

class Pacgums : public ICharacter
{
	private:
	public:
		Pacgums(int x, int y);
		Pacgums(int x, int y, bool super);
		~Pacgums();
		std::vector<int> getPosition() {
			return this->position;
		};
		void setPosition(int x, int y);
		bool isEatable = true;
		bool isSuper = false;
};