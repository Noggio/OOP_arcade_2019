/*
** EPITECH PROJECT, 2020
** SFML.cpp
** File description:
** SFML
*/

#include "SFML.hpp"
#include <fstream>

SFML::SFML()
{
    this->window.create(sf::VideoMode(1280, 720), "Arcade 2k20 Coronavirus-Safe");
    this->window.setFramerateLimit(60);
    this->enterBuffer.loadFromFile("lib/song_nibbler/enter-game.wav");
    this->enterSound.setBuffer(this->enterBuffer);
    this->appleBuffer.loadFromFile("lib/song_nibbler/apple.wav");
    this->appleSound.setBuffer(this->appleBuffer);
    this->overNibBuffer.loadFromFile("lib/song_nibbler/gameover.wav");
    this->overNibSound.setBuffer(this->overNibBuffer);
    this->overPacBuffer.loadFromFile("lib/song_pacman/dead.wav");
    this->overPacSound.setBuffer(this->overPacBuffer);
    this->eatBuffer.loadFromFile("lib/song_pacman/eat.wav");
    this->eatSound.setBuffer(this->eatBuffer);
    this->musicScore = 0;
    this->txt_background.loadFromFile("lib/img_nibbler/background.png");
    this->spr_background.setTexture(this->txt_background, true);
    this->spr_background.setPosition(0, 0);
    this->_menu.openFromFile("./lib/menu.wav");
    this->scoreName = "";
    this->pacman = false;
    this->nibbler = false;
}

int SFML::menu()
{
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");

    sf::Text startGame1("Play Snake", font, 30);
    startGame1.setFillColor(sf::Color::Black);
    startGame1.setPosition(sf::Vector2f(230, 150));

    sf::Text startGame2("Play Pacman", font, 30);
    startGame2.setFillColor(sf::Color::Black);
    startGame2.setPosition(sf::Vector2f(855, 150));

    sf::Text title("Arcade", font, 30);
    title.setFillColor(sf::Color::Black);
    title.setPosition(sf::Vector2f(580, 10));

    sf::Text quit("Quit", font, 30);
    quit.setFillColor(sf::Color::Black);
    quit.setPosition(sf::Vector2f(605, 575));

    sf::Text credits("Made by : Vincent Son, Gabriel Riboldi et Corentin Colsenet", font, 15);
    credits.setFillColor(sf::Color::Black);
    credits.setPosition(sf::Vector2f(0, 690));

    sf::RectangleShape buttonSnake;
    sf::RectangleShape buttonPacman;
    sf::RectangleShape buttonQuit;
    buttonSnake.setSize(sf::Vector2f(200, 100));
    buttonSnake.setPosition(sf::Vector2f(213, 125));
    buttonPacman.setSize(sf::Vector2f(200, 100));
    buttonPacman.setPosition(sf::Vector2f(852, 125));
    buttonQuit.setSize(sf::Vector2f(200, 100));
    buttonQuit.setPosition(sf::Vector2f(539, 550));

    std::string bestScore = getScore();

    sf::Text score_txt("Best Score: " + bestScore, font, 30);
    score_txt.setFillColor(sf::Color::Black);
    score_txt.setPosition(sf::Vector2f(50, 575));

    this->_menu.play();

    while (window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                this->window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
        sf::Mouse::getPosition(this->window).x >= buttonSnake.getPosition().x && sf::Mouse::getPosition(this->window).x <= buttonSnake.getPosition().x + buttonSnake.getSize().x &&
        sf::Mouse::getPosition(this->window).y >= buttonSnake.getPosition().y && sf::Mouse::getPosition(this->window).y <= buttonSnake.getPosition().y + buttonSnake.getSize().y) {
            this->_menu.stop();
            this->enterSound.play();
            this->nibbler = true;
            this->pacman = false;
            return (0);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
        sf::Mouse::getPosition(this->window).x >= buttonPacman.getPosition().x && sf::Mouse::getPosition(this->window).x <= buttonPacman.getPosition().x + buttonSnake.getSize().x &&
        sf::Mouse::getPosition(this->window).y >= buttonPacman.getPosition().y && sf::Mouse::getPosition(this->window).y <= buttonPacman.getPosition().y + buttonSnake.getSize().y) {
            this->_menu.stop();
            this->enterSound.play();
            this->pacman = true;
            this->nibbler = false;
            return (1);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
        sf::Mouse::getPosition(this->window).x >= buttonQuit.getPosition().x && sf::Mouse::getPosition(this->window).x <= buttonQuit.getPosition().x + buttonQuit.getSize().x &&
        sf::Mouse::getPosition(this->window).y >= buttonQuit.getPosition().y && sf::Mouse::getPosition(this->window).y <= buttonQuit.getPosition().y + buttonQuit.getSize().y) {
            this->_menu.stop();
            this->enterSound.play();
            return (-1);
        }
        this->window.clear(sf::Color(128, 0, 0, 255));
        this->window.draw(buttonSnake);
        this->window.draw(buttonPacman);
        this->window.draw(buttonQuit);
        this->window.draw(title);
        this->window.draw(credits);
        this->window.draw(startGame1);
        this->window.draw(startGame2);
        this->window.draw(quit);
        this->window.draw(score_txt);
        this->window.display();
    }
    return (-1);
}

