/*
** EPITECH PROJECT, 2020
** IDisplayModule.hpp
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include <string>
#include <vector>
#include <memory>
#include "../games/ICharacter.hpp"

class IDisplayModule {
    public:
        virtual ~IDisplayModule() = default;
        virtual void init() = 0;
        virtual void stop() = 0;
        virtual int menu() = 0;
        virtual void drawMap(std::string str, std::string gameName) = 0;
        virtual void drawCharacters(const std::vector<ICharacter *> *chars) = 0;
        virtual void drawScore(int score) = 0;
        virtual int gameover() = 0;
        virtual int getInput() = 0;
        virtual const std::string &getScoreName() const = 0;
        virtual const std::string &getName() const = 0;
        virtual std::string getScore() const = 0;
    protected:
        std::string scoreName;
    private:
};

#endif /* !IDISPLAYMODULE_HPP_ */
