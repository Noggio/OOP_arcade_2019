/*
** EPITECH PROJECT, 2020
** nCurses.cpp
** File description:
** nCurses
*/

#include "nCurses.hpp"  

nCurses::nCurses()
{
    int maxX;
    int maxY;

    initscr();
    cbreak();
    noecho();
    getmaxyx(stdscr, maxY, maxX);
    this->window = newwin(maxY - 10, maxX - 10, 0, 0);
    wmove(this->window, 0, 0);
    box(this->window, 15, 15);
    wborder(this->window, 124, 124, 61, 61, 35, 35, 35, 35);
    keypad(this->window, true);
    refresh();
    wrefresh(this->window);
    //start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
}

std::string nCurses::getScore() const
{

}

nCurses::~nCurses()
{
    wclear(this->window);
    endwin();
}

int nCurses::menu()
{
    std::string choices[3] = {"Snake", "PacMan", "Exit"};
    std::string name = "Player";
    int highlight = 0;
    int best = 0;
    int input;
    int maxX;
    int maxY;

    wattron(this->window, COLOR_PAIR(1));
    getmaxyx(stdscr, maxY, maxX);
    mvwprintw(this->window, 0, (maxX / 2) - 8, "ARCADE");
    mvwprintw(this->window, 1, (maxX / 2) - 8, "NAME: Player");
    mvwprintw(this->window, 2, (maxX / 2) - 8, "BEST: %d", 0);
    wrefresh(this->window);
    while (1) {
        for (int i = 0; i < 3; i++) {
            if (i == highlight) {
                wattron(this->window, A_REVERSE);
            }
            mvwprintw(this->window, i+1, 2, choices[i].c_str());
            wattroff(this->window, COLOR_PAIR(1));
            wattroff(this->window, A_REVERSE);
        }
        input = wgetch(this->window);
        switch (input)
        {
        case KEY_UP:
            if (highlight > 0)
                highlight--;
            break;

        case KEY_DOWN:
            if (highlight < 2)
                highlight++;
            break;

        case KEY_BACKSPACE:
            if (name.length() > 0) {
                wclear(this->window);
                name.pop_back();
                box(this->window, 61, 61);
                wborder(this->window, 124, 124, 61, 61, 35, 35, 35, 35);
                mvwprintw(this->window, 0, (maxX / 2) - 8, "ARCADE");
                mvwprintw(this->window, 1, (maxX / 2) - 8, "NAME: ");
                mvwprintw(this->window, 2, (maxX / 2) - 8, "BEST: %d", best);
                mvwprintw(this->window, 1, (maxX / 2) - 2, name.c_str());
                wrefresh(this->window);
            }
            break;
        
        case 10: // ENTER
            if (highlight == 0) {
                clear();
                wclear(this->window);
                werase(this->window);
                delwin(this->window);
                this->window = newwin(45, 45, 0, 0);
                curs_set(0);
                keypad(this->window, true);
                refresh();
                wrefresh(this->window);
                printf("Playing Snake...\n");
                return (0);
            } else if (highlight == 1) {
                clear();
                wclear(this->window);
                werase(this->window);
                delwin(this->window);
                this->window = newwin(45, 45, 0, 0);
                curs_set(0);
                keypad(this->window, true);
                refresh();
                wrefresh(this->window);
                printf("Playing Pacman...\n");
                return (1);
            } else
                exit (0);
            break;
        
        default:
            if (name.length() < 15) {
                name.push_back(input);
                mvwprintw(this->window, 1, (maxX / 2) - 2, name.c_str());
            }
            break;
        }
        if (input == 4)
            break;
    }
    return (0);
}

void nCurses::drawMap(std::string unused, std::string gameName)
{
    wclear(this->window);
    wrefresh(this->window);
    std::string line;
    std::ifstream myfile("./" + gameName + ".txt");
    if (myfile.is_open())
    for (int i = 0; getline(myfile, line); i++)
        mvwprintw(this->window, i, 0, line.c_str());
    mvwprintw(this->window, 0, 3, "SCORE: ");
    wrefresh(this->window);
    myfile.close();
}

