/*
** EPITECH PROJECT, 2020
** main.cpp
** File description:
** main
*/

#include "./Headers/DLLoader.hpp"
#include "Headers/IDisplayModule.hpp"
#include "Headers/Core.hpp"
#include <string>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "You need to provide a dynamic library !" << std::endl;
        exit (84);
    } else if (argc > 2) {
        std::cout << "Too many arguments !" << std::endl;
        exit (84);
    }
    std::string const path = argv[1];
    if (path.substr(path.size() - 3, path.size()) == ".so") {
        Core *core = new Core(path);
        core->menu();
        core->~Core();
    } else {
        std::cout << "You must provide a valid library" << std::endl;
        return (84);
    }
    
    return 0;
}