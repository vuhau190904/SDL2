#include "Ltexture.h"
#include "header.h"
#include "menu.h"
#include "play.h"

SDL_Window* Global::window = NULL;
SDL_Renderer* Global::render = NULL;
SDL_Event Global::e;
Mix_Chunk* Global::click = NULL;

int Global::Character_number = -1;
int Global::Background_number = -1;
bool Global::REPLAY = false;

void init()
{
    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Set texture filtering to linear
        if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        //Create window
        Global::window = SDL_CreateWindow("Hau tap lam game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(Global::window == NULL)
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Create renderer for window
            Global::render = SDL_CreateRenderer(Global::window, -1, SDL_RENDERER_ACCELERATED);
            if(Global::render == NULL)
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(Global::render, 0xFF, 0xFF, 0xFF, 0xFF);
                 
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                }

                //Initialize SDL_mixer
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                }

                 //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                }
            }
        }
    }
    Global::click = Mix_LoadWAV("Sound/click.wav");
}


void close()
{
    Mix_FreeChunk(Global::click);

    Global::click = NULL;

    SDL_DestroyWindow(Global::window);
    SDL_DestroyRenderer(Global::render);
    Global::window = NULL;
    Global::render = NULL;

    Global::Character_number = -1;
    Global::Background_number = -1;

    Global::REPLAY = false;

    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}



int main()
{
    init();
    L:
    if(HandleMenu())
    {
    Play();
    End();
    FreePlay();
    FreeMenu();
    if(Global::REPLAY == true) goto L;
    }
    close();
    
}


