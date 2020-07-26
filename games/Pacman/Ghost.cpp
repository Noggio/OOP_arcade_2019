/*
** EPITECH PROJECT, 2020
** Repos
** File description:
** Ghost
*/

#include "Ghost.hpp"

Ghost::Ghost()
{
    this->position.push_back(224);
    this->position.push_back(224);
    this->size = 1;
    this->texture = "./lib/img_pacman/ghost.png";
}

Ghost::Ghost(int x, int y) {
    this->position.push_back(x);
    this->position.push_back(y);
    this->size = 1;
    this->texture = "./lib/img_pacman/ghost.png";
}

std::vector<int> Ghost::getPosition() {
    return this->position;
}

void Ghost::setPosition(int x, int y) {
    this->position.at(0) = x;
    this->position.at(1) = y;
}

Ghost::~Ghost()
{
}
