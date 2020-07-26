/*
** EPITECH PROJECT, 2020
** SDL.cpp
** File description:
** SDL
*/

#include "SDL.hpp"

SDL::SDL()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    this->window = SDL_CreateWindow("Menu SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_RESIZABLE);
    this->rend = NULL;
    this->run = true;
    this->txt_pacman = NULL;
    this->txt_nibbler = NULL;
    this->txt_exit = NULL;
    this->texture_wall = NULL;
    this->txt_background = NULL;
    this->musicScore = 0;
    this->gameOver = false;
    init_button();
}

std::string SDL::getScore() const
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

void SDL::init_button()
{
    this->rend = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(this->rend, 255, 0, 0, 0.2);
    // Create img_nibbler
    this->img_background = IMG_Load("lib/img_nibbler/background.png");
    this->txt_background = SDL_CreateTextureFromSurface(this->rend, this->img_background);
    SDL_FreeSurface(this->img_background);
    // Create img_pacman
    this->img_back_pacman = IMG_Load("lib/img_pacman/background.png");
    this->txt_back_pacman = SDL_CreateTextureFromSurface(this->rend, this->img_back_pacman);
    SDL_FreeSurface(this->img_back_pacman);
    // Create button Pacman
    this->img_pacman = SDL_LoadBMP("lib/Pacman.bmp");
    this->txt_pacman = SDL_CreateTextureFromSurface(this->rend, this->img_pacman);
    SDL_FreeSurface(this->img_pacman);
    this->destPac.x = 200;
    this->destPac.y = 200;
    this->destPac.h = 150;
    this->destPac.w = 250;
    // Create button Nibbler
    this->img_nibbler = SDL_LoadBMP("lib/Nibbler.bmp");
    this->txt_nibbler = SDL_CreateTextureFromSurface(this->rend, this->img_nibbler);
    SDL_FreeSurface(this->img_nibbler);
    this->destNib.x = 800;
    this->destNib.y = 200;
    this->destNib.h = 150;
    this->destNib.w = 250;
    // Create Button Exit
    this->img_exit = SDL_LoadBMP("lib/Quit.bmp");
    this->txt_exit = SDL_CreateTextureFromSurface(this->rend, this->img_exit);
    SDL_FreeSurface(this->img_exit);
    this->destQuit.x = 600;
    this->destQuit.y = 500;
    this->destQuit.h = 100;
    this->destQuit.w = 100;
    // load song
    SDL_LoadWAV("./lib/song_nibbler/enter-game.wav", &this->enter, &this->enterBuffer, &this->enterLength);
    this->enterDevice = SDL_OpenAudioDevice(NULL, 0, &this->enter, NULL, 0);
    SDL_LoadWAV("./lib/song_nibbler/apple.wav", &this->apple, &this->appleBuffer, &this->appleLength);
    this->appleDevice = SDL_OpenAudioDevice(NULL, 0, &this->apple, NULL, 0);
    SDL_LoadWAV("./lib/menu.wav", &this->_menu, &this->menuBuffer, &this->menuLength);
    this->menuDevice = SDL_OpenAudioDevice(NULL, 0, &this->_menu, NULL, 0);
    SDL_LoadWAV("./lib/song_pacman/eat.wav", &this->eatPacman, &this->eatBuffer, &this->eatLength);
    this->eatDevice = SDL_OpenAudioDevice(NULL, 0, &this->eatPacman, NULL, 0);
    SDL_LoadWAV("./lib/song_pacman/dead.wav", &this->dead, &this->deadBuffer, &this->deadLength);
    this->deadDevice = SDL_OpenAudioDevice(NULL, 0, &this->dead, NULL, 0);
    SDL_LoadWAV("./lib/song_pacman/dead.wav", &this->deadSnake, &this->deadSnakeBuffer, &this->deadSnakeLength);
    this->deadSnakeDevice = SDL_OpenAudioDevice(NULL, 0, &this->deadSnake, NULL, 0);
}

