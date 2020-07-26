/*
** EPITECH PROJECT, 2020
** Apple.cpp
** File description:
** Apple
*/

#include "Apple.hpp"
#include <iostream>

Apple::Apple()
{
    this->size = 1;
    this->position.push_back(8 * 32);
    this->position.push_back(3 * 32);
    this->texture = "./lib/img_nibbler/food.png";
}

Apple::Apple(int x, int y) {
    this->size = 1;
    this->position.push_back(x);
    this->position.push_back(y);
    this->texture = "./lib/img_nibbler/food.png";
}

void Apple::setPosition(int x, int y)
{
    this->position.at(0) = x;
    this->position.at(1) = y;
}

std::vector<int> Apple::getPosition()
{
    return this->position;
}

Apple::~Apple()
{
    std::cout << "Destructor" << std::endl;
}