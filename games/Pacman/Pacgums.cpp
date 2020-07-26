/*
** EPITECH PROJECT, 2020
** Pacgums.cpp
** File description:
** Pacgums
*/

#include "Pacgums.hpp"  

Pacgums::Pacgums(int x, int y)
{
    this->size = 1;
    this->texture = "./lib/img_pacman/point.png";
    this->position.push_back(x);
    this->position.push_back(y);
}

Pacgums::Pacgums(int x, int y, bool super)
{
    this->size = 1;
    this->texture = "./lib/img_pacman/point.png";
    this->position.push_back(x);
    this->position.push_back(y);
    this->isSuper = super;
}

void Pacgums::setPosition(int x, int y)
{
    this->position.at(0) = x;
    this->position.at(1) = y;
}

Pacgums::~Pacgums()
{

}