int SDL::menu()
{
    SDL_Event event;

    int success = SDL_QueueAudio(this->enterDevice, this->enterBuffer, this->enterLength);
    int success_two = SDL_QueueAudio(this->menuDevice, this->menuBuffer, this->menuLength);
    SDL_PauseAudioDevice(this->menuDevice, 0);
    if (TTF_Init() == -1) {
        std::cout << "Error with TTF_Init" << std::endl; 
		this->run = false; 
	}
    std::string Font = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
    TTF_Font *font = NULL;
    font = TTF_OpenFont(Font.c_str(), 30);
    SDL_Color black = {0, 0, 0};
    SDL_Surface *text = TTF_RenderText_Solid(font, ("Best Score: " + getScore()).c_str(), black);
    SDL_Texture *message = SDL_CreateTextureFromSurface(this->rend, text);
    if (!message)
        std::cout << "Error Game Over Texture SDL" << std::endl;
    SDL_FreeSurface(text);
    SDL_Rect rct_message;
    rct_message.x = 50;
    rct_message.y = 575;
    rct_message.h = 60;
    rct_message.w = 300;
    while (this->run) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                this->run = false;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            this->posx = event.button.x;
            this->posy = event.button.y;
            // Look if the click is on the first button
            if (this->posx >= 201 && this->posx <= 449 && this->posy >= 202 && this->posy <= 348) {
                SDL_PauseAudioDevice(this->menuDevice, 1);
                SDL_PauseAudioDevice(this->enterDevice, 0);
                std::cout << "The game choosen is the Pacman" << std::endl;
                this->pacman = true;
                this->nibbler = false;
                return (1);
            }
            // Look if the click is on the second button
            else if (this->posx >= 805 && this->posx <= 1049 && this->posy >= 202 && this->posy <= 348) {
                SDL_PauseAudioDevice(this->menuDevice, 1);
                SDL_PauseAudioDevice(this->enterDevice, 0);
                std::cout << "The game choosen is the Snake" << std::endl;
                this->nibbler = true;
                this->pacman = false;
                return (0);
            }
            // Look if the click is on the third button
            else if (this->posx >= 600 && this->posx <= 696 && this->posy >= 503 && this->posy <= 596) {
                SDL_PauseAudioDevice(this->menuDevice, 1);
                std::cout << "The main menu is closed" << std::endl;
                run = false;
            }
        }
        SDL_RenderClear(this->rend);
        SDL_RenderCopy(this->rend, this->txt_pacman, NULL, &this->destPac);
        SDL_RenderCopy(this->rend, this->txt_nibbler, NULL, &this->destNib);
        SDL_RenderCopy(this->rend, this->txt_exit, NULL, &this->destQuit);
        SDL_RenderCopy(this->rend, message, NULL, &rct_message);
        SDL_RenderPresent(this->rend);
    }
    return (-1);
}

void SDL::drawMap(std::string str, std::string gameName)
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
    this->img_wall = IMG_Load(str.c_str());
	this->texture_wall = SDL_CreateTextureFromSurface(this->rend, this->img_wall);
    SDL_FreeSurface(this->img_wall);
    // sf::Texture texture_wall;
    // texture_wall.loadFromFile(str);
    this->destWall.h = 32;
    this->destWall.w = 32;
    // sf::RectangleShape wall;
    // wall.setSize(sf::Vector2f(32, 32));
    // wall.setTexture(&texture_wall);
    int pos_x = 0;
    int pos_y = 0;
    
    SDL_RenderClear(this->rend);
    if (!this->txt_background)
        std::cout << "ERROR" << std::endl;
    if (this->nibbler)
        SDL_RenderCopy(this->rend, this->txt_background, NULL, NULL);
    else if (this->pacman)
        SDL_RenderCopy(this->rend, this->txt_back_pacman, NULL, NULL);
    for (int i = 0; i != map.length(); i++) {
        if (map.at(i) == '\n') {
            pos_y += 32;
            pos_x = 0;
        }
        if (map.at(i) == '#') {
            this->destWall.x = pos_x;
            this->destWall.y = pos_y;
            SDL_RenderCopy(this->rend, this->texture_wall, NULL, &this->destWall);
            this->vect_walls.push_back(this->destWall);
            pos_x += 32;
        } else if (map.at(i) == ' ' || map.at(i) == '.' || map.at(i) == 'X') {
            pos_x += 32;
        }
    }
    if (this->run) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                this->run = false;
        }
    }
    this->vect_food.clear();
    this->vect_walls.clear();
}

