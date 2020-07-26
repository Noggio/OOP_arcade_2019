/*
** EPITECH PROJECT, 2020
** Core.hpp
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_
#include "./IDisplayModule.hpp"
#include "./IGame.hpp"
#include "./DLLoader.hpp"
#include <vector>
#include <fstream>

class Core {
    public:
        Core(std::string path);
        ~Core();
        void menu();
        void events(int event);
        void play_game();
        void setScores(int score, std::string name);
        void loadScores();
        enum Commands {
            NOTHING = 0,
            PREV_LIB = 1,
            NEXT_LIB = 2,
            PREV_GAME = 3,
            NEXT_GAME = 4,
            RESTART_GAME = 5,
            GO_TO_MENU = 6,
            EXIT = 7
        };
        DLLoader<IDisplayModule> *lib;
    protected:
    private:
        IDisplayModule *loaded_lib;
        IGame *loaded_game;
        std::vector<std::string> games;
        std::vector<std::string> graph_libs;
        std::fstream file;
        std::string scores;
        size_t lib_index;
        size_t game_index;
};

#endif /* !CORE_HPP_ */
