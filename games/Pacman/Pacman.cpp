/*
** EPITECH PROJECT, 2020
** Pacman.cpp
** File description:
** Pacman
*/

#include "Pacman.hpp"

Pacman::Pacman()
{
    std::cout << "Constructing Pacman..." << std::endl;
    this->nomnom = new Nomnom;
    this->ghost = new Ghost;
    this->chars.push_back(this->nomnom);
    this->chars.push_back(this->ghost);
    this->chars.push_back(new Ghost(224 + 32, 224));
    this->chars.push_back(new Ghost(224 - 32, 224));
    this->chars.push_back(new Ghost(224, 224 + 32));

    this->score = 0;
    this->timer = 0;
    this->load_map();
}

void Pacman::load_map()
{
    std::string buffer, map;
    std::ifstream file;
    int y = 0;
    int x;
    file.open("pacman.txt");
    if (!file.is_open())
        std::cout << "Can't open map !" << std::endl;
    while (file.is_open() && getline(file, buffer)){
        map += buffer;
        map += '\n';
    }
    for (int i = 0; i != map.length(); i++) {
        if (map.at(i) == '\n') {
            y++;
            x = 0;
        }
        if (map.at(i) == '#') {
            this->map.push_back(std::pair<int, int>(x * 32, y * 32));
            x++;
        } else if (map.at(i) == '.') {
            this->chars.push_back(new Pacgums(x * 32, y * 32));
            x++;
        } else if (map.at(i) == 'X') {
            this->chars.push_back(new Pacgums(x *32, y * 32, true));
            x++;
        } else if (map.at(i) == ' ')
            x++;
    }
}

bool Pacman::update(int event)
{
    this->pacman_movement(event);
    this->timerEat();
    this->ghost_movement();
    return isEatingPacgum();
}

void Pacman::ghost_movement() {
    Ghost *move;
    int r, x, y = 0;
    for (auto it = this->chars.begin() + 1; it != this->chars.begin() + 5; it++) {
        move = reinterpret_cast<Ghost *>(*it);
        r = (rand() % 2);
        if (r == 0) {
            x = (rand() % 3) - 1;
            move->position.at(0) += x * 32;
            if (this->ghost_WallHit(move))
                move->position.at(0) -= x * 32;
        } else {
            y = (rand() % 3) - 1;
            move->position.at(1) += y * 32;
            if (this->ghost_WallHit(move))
                move->position.at(1) -= y * 32;
        }
    }
    // for (auto it = this->chars.begin() + 1; it != this->chars.begin() + 6; it++) {
    //     move = reinterpret_cast<Ghost *>(*it);
    // }
}

bool Pacman::ghost_WallHit(Ghost *ghost)
{
    for (int i = 0; i < this->map.size(); i++) {
        if ((ghost->getPosition().at(0) == this->map.at(i).first && ghost->getPosition().at(1) == this->map.at(i).second) ||
            ghost->getPosition().at(1) == 0)
            return true;
    }
    return false;
}

void Pacman::timerEat()
{
    if (reinterpret_cast<Nomnom *>(this->chars.at(0))->canEat == true && this->timer < 15) {
        this->timer++;
    } else if (this->timer >= 15) {
        this->timer = 0;
        reinterpret_cast<Nomnom *>(this->chars.at(0))->canEat = false;
    }
}

bool Pacman::isEatingPacgum()
{
    Pacgums *gum;
    int i = 1;
    for (auto it = this->chars.begin()+1; it != this->chars.end(); it++, i++) {
        gum = reinterpret_cast<Pacgums *>(*it);
        if (this->chars.at(0)->getPosition() == gum->getPosition() && gum->isEatable == true && gum->isSuper == false) {
            this->chars.erase(this->chars.begin() + i);
            this->score += 10;
            return true;
        } else if (this->chars.at(0)->getPosition() == gum->getPosition() && gum->isEatable == true && gum->isSuper == true){
            reinterpret_cast<Nomnom *>(this->chars.at(0))->canEat = true;
            this->chars.erase(this->chars.begin() + i);
            this->score += 20;
            return true;
        } else if (this->chars.at(0)->getPosition() == gum->getPosition() && gum->isEatable == false &&
                    reinterpret_cast<Nomnom *>(this->chars.at(0))->canEat == false) {
            return false;
        } else if (this->chars.at(0)->getPosition() == gum->getPosition() && gum->isEatable == false &&
                    reinterpret_cast<Nomnom *>(this->chars.at(0))->canEat == true) {
            this->chars.erase(this->chars.begin() + i);
            this->score += 100;
            return true;
        }
    }
    return true;
}

bool Pacman::isWallHit()
{
    for (int i = 0; i < this->map.size(); i++) {
        if (this->chars.at(0)->getPosition().at(0) == this->map.at(i).first && this->chars.at(0)->getPosition().at(1) == this->map.at(i).second
            || this->chars.at(0)->getPosition().at(1) == 0)
            return true;
    }

    return false;
}

void Pacman::pacman_movement(int dir) {
    if (dir == 1) {
        this->chars.at(0)->position.at(1) += 32;
        this->chars.at(0)->texture = "./lib/img_pacman/nomnom_d.png";
        if (this->isWallHit()) {
            this->chars.at(0)->position.at(1) -= 32;
            this->chars.at(0)->texture = "./lib/img_pacman/nomnom.png";

        }
    }
    else if (dir == 0) {
        this->chars.at(0)->position.at(1) -= 32;
        this->chars.at(0)->texture = "./lib/img_pacman/nomnom_u.png";
        if (this->isWallHit()) {
            this->chars.at(0)->position.at(1) += 32;
            this->chars.at(0)->texture = "./lib/img_pacman/nomnom.png";
        }
    }
    else if (dir == 3) {
        this->chars.at(0)->position.at(0) += 32;
        this->chars.at(0)->texture = "./lib/img_pacman/nomnom_r.png";
        if (this->isWallHit()) {
            this->chars.at(0)->position.at(0) -= 32;
            this->chars.at(0)->texture = "./lib/img_pacman/nomnom.png";
        }
    }
    else if (dir == 2) {
        this->chars.at(0)->position.at(0) -= 32;
        this->chars.at(0)->texture = "./lib/img_pacman/nomnom.png";
        if (this->isWallHit()) {
            this->chars.at(0)->position.at(0) += 32;
            this->chars.at(0)->texture = "./lib/img_pacman/nomnom.png";
        }
    }
}

Pacman::~Pacman()
{

}

extern "C" IGame *create_game() {
    return new Pacman();
}