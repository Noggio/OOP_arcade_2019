/*
** EPITECH PROJECT, 2020
** Core.cpp
** File description:
** Core
*/

#include "./Headers/Core.hpp"
#include <unistd.h>
#include <thread>
#include <chrono>
#include <sstream>

Core::Core(std::string path)
{
    this->games.push_back("./games/lib_arcade_nibbler.so");
    this->games.push_back("./games/lib_arcade_pacman.so");
    this->graph_libs.push_back("./lib/lib_arcade_sfml.so");
    this->graph_libs.push_back("./lib/lib_arcade_sdl.so");
    this->graph_libs.push_back("./lib/lib_arcade_ncurses.so");
    for (size_t i = 0; i < graph_libs.size(); i++) {
        if (path == graph_libs.at(i)) {
            this->lib = new DLLoader<IDisplayModule>(path);
            this->loaded_lib = lib->getInstance("createLib");
            this->lib_index = i;
        }
    }
    if (!this->loaded_lib)
        exit(84);
}

void Core::menu()
{
    this->loadScores();
    if (this->loaded_lib->menu() == 0) {
        DLLoader<IGame> *game = new DLLoader<IGame>((this->games.at(0)));
        this->loaded_game = game->getInstance("create_game");
        this->game_index = 0;

    } else if (this->loaded_lib->menu() == 1) {
        DLLoader<IGame> *game = new DLLoader<IGame>((this->games.at(1)));
        this->loaded_game = game->getInstance("create_game");
        this->game_index = 1;
    }
    if (this->loaded_game != NULL)
        this->play_game();
    else {
        std::cout << "Bye !" << std::endl;
        this->loaded_lib->~IDisplayModule();
        exit (0);
    }
}

void Core::play_game()
{
    bool isRunning = true;
    int event = -1;
    while (event != Core::Commands::EXIT && isRunning && this->loaded_game) {
        std::string paths = this->loaded_game->getWallPath();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        event = this->loaded_lib->getInput();
        isRunning = this->loaded_game->update(event);
        loaded_lib->drawMap(paths, this->loaded_game->getName());
        this->loaded_lib->drawCharacters(this->loaded_game->getChar());
        this->loaded_lib->drawScore(this->loaded_game->getScore());
        if (event == 6) {
            this->loaded_lib->~IDisplayModule();
            this->lib_index++;
            if (this->lib_index >= this->graph_libs.size())
                this->lib_index = 0;
            DLLoader<IDisplayModule> *lib = new DLLoader<IDisplayModule>(this->graph_libs.at(this->lib_index));
            this->loaded_lib = lib->getInstance("createLib");
        } else if (event == 5) {
            this->loaded_game->~IGame();
            this->game_index++;
            if (this->game_index >= this->games.size())
                this->game_index = 0;
            DLLoader<IGame> *game = new DLLoader<IGame>((this->games.at(this->game_index)));
            this->loaded_game = game->getInstance("create_game");
        } else if (event == 4) {
            this->loaded_game->~IGame();
            DLLoader<IGame> *game = new DLLoader<IGame>((this->games.at(this->game_index)));
            this->loaded_game = game->getInstance("create_game");
        } else if (event == 8) {
            this->loaded_game->~IGame();
            this->menu();
        }
    }
    if (!isRunning) {
        event = this->loaded_lib->gameover();
        if (event == 4) {
            this->loaded_game->~IGame();
            DLLoader<IGame> *game = new DLLoader<IGame>((this->games.at(this->game_index)));
            this->loaded_game = game->getInstance("create_game");
            this->play_game();
        } else if (event == 10) {
            this->loaded_game->~IGame();
            this->loaded_game = NULL;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            this->menu();
        }
    }
    if (this->loaded_lib->getScoreName() != "")
        this->setScores(this->loaded_game->getScore(), this->loaded_lib->getScoreName());
}

void Core::setScores(int score, std::string name)
{
    std::list<std::string> scores_list;
    std::list<int> int_l;
    int newLine = 0;
    std::stringstream ss;
    int found;
    std::string temp;
    for (size_t i = 0; i <=  this->scores.length(); i++) {
        if (i == this->scores.length()) {
            scores_list.push_back(this->scores.substr(newLine, i - 1));
            break;
        }
        if (this->scores[i] == '\n' || this->scores[i] == '\r') {
            scores_list.push_back(this->scores.substr(newLine, i - newLine));
            newLine = i;
        }
    }
    for (auto it = scores_list.begin(); it != scores_list.end(); it++) {
        ss << *it;
        while (!ss.eof()) {
            ss >> temp;
            if (std::stringstream(temp) >> found)
                int_l.push_back(found);
        }
        temp = "";
        ss.clear();
        ss.str(std::string());
    }
    std::list<std::string>::iterator iter = scores_list.begin();
    for (auto it = int_l.begin(); it != int_l.end(); it++, iter++) {
        if (score >= *it) {
            scores_list.insert(iter, '\n' + name + " " + std::to_string(score));
            break;
        }
    }

    std::filebuf fb;
    fb.open("scores.arcd", std::ios::out);
    std::ostream os(&fb);
    for (auto it = scores_list.begin(); it != scores_list.end(); it++) {
        if (os) {
            os.write(it->c_str(), it->length());
        }
        else
            std::cout << "OOOOOPS" << std::endl;
    }
    if (scores.length() == 0) {
        os << name + " " + std::to_string(score);
    }
}

void Core::loadScores()
{
    this->file.open("./scores.arcd");
    if(!this->file)
        std::cout << "BOUUUUG" << std::endl;
    this->file.seekg(0, this->file.end);
    int fsize = file.tellg();
    this->file.seekg(0, this->file.beg);

    if (fsize != 0) {
        char *buf = new char [fsize + 1];
        file.read(buf, fsize + 1);
        this->scores = buf;
    }
}

Core::~Core()
{
    //this->file.close();
    this->loaded_game->~IGame();
    this->loaded_lib->~IDisplayModule();
    this->lib->~DLLoader();
}