int SDL::getInput()
{
    SDL_Event event;
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (!this->run || state[SDL_SCANCODE_ESCAPE])
        return (7);
    if (state[SDL_SCANCODE_W])
        return (0);
    if (state[SDL_SCANCODE_S])
        return (1);
    if (state[SDL_SCANCODE_A])
        return (2);
    if (state[SDL_SCANCODE_D])
        return (3);
    if (state[SDL_SCANCODE_P])
        return (6);
    if (state[SDL_SCANCODE_R])
        return (4);
    if (state[SDL_SCANCODE_O])
        return (5);
    if (state[SDL_SCANCODE_M])
        return (8);
    return (-1);
}

void SDL::drawCharacters(const std::vector<ICharacter *> *chars)
{
    SDL_Rect character;
    character.w = 32;
    character.h = 32;
    std::vector<SDL_Rect> toDraw;
    SDL_Surface *surface;
    SDL_Texture *texture;

    for (int i = 0; i < chars->size(); i++) {
        surface = IMG_Load(chars->at(i)->texture.c_str());
        texture = SDL_CreateTextureFromSurface(this->rend, surface);
        SDL_FreeSurface(surface);
        character.x = chars->at(i)->getPosition().at(0);
        character.y = chars->at(i)->getPosition().at(1);
        SDL_RenderCopy(this->rend, texture, NULL, &character);
        toDraw.push_back(character);
    }
    if (this->run) {
        SDL_Event event;

        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                this->run = false;
        }
    }
    toDraw.clear();
}

void SDL::drawScore(int score)
{
    if (TTF_Init() == -1) {
        std::cout << "Error with TTF_Init" << std::endl; 
		this->run = false; 
	}
    if (musicScore < score) {
        if (this->nibbler) {
            int success = SDL_QueueAudio(this->appleDevice, this->appleBuffer, this->appleLength);
            SDL_PauseAudioDevice(this->appleDevice, 0);
        } else if (this->pacman) {
            int success2 = SDL_QueueAudio(this->eatDevice, this->eatBuffer, this->eatLength);
            SDL_PauseAudioDevice(this->eatDevice, 0);
        }
    }
    musicScore = score;
    std::string Font = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
    TTF_Font *font = NULL;
    font = TTF_OpenFont(Font.c_str(), 30);
    SDL_Color red = {255, 0, 0};
    std::string Score = std::to_string(score);
    SDL_Surface *text = TTF_RenderText_Solid(font, ("SCORE : " + Score).c_str(), red);
    SDL_Texture *message = SDL_CreateTextureFromSurface(this->rend, text);
    if (!message)
        std::cout << "Error Score Texture SDL" << std::endl;
    SDL_FreeSurface(text);
    SDL_Rect rct_message;
    rct_message.x = 1280/2.0f;
    rct_message.y = 680;
    rct_message.h = 30;
    rct_message.w = 150;
    SDL_RenderCopy(this->rend, message, NULL, &rct_message);
    SDL_RenderPresent(this->rend);
}

