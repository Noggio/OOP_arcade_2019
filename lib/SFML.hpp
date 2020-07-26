/*
** EPITECH PROJECT, 2020
** SFML.hpp
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "../Headers/IDisplayModule.hpp"
#include "../games/ICharacter.hpp"
#include <iostream>

class SFML : public IDisplayModule {
    public:
        SFML();
        ~SFML();
        int menu();
        void init() {
            std::cout << "SFML Loaded !" << std::endl;
        };
        void stop() {
            std::cout << "SFML deloaded !" << std::endl;
        };
        const std::string &getName() const {
            std::string *name = new std::string("SFML");
            return *name;
        };
        void drawMap(std::string str, std::string gameName);
        void drawCharacters(const std::vector<ICharacter *> *chars);
        void drawScore(int score);
        int gameover();
        int getInput();
        const std::string &getScoreName() const {
            return this->scoreName;
        };
        std::string getScore() const;
        sf::RenderWindow window;
    protected:
    private:
        bool nibbler;
        bool pacman;
        std::vector<sf::RectangleShape> vect_walls;
        sf::SoundBuffer enterBuffer;
        sf::Sound enterSound;
        sf::SoundBuffer appleBuffer;
        sf::Sound appleSound;
        sf::SoundBuffer eatBuffer;
        sf::Sound eatSound;
        sf::SoundBuffer overNibBuffer;
        sf::Sound overNibSound;
        sf::SoundBuffer overPacBuffer;
        sf::Sound overPacSound;
        sf::Music _menu;
        int musicScore;
        sf::Texture txt_background;
        sf::Sprite spr_background;
};

#endif /* !SFML_HPP_ */
