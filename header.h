#ifndef HEADER_H
#define HEADER_H

class Global {
    public:
    static SDL_Window* window;
    static SDL_Renderer* render;
    static SDL_Event e;
    static int Background_number;
    static int Character_number;
    static bool REPLAY;
    static Mix_Chunk* click;
};

const std::string Scene[6] = {
    "img/background/background_0.png",
    "img/background/background_1.png",
    "img/background/background_2.png",
    "img/background/background_3.png",
    "img/background/background_4.png",
    "img/background/background_5.png"
};

const std::string Figure_Run[4] = {
       "img/figure_Run/dog_0.png",
       "img/figure_Run/dog_1.png",
       "img/figure_Run/dog_2.png",
       "img/figure_Run/dog_3.png"
};

const std::string Figure_Idle[4] = {
       "img/figure_Idle/Idle_0.png",
       "img/figure_Idle/Idle_1.png",
       "img/figure_Idle/Idle_2.png",
       "img/figure_Idle/Idle_3.png",
};

const std::string Figure_Lie[4] = {
       "img/figure_Lie/lie_0.png",
       "img/figure_Lie/lie_1.png",
       "img/figure_Lie/lie_2.png",
       "img/figure_Lie/lie_3.png",
};

const std::string Figure_impediment[4] = {
       "img/impediment/rat1.png",
       "img/impediment/rat2.png",
       "img/impediment/bird1.png",
       "img/impediment/bird2.png",
};

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 563;

const int DOG_WIDTH = 120;
const int DOG_HEIGHT = 120;

const int DOG_LIE_WIDTH = 120;
const int DOG_LIE_HEIGHT = 30;

const int rat_WIDTH = 100;
const int rat_HEIGHT = 30;

const int bird_WIDTH = 75;
const int bird_HEIGHT = 75;

const int GAMEOVER_WIDTH = 311;
const int GAMEOVER_HEIGHT = 162;

const int WINNER_WIDTH = 360;
const int WINNER_HEIGHT = 360;

const int DOG_COORDINATES_WIDTH = 200;
const int DOG_COORDINATES_HEIGHT = 390;

const int DOG_LIE_COORDINATES_WIDTH = 200;
const int DOG_LIE_COORDINATES_HEIGHT = 480;

const int rat_COORDINATES_HEIGHT = 479;

const int bird_COORDINATES_HEIGHT = 390;

const int GAMEOVER_COORDINATES_WIDTH = 335;
const int GAMEOVER_COORDINATES_HEIGHT = 100;

const int WINNER_COORDINATES_WIDTH = 300;
const int WINNER_COORDINATES_HEIGHT = 100;

const int DELTA = 153;


#endif