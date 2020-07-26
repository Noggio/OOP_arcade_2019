/*
** EPITECH PROJECT, 2020
** Snake.hpp
** File description:
** Snake
*/

#include "Snake.hpp"  

Snake::Snake()
{
    this->texture = "./lib/img_nibbler/snake.png";
    this->size = 1;
    this->position.push_back(21 * 32);
    this->position.push_back(6 * 32);
    this->current_dir = Direction::RIGHT;
    std::cout << "Snake is constructed " << std::endl;
}

Snake::Snake(int x, int y, int dir)
{
    this->texture = "./lib/img_nibbler/snake.png";
    this->size = 1;
    this->position.push_back(x);
    this->position.push_back(y);
    this->current_dir = dir;
}

bool Snake::isAlive()
{
    if (this->getPosition().at(0) < 32 || this->getPosition().at(1) < 32 || this->getPosition().at(0) > 1280 - 96|| this->getPosition().at(1) > 384 - 64)
        return false;
    else
        return true;
}

bool Snake::isEating(int pos_x, int pos_y)
{
    if ((this->position.at(0) <= pos_x + 32 && this->position.at(0) >= pos_x) && (this->position.at(1) >= pos_y - 32 && this->position.at(1) <= pos_y))
        return true;
    else
        return false;
}

void Snake::hasEaten()
{
    std::cout << "Snake has eaten !!" << std::endl;
    this->size += 1;
}

void Snake::movement(int dir)
{
    if (dir != -1)
        current_dir = dir;
    
    if (current_dir == Direction::DOWN)
        this->position.at(1) += 32;
    else if (current_dir == Direction::UP)
        this->position.at(1) -= 32;
    else if (current_dir == Direction::RIGHT)
        this->position.at(0) += 32;
    else if (current_dir == Direction::LEFT)
        this->position.at(0) -= 32;
}

void Snake::setPosition(int x, int y)
{
    this->position.at(0) = x;
    this->position.at(1) = y;
}

std::vector<int> Snake::getPosition()
{
    return this->position;
}

Snake::~Snake()
{

}