void nCurses::drawCharacters(const std::vector<ICharacter *> *chars)
{
    for (int i = 0; i < chars->size(); i++) {
        mvwprintw(this->window, (chars->at(i)->getPosition().at(1) / 32), (chars->at(i)->getPosition().at(0) / 32),  getPart(i));
        // PRINT THE APPLE POS :
        //mvwprintw(this->window, 3, 10, "y=%d x=%d i=%d\n", (chars->at(i)->getPosition().at(0) / 32), (chars->at(i)->getPosition().at(1) / 32), i);
        refresh();
        wrefresh(this->window);
    }
}

void nCurses::drawScore(int score)
{
    mvwprintw(this->window, 0, 3, "SCORE: %d", score);
    wrefresh(this->window);
}

int nCurses::getInput()
{
    int ch = 0;
    std::string letters = "";

    nodelay(this->window, true);
    ch = wgetch(this->window);
    letters.push_back(ch);
    refresh();
    wrefresh(this->window);
    if (letters == "D" || letters == "d") {
        letters = "";
        return 3;
    } else if (letters == "Q" || letters == "q") {
        letters = "";
        return 2;
    } else if (letters == "Z" || letters == "z") {
        letters = "";
        return 0;
    } else if (letters == "S" || letters == "s") {
        letters = "";
        return 1;
    } else if (letters == "P" || letters == "p") {
        letters = "";
        return 6;
    } else if (letters == "O" || letters == "o") {
        letters = "";
        return 5;
    } else if (letters == "R" || letters == "r") {
        letters = "";
        return 4;
    } else if (letters == "M" || letters == "m") {
        letters = "";
        return 8;
    } else if (ch == 27) { // ECHAP
        letters = "";
        return 7;
    } else
        return -1;
}

const char *nCurses::getPart(int part) const
{
    if (part == 0)
        return "O";
    else
        return "o";
}

int nCurses::gameover()
{
    std::string choices[3] = {"Retry", "Menu", "Exit"};
    std::string letters = "";
    std::string name = "";
    int highlight = 0;
    int input = 0;

    wclear(this->window);
    wrefresh(this->window);
    mvwprintw(this->window, 1, 1, "GAME OVER");
    mvwprintw(this->window, 2, 1, "NAME : %s", name.c_str());
    nodelay(this->window, false);
    while (1) {
        for (int i = 0; i < 3; i++) {
            if (i == highlight) {
                wattron(this->window, A_REVERSE);
            }
            mvwprintw(this->window, i+ 3, 2, choices[i].c_str());
            wattroff(this->window, COLOR_PAIR(1));
            wattroff(this->window, A_REVERSE);
        }
        input = wgetch(this->window);
        letters.push_back(input);
        mvwprintw(this->window, 2, 1, "NAME : %s", name.c_str());
        wrefresh(this->window);
        if (letters == "S" || letters == "s") {
            if (highlight <= 2) {
                letters = "";
                highlight++;
            }
        } else if (letters == "Z" || letters == "z") {
            if (highlight > 0) {
                letters = "";
                highlight--;
            }
        } else if (input == 27) {
            letters = "";
            exit (0);
        } else if (input == KEY_BACKSPACE) {
            if (name.length() > 0) {
                name.pop_back();
                wclear(this->window);
                mvwprintw(this->window, 1, 1, "GAME OVER");
                mvwprintw(this->window, 2, 1, "NAME : %s", name.c_str());
                for (int i = 0; i < 3; i++)
                    mvwprintw(this->window, i+ 3, 2, choices[i].c_str());
                wrefresh(this->window);
            }
        } else if (input == 10) { // ENTER
            this->scoreName = name;
            if (highlight == 0) {
                nodelay(this->window, true);
                return (4);
            } else if (highlight == 1) {
                return (10);
            } else
                exit (0);
        } else {
            if (name.length() < 15)
                name.push_back(input);
            letters = "";
            mvwprintw(this->window, 2, 1, "NAME : %s", name.c_str());
            wrefresh(this->window);
        }
    }
}

extern "C" IDisplayModule *createLib() {
    std::cout << "Creating nCurses" << std::endl;
    return new nCurses();
}