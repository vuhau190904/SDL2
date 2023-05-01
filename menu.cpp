#include "Ltexture.h"
#include "menu.h"
#include "header.h"

Ltexture ChooseBackground[6];
Ltexture Idle_0;
Ltexture Idle_1;
Ltexture Idle_2;
Ltexture Idle_3;
Ltexture border_character;
Ltexture border_background;
Ltexture Menu_Button_start;
Ltexture Menu_Button_quit;
Ltexture CharacterMenuText;
Ltexture BackgroundMenuText;
Ltexture welcomeText;
TTF_Font* MenuFont;
SDL_Color MenuTextColor = {255, 188, 190};

void loadImgMenu()
{
    border_character.loadIMG("img/figure_Idle/border_character.png", Global::render, 220, 220, 1);
    border_background.loadIMG("img/background/border_background.png", Global::render, 301, 195, 1);

    Idle_0.loadIMG(Figure_Idle[0], Global::render, 160, 160, 1);
    Idle_1.loadIMG(Figure_Idle[1], Global::render, 160, 160, 1);
    Idle_2.loadIMG(Figure_Idle[2], Global::render, 160, 160, 1);
    Idle_3.loadIMG(Figure_Idle[3], Global::render, 160, 160, 1);

    Menu_Button_quit.loadIMG("img/button/quit.png", Global::render, 200, 75, 1);
    Menu_Button_start.loadIMG("img/button/playnow.png", Global::render, 200, 75, 1);

    ChooseBackground[0].loadIMG(Scene[0], Global::render, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    for(int i = 1; i <= 5; ++i)
    {
        ChooseBackground[i].loadIMG(Scene[i], Global::render, 220, 124, 1);
    }

    MenuFont = TTF_OpenFont("font/lazy.ttf", 70);    
}

bool start_game()
{   
    if(Global::REPLAY == true) return 1;
    MenuFont = TTF_OpenFont("font/lazy.ttf", 100);   
    welcomeText.loadText("Welcome to my game", Global::render, 600, 150, MenuFont, MenuTextColor);
    MenuFont = TTF_OpenFont("font/lazy.ttf", 70);   
    bool quit = false;
    while(!quit)
    {
        SDL_SetRenderDrawColor(Global::render, 255, 255, 255, 255);
        SDL_RenderClear(Global::render);

        ChooseBackground[0].Render(Global::render, 0, 0, NULL);
        welcomeText.Render(Global::render, 200, 20, NULL);
        Menu_Button_start.Render(Global::render, 400, 200, NULL);
        Menu_Button_quit.Render(Global::render, 400, 300, NULL);

        SDL_Rect rect_1 = {400, 200, 200, 75};
        SDL_Rect rect_2 = {400, 300, 200, 75};

        SDL_RenderPresent(Global::render);
        while(SDL_PollEvent(&Global::e) != 0)
        {
            if(Global::e.type == SDL_QUIT) return 0;
            if(Global::e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(Global::e.button.x >= rect_1.x && Global::e.button.x <= rect_1.x + rect_1.w &&
                Global::e.button.y >= rect_1.y && Global::e.button.y <= rect_1.y + rect_1.h)
                {
                    Mix_PlayChannel(-1, Global::click, 0);
                    return 1;
                }
                if (Global::e.button.x >= rect_2.x && Global::e.button.x <= rect_2.x + rect_2.w &&
                Global::e.button.y >= rect_2.y && Global::e.button.y <= rect_2.y + rect_2.h)
                {
                    Mix_PlayChannel(-1, Global::click, 0);
                    return 0;
                }
            }
        }
    }
    return 1;
}

bool Character_Menu()
{
    CharacterMenuText.loadText("Choose a character", Global::render, 600, 90, MenuFont, MenuTextColor);

    bool quit = false;
    while(!quit)
    {
    SDL_SetRenderDrawColor(Global::render, 255, 255, 255, 255);
    SDL_RenderClear(Global::render);
    ChooseBackground[0].Render(Global::render, 0, 0, NULL);

    Idle_0.Render(Global::render, 135, 200, NULL);
    Idle_1.Render(Global::render, 335, 200, NULL);
    Idle_2.Render(Global::render, 535, 200, NULL);
    Idle_3.Render(Global::render, 745, 200, NULL);

    CharacterMenuText.Render(Global::render, 220, 30, NULL);
    
    SDL_Rect rect_0 = { 135, 200, 150, 150 };
    SDL_Rect rect_1 = { 335, 200, 150, 150 };
    SDL_Rect rect_2 = { 535, 200, 150, 150 };
    SDL_Rect rect_3 = { 745, 200, 150, 150 };

    
    
    while(SDL_PollEvent(&Global::e) != 0)
    {   
        if(Global::e.type == SDL_MOUSEMOTION)
        {
           if (Global::e.button.x >= rect_0.x && Global::e.button.x <= rect_0.x + rect_0.w &&
                Global::e.button.y >= rect_0.y && Global::e.button.y <= rect_0.y + rect_0.h)
            {
                    border_character.Render(Global::render, 100, 210, NULL);
                    SDL_Delay(100);
            }

           if (Global::e.button.x >= rect_1.x && Global::e.button.x <= rect_1.x + rect_1.w &&
                Global::e.button.y >= rect_1.y && Global::e.button.y <= rect_1.y + rect_1.h)
            {
                    border_character.Render(Global::render, 300, 210, NULL);
                    SDL_Delay(100);
            }
                    
           
           if (Global::e.button.x >= rect_2.x && Global::e.button.x <= rect_2.x + rect_2.w &&
                Global::e.button.y >= rect_2.y && Global::e.button.y <= rect_2.y + rect_2.h)
            {
                    border_character.Render(Global::render, 500, 210, NULL);
                    SDL_Delay(100);
            }

           if (Global::e.button.x >= rect_3.x && Global::e.button.x <= rect_3.x + rect_3.w &&
                Global::e.button.y >= rect_3.y && Global::e.button.y <= rect_3.y + rect_3.h)
            {
                    border_character.Render(Global::render, 700, 210, NULL);
                    SDL_Delay(100);
            }
        }

        if(Global::e.type == SDL_MOUSEBUTTONDOWN)
        {
           if (Global::e.button.x >= rect_0.x && Global::e.button.x <= rect_0.x + rect_0.w &&
                Global::e.button.y >= rect_0.y && Global::e.button.y <= rect_0.y + rect_0.h)
            {
                    Global::Character_number = 0;
                    border_character.Render(Global::render, 100, 210, NULL);
                    Mix_PlayChannel(-1, Global::click, 0);
                    SDL_Delay(100);
                    quit = true;
                    break;
            }

           if (Global::e.button.x >= rect_1.x && Global::e.button.x <= rect_1.x + rect_1.w &&
                Global::e.button.y >= rect_1.y && Global::e.button.y <= rect_1.y + rect_1.h)
            {
                    Global::Character_number = 1;
                    border_character.Render(Global::render, 300, 210, NULL);
                    Mix_PlayChannel(-1, Global::click, 0);
                    SDL_Delay(100);
                    quit = true;
                    break;
            }
                    
           
           if (Global::e.button.x >= rect_2.x && Global::e.button.x <= rect_2.x + rect_2.w &&
                Global::e.button.y >= rect_2.y && Global::e.button.y <= rect_2.y + rect_2.h)
            {
                    Global::Character_number = 2;
                    border_character.Render(Global::render, 500, 210, NULL);
                    Mix_PlayChannel(-1, Global::click, 0);
                    SDL_Delay(100);
                    quit = true;
                    break;
            }

           if (Global::e.button.x >= rect_3.x && Global::e.button.x <= rect_3.x + rect_3.w &&
                Global::e.button.y >= rect_3.y && Global::e.button.y <= rect_3.y + rect_3.h)
            {
                    Global::Character_number = 3;
                    border_character.Render(Global::render, 700, 210, NULL);
                    Mix_PlayChannel(-1, Global::click, 0);
                    SDL_Delay(100);
                    quit = true;
                    break;
            }
        }
        if(Global::e.type == SDL_QUIT) return 0;  
    }
    SDL_RenderPresent(Global::render);
    }
    return 1;
}

bool Background_Menu()
{
    BackgroundMenuText.loadText("Choose a background", Global::render, 600, 90, MenuFont, MenuTextColor);

    bool quit = false;
    while(!quit)
    {
    SDL_SetRenderDrawColor(Global::render, 255, 255, 255, 255);
    SDL_RenderClear(Global::render);

    ChooseBackground[0].Render(Global::render, 0, 0, NULL);

    border_background.Render(Global::render, 20, 125, NULL);
    border_background.Render(Global::render, 680, 125, NULL);
    border_background.Render(Global::render, 350, 240, NULL);
    border_background.Render(Global::render, 20, 355, NULL);
    border_background.Render(Global::render, 680, 355, NULL);

    ChooseBackground[1].Render(Global::render, 60, 160, NULL);
    ChooseBackground[2].Render(Global::render, 720, 160, NULL);
    ChooseBackground[3].Render(Global::render, 390, 275, NULL);
    ChooseBackground[4].Render(Global::render, 60, 390, NULL);
    ChooseBackground[5].Render(Global::render, 720, 390, NULL);

    BackgroundMenuText.Render(Global::render, 220, 30, NULL);
    
    SDL_Rect rect_1 = { 60, 160, 220, 124 };
    SDL_Rect rect_2 = { 720, 160, 220, 124 };
    SDL_Rect rect_3 = { 390, 275, 220, 124 };
    SDL_Rect rect_4 = { 60, 390, 220, 124 };
    SDL_Rect rect_5 = { 720, 390, 220, 124 };

    
    
    while(SDL_PollEvent(&Global::e) != 0)
    {   
        if(Global::e.type == SDL_MOUSEBUTTONDOWN)
        {
           if (Global::e.button.x >= rect_5.x && Global::e.button.x <= rect_5.x + rect_5.w &&
                Global::e.button.y >= rect_5.y && Global::e.button.y <= rect_5.y + rect_5.h)
            {
                    Global::Background_number = 5;
                    Mix_PlayChannel(-1, Global::click, 0);
                    quit = true;
                    break;
            }

           if (Global::e.button.x >= rect_1.x && Global::e.button.x <= rect_1.x + rect_1.w &&
                Global::e.button.y >= rect_1.y && Global::e.button.y <= rect_1.y + rect_1.h)
            {
                    Global::Background_number = 1;
                    Mix_PlayChannel(-1, Global::click, 0);
                    quit = true;
                    break;
            }
                    
           
           if (Global::e.button.x >= rect_2.x && Global::e.button.x <= rect_2.x + rect_2.w &&
                Global::e.button.y >= rect_2.y && Global::e.button.y <= rect_2.y + rect_2.h)
            {
                    Global::Background_number = 2;
                    Mix_PlayChannel(-1, Global::click, 0);
                    quit = true;
                    break;
            }

           if (Global::e.button.x >= rect_3.x && Global::e.button.x <= rect_3.x + rect_3.w &&
                Global::e.button.y >= rect_3.y && Global::e.button.y <= rect_3.y + rect_3.h)
            {
                    Global::Background_number = 3;
                    Mix_PlayChannel(-1, Global::click, 0);
                    quit = true;
                    break;
            }
           if (Global::e.button.x >= rect_4.x && Global::e.button.x <= rect_4.x + rect_4.w &&
                Global::e.button.y >= rect_4.y && Global::e.button.y <= rect_4.y + rect_4.h)
            {
                    Global::Background_number = 4;
                    Mix_PlayChannel(-1, Global::click, 0);
                    quit = true;
                    break;
            }
        }
        if(Global::e.type == SDL_QUIT) return 0;  
    }
    SDL_RenderPresent(Global::render);
    }
    return 1;
}

bool HandleMenu()
{
    
    loadImgMenu();
    if(!start_game()) return 0;
    if(!Character_Menu()) return 0;
    if(!Background_Menu()) return 0;
    return 1;
}

void FreeMenu()
{
    for(int i = 0; i <= 5; ++i)
        ChooseBackground[i].Free();
    Idle_0.Free();
    Idle_1.Free();
    Idle_2.Free();
    Idle_3.Free();
    border_character.Free();
    border_background.Free();
    Menu_Button_start.Free();
    Menu_Button_quit.Free();
    CharacterMenuText.Free();
    BackgroundMenuText.Free();
    welcomeText.Free();
    TTF_CloseFont(MenuFont);
    MenuFont = NULL;
}