int SDL::gameover()
{
    if (this->pacman) {
        int success = SDL_QueueAudio(this->deadDevice, this->deadBuffer, this->deadLength);
        SDL_PauseAudioDevice(this->deadDevice, 0);
    } else if (this->nibbler) {
        int success = SDL_QueueAudio(this->deadSnakeDevice, this->deadSnakeBuffer, this->deadSnakeLength);
        SDL_PauseAudioDevice(this->deadSnakeDevice, 0);
    }
    this->gameOver = true;
    SDL_RenderClear(this->rend);
    SDL_SetRenderDrawColor(this->rend, 255, 0, 0, 0.2);
    // Create button Menu
    this->img_restart = IMG_Load("lib/img_gameover/restart.png");
    this->txt_restart = SDL_CreateTextureFromSurface(this->rend, this->img_restart);
    SDL_FreeSurface(this->img_restart);
    this->destRestart.x = 200;
    this->destRestart.y = 200;
    this->destRestart.h = 150;
    this->destRestart.w = 250;
    // Create button Restart
    this->img_menu = IMG_Load("lib/img_gameover/menu.png");
    this->txt_menu = SDL_CreateTextureFromSurface(this->rend, this->img_menu);
    SDL_FreeSurface(this->img_menu);
    this->destMenu.x = 800;
    this->destMenu.y = 200;
    this->destMenu.h = 150;
    this->destMenu.w = 250;
    // Create Button Quit
    this->img_exit_over= IMG_Load("lib/img_gameover/quit.png");
    this->txt_exit_over = SDL_CreateTextureFromSurface(this->rend, this->img_exit_over);
    SDL_FreeSurface(this->img_exit_over);
    this->destQuitOver.x = 500;
    this->destQuitOver.y = 500;
    this->destQuitOver.h = 150;
    this->destQuitOver.w = 250;
    SDL_Event SecondEvent;

    if (TTF_Init() == -1) {
        std::cout << "Error with TTF_Init" << std::endl; 
		this->run = false; 
	}
    std::string Font = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
    TTF_Font *font = NULL;
    font = TTF_OpenFont(Font.c_str(), 30);
    SDL_Color black = {0, 0, 0};
    SDL_Surface *text = TTF_RenderText_Solid(font, "GAME OVER", black);
    SDL_Texture *message = SDL_CreateTextureFromSurface(this->rend, text);
    if (!message)
        std::cout << "Error Game Over Texture SDL" << std::endl;
    SDL_FreeSurface(text);
    SDL_Rect rct_message;
    rct_message.x = 500;
    rct_message.y = 40;
    rct_message.h = 60;
    rct_message.w = 300;
    SDL_RenderCopy(this->rend, message, NULL, &rct_message);
    while (this->gameOver) {
        while (SDL_PollEvent(&SecondEvent)) {
            if (SecondEvent.type == SDL_QUIT)
                this->gameOver = false;
        }
        if (SecondEvent.button.button == SDL_BUTTON_LEFT) {
            this->Secondposx = SecondEvent.button.x;
            this->Secondposy = SecondEvent.button.y;
            // std::cout << posx << "  " << posy << std::endl;
            // Look if the click is on the first button
            if (this->Secondposx >= 201 && this->Secondposx <= 449 && this->Secondposy >= 202 && this->Secondposy <= 348) {
                SDL_PauseAudioDevice(this->enterDevice, 0);
                return (4);
            }
            // Look if the click is on the second button
            else if (this->Secondposx >= 805 && this->Secondposx <= 1049 && this->Secondposy >= 202 && this->Secondposy <= 348) {
                SDL_PauseAudioDevice(this->enterDevice, 0);
                return (10);
            }
            // Look if the click is on the third button
            else if (this->Secondposx >= 500 && this->Secondposx <= 750 && this->Secondposy >= 500 && this->Secondposy <= 650) {
                return (0);
            }
        }
        SDL_RenderCopy(this->rend, this->txt_restart, NULL, &this->destRestart);
        SDL_RenderCopy(this->rend, this->txt_menu, NULL, &this->destMenu);
        SDL_RenderCopy(this->rend, this->txt_exit_over, NULL, &this->destQuitOver);
        SDL_RenderPresent(this->rend);
    }
    return (0);
}

SDL::~SDL()
{
    SDL_CloseAudioDevice(this->deadSnakeDevice);
    SDL_FreeWAV(this->deadSnakeBuffer);
    SDL_CloseAudioDevice(this->eatDevice);
    SDL_FreeWAV(this->eatBuffer);
    SDL_CloseAudioDevice(this->deadDevice);
    SDL_FreeWAV(this->deadBuffer);
    SDL_CloseAudioDevice(this->menuDevice);
    SDL_FreeWAV(this->menuBuffer);
    SDL_CloseAudioDevice(this->enterDevice);
    SDL_FreeWAV(this->enterBuffer);
    SDL_CloseAudioDevice(this->appleDevice);
    SDL_FreeWAV(this->appleBuffer);
    SDL_DestroyTexture(this->txt_pacman);
    SDL_DestroyTexture(this->txt_nibbler);
    SDL_DestroyTexture(this->txt_exit);
    SDL_DestroyTexture(this->txt_menu);
    SDL_DestroyTexture(this->txt_restart);
    SDL_DestroyTexture(this->txt_exit_over);
    SDL_DestroyTexture(this->texture_wall);
    SDL_DestroyTexture(this->txt_background);
    SDL_DestroyRenderer(this->rend);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

extern "C" IDisplayModule *createLib() {
    std::cout << "Creating SDL" << std::endl;
    return new SDL();
}