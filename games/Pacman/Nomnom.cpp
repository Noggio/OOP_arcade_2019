/*
** EPITECH PROJECT, 2020
** Repos
** File description:
** Nomnom
*/

#include "Nomnom.hpp"

Nomnom::Nomnom()
{
    this->size = 1;
    this->texture = "./lib/img_pacman/nomnom.png";
    this->current_dir = -1;
    this->position.push_back(96);
    this->position.push_back(64);
    this->canEat = false;
}

void Nomnom::movement(int dir)
{
    this->current_dir = dir;

    if (current_dir == Direction::DOWN)
        this->position.at(1) += 32;
    else if (current_dir == Direction::UP)
        this->position.at(1) -= 32;
    else if (current_dir == Direction::RIGHT)
        this->position.at(0) += 32;
    else if (current_dir == Direction::LEFT)
        this->position.at(0) -= 32;
}

void Nomnom::setPosition(int x, int y)
{
    this->position.at(0) = x;
    this->position.at(1) = y;
}

Nomnom::~Nomnom()
{

}