void SFML::drawMap(std::string str, std::string gameName)
{
    std::string game = "./" + gameName + ".txt";
    std::string buffer, map;
    std::ifstream file;
    file.open(game);
    if(!file.is_open())
        std::cout << "Can't open file" << std::endl;
    while (file.is_open() && getline(file, buffer)) {
        map += buffer;
        map += '\n';
    };
    sf::Texture texture_wall;
    texture_wall.loadFromFile(str);
    sf::RectangleShape wall;
    wall.setSize(sf::Vector2f(32, 32));
    wall.setTexture(&texture_wall);
    int pos_x = 0;
    int pos_y = 0;
    
    this->window.clear();
    this->window.draw(this->spr_background);
    for (int i = 0; i != map.length(); i++) {
        if (map.at(i) == '\n') {
            pos_y += 32;
            pos_x = 0;
        }
        if (map.at(i) == '#') {
            wall.setPosition(sf::Vector2f(pos_x, pos_y));
            this->vect_walls.push_back(wall);
            pos_x += 32;
        } else if (map.at(i) == ' ' || map.at(i) == '.' || map.at(i) == 'X') {
            pos_x += 32;
        }
    }
    if (this->window.isOpen()) {
        sf::Event event;

        this->window.clear();
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                this->window.close();
        }
        for (auto it = this->vect_walls.cbegin(); it != this->vect_walls.cend(); it++) {
            this->window.draw(*it);
        }
    }
    this->vect_walls.clear();
}

std::string SFML::getScore() const
{
    std::string game = "scores.arcd";
    std::string buffer = "Unknown";
    std::ifstream file;
    file.open(game);
    if(!file.is_open())
        std::cout << "Can't open file score" << std::endl;
    while (!file.eof()) {
        getline(file, buffer);
        break;
    }
    return (buffer);
}

