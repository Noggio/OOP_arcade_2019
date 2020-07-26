/*
** EPITECH PROJECT, 2020
** Nibbler.cpp
** File description:
** Nibbler
*/

#include "Nibbler.hpp"
#include <iostream>
#include "../../Headers/IGame.hpp"

Nibbler::Nibbler()
{
    this->score = 0;
    this->apple = new Apple;
    this->snake = new Snake;
    this->chars.push_back((this->snake));
    this->chars.push_back((new Snake(this->chars.back()->getPosition().at(0) - 32, this->chars.back()->getPosition().at(1), this->snake->current_dir)));
    this->chars.push_back((new Snake(this->chars.back()->getPosition().at(0) - 32, this->chars.back()->getPosition().at(1), this->snake->current_dir)));
    this->chars.push_back((new Snake(this->chars.back()->getPosition().at(0) - 32, this->chars.back()->getPosition().at(1), this->snake->current_dir)));
    this->chars.push_back((this->apple));
}

bool Nibbler::update(int event)
{
    for (int i = this->chars.size() - 2; i > 0; i--) {
        this->movement(this->chars, i);
    }
    this->movement(event);
    if (this->isEating()) {
        this->score += 100;
        this->chars.pop_back();
        this->addNewCell();
        this->apple = new Apple(32 * (std::rand() % 40), 32 * (std::rand() % 10 + 1));
        this->chars.push_back(this->apple);
    }
    return this->isAlive() && this->snake->isAlive();
}

bool Nibbler::isAlive()
{
    for (int i = this->chars.size() - 2; i > 2; i--) {
        if (this->chars.at(0)->getPosition() == this->chars.at(i)->getPosition())
            return false;
    }
    return true;
}

bool Nibbler::isEating()
{
    if (this->chars.at(0)->getPosition() == this->chars.back()->getPosition())
        return true;
    else
        return false;
}

void Nibbler::movement(std::vector<ICharacter *> block, int i)
{
    this->chars.at(i)->setPosition(this->chars.at(i - 1)->getPosition().at(0), this->chars.at(i - 1)->getPosition().at(1));
}

void Nibbler::movement(int dir) {
    this->snake = reinterpret_cast<Snake *>(this->chars.at(0));
    if (dir == 0 || dir == 1 || dir == 2 || dir == 3) {
        if ((this->snake->current_dir == 0 && dir != 1) ||
            (this->snake->current_dir == 1 && dir != 0) ||
            (this->snake->current_dir == 2 && dir != 3) ||
            (this->snake->current_dir == 3 && dir != 2))
            this->snake->current_dir = dir;
    }

    if (this->snake->current_dir == 0)
        this->chars.at(0)->setPosition(this->chars.at(0)->getPosition().at(0), this->chars.at(0)->getPosition().at(1) - 32);
    if (this->snake->current_dir == 1)
        this->chars.at(0)->setPosition(this->chars.at(0)->getPosition().at(0), this->chars.at(0)->getPosition().at(1) + 32);
    if (this->snake->current_dir == 2)
        this->chars.at(0)->setPosition(this->chars.at(0)->getPosition().at(0) - 32, this->chars.at(0)->getPosition().at(1));
    if (this->snake->current_dir == 3)
        this->chars.at(0)->setPosition(this->chars.at(0)->getPosition().at(0) + 32, this->chars.at(0)->getPosition().at(1));
}

void Nibbler::addNewCell()
{
    int x = this->chars.at(0)->getPosition().at(0);
    int y = this->chars.at(0)->getPosition().at(1);
    std::reverse(this->chars.begin(), this->chars.end());
    Snake *newSnake = new Snake(x, y, this->snake->current_dir);
    this->chars.push_back(newSnake);
    for (int i = 0; i < this->chars.size() - 1; i++) {
        if (reinterpret_cast<Snake *>(&this->chars.at(i))->current_dir == 3 || reinterpret_cast<Snake *>(&this->chars.at(i))->current_dir == 2)
            this->chars.at(i)->position[0] -= 32;
        else
            this->chars.at(i)->position[0] += 32;
        
    }
    std::reverse(this->chars.begin(), this->chars.end());
}

Nibbler::~Nibbler()
{
}

extern "C" IGame *create_game() {
    return new Nibbler();
}