int SFML::gameover()
{
    if (this->nibbler) {
        this->overNibSound.play();
    } else if (this->pacman) {
        this->overPacSound.play();
    }
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");

    sf::String input;
    sf::Text inputText("", font, 40);
    inputText.setPosition(sf::Vector2f(425, 300));
    inputText.setFillColor(sf::Color::Black);

    sf::Text getInpt("Enter your name :", font, 30);
    getInpt.setPosition(sf::Vector2f(400, 200));
    getInpt.setFillColor(sf::Color::Black);

    sf::Text GameOver("YOU DIED", font, 75);
    GameOver.setFillColor(sf::Color(128, 0, 0, 255));
    GameOver.setOutlineColor(sf::Color::Black);
    GameOver.setOutlineThickness(5);
    // GameOver.setLetterSpacing(2);
    GameOver.setPosition(sf::Vector2f(425, 50));

    sf::Text restart("Restart", font, 30);
    restart.setFillColor(sf::Color::Black);
    restart.setPosition(sf::Vector2f(259, 400));

    sf::Text Menu("Menu", font, 30);
    Menu.setFillColor(sf::Color::Black);
    Menu.setPosition(sf::Vector2f(909, 400));

    sf::Text quit("Quit", font, 30);
    quit.setFillColor(sf::Color::Black);
    quit.setPosition(sf::Vector2f(605, 575));

    sf::RectangleShape buttonReplay;
    sf::RectangleShape buttonMenu;
    sf::RectangleShape buttonQuit;
    buttonReplay.setSize(sf::Vector2f(200, 100));
    buttonReplay.setPosition(sf::Vector2f(215, 375));
    buttonMenu.setSize(sf::Vector2f(200, 100));
    buttonMenu.setPosition(sf::Vector2f(855, 375));
    buttonQuit.setSize(sf::Vector2f(200, 100));
    buttonQuit.setPosition(sf::Vector2f(539, 550));

    while (this->window.isOpen()) {
        sf::Event event;

        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                this->window.close();
            if (event.type == sf::Event::TextEntered) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSpace) && input.getSize() > 0)
                    input.erase(input.getSize() - 1, 1);
                else
                    input += event.text.unicode;
                inputText.setString(input);
                this->scoreName = input;
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
        sf::Mouse::getPosition(this->window).x >= buttonMenu.getPosition().x && sf::Mouse::getPosition(this->window).x <= buttonMenu.getPosition().x + buttonMenu.getSize().x &&
        sf::Mouse::getPosition(this->window).y >= buttonMenu.getPosition().y && sf::Mouse::getPosition(this->window).y <= buttonMenu.getPosition().y + buttonMenu.getSize().y) {
            this->enterSound.play();
            return (10);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
        sf::Mouse::getPosition(this->window).x >= buttonReplay.getPosition().x && sf::Mouse::getPosition(this->window).x <= buttonReplay.getPosition().x + buttonReplay.getSize().x &&
        sf::Mouse::getPosition(this->window).y >= buttonReplay.getPosition().y && sf::Mouse::getPosition(this->window).y <= buttonReplay.getPosition().y + buttonReplay.getSize().y) {
            this->enterSound.play();
            return (4);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
        sf::Mouse::getPosition(this->window).x >= buttonQuit.getPosition().x && sf::Mouse::getPosition(this->window).x <= buttonQuit.getPosition().x + buttonQuit.getSize().x &&
        sf::Mouse::getPosition(this->window).y >= buttonQuit.getPosition().y && sf::Mouse::getPosition(this->window).y <= buttonQuit.getPosition().y + buttonQuit.getSize().y) {
            this->enterSound.play();
            return (0);
        }
        this->window.clear(sf::Color(128, 0, 0, 255));
        this->window.draw(buttonMenu);
        this->window.draw(buttonReplay);
        this->window.draw(Menu);
        this->window.draw(restart);
        this->window.draw(buttonQuit);
        this->window.draw(quit);
        this->window.draw(GameOver);
        this->window.draw(getInpt);
        this->window.draw(inputText);
        this->window.display();
    }
    return 0;
}

int SFML::getInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        return 3;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
        return 2;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
        return 0;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        return 1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
        return 4;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O))
        return 5;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
        return 6;
    else if (!this->window.isOpen() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        return 7;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
        return 8;
    else
        return -1;
}

void SFML::drawCharacters(const std::vector<ICharacter *> *chars)
{
    sf::RectangleShape character;
    character.setSize(sf::Vector2f(32, 32));
    std::vector<sf::RectangleShape> toDraw;
    sf::Texture texture;

    for (int i = 0; i < chars->size(); i++) {
        texture.loadFromFile(chars->at(i)->texture);
        character.setTexture(new sf::Texture(texture));
        character.setPosition(sf::Vector2f(chars->at(i)->getPosition().at(0), chars->at(i)->getPosition().at(1)));
        toDraw.push_back(character);
    }
    if (this->window.isOpen()) {
        sf::Event event;

        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                this->window.close();
        }
        for (auto it = toDraw.cbegin(); it != toDraw.cend(); it++) {
            this->window.draw(*it);
        }
    }
    toDraw.clear();
}

void SFML::drawScore(int score)
{
    if (this->musicScore < score) {
        if (this->nibbler) {
            this->appleSound.play();
        } else if (this->pacman) {
            this->eatSound.play();
        }
    }
    this->musicScore = score;
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    sf::Text text("SCORE : " + std::to_string(score) , font, 30);
    text.setFillColor(sf::Color::Red);
    text.setPosition(1280/2.0f, 680);
    text.setOrigin(text.getLocalBounds().left/2.0f,text.getLocalBounds().top/2.0f);
    this->window.draw(text);
    this->window.display();
}

SFML::~SFML()
{
    std::cout << "Stopping SFML" << std::endl;
    this->window.close();
}

extern "C" IDisplayModule *createLib() {
    std::cout << "Creating SFML" << std::endl;
    return new SFML();
}