#include "play.h"
#include "Ltexture.h"
#include "header.h"

Ltexture background;
Ltexture dog;
Ltexture dog_lie;
Ltexture rat1;
Ltexture bird1;
Ltexture rat2;
Ltexture bird2;
Ltexture gameover;
Ltexture ScoreText;
Ltexture Button_Replay;
Ltexture Button_quit;
TTF_Font* ScoreFont;
Ltexture HighScoreText;

Mix_Music* gMusic = NULL;
Mix_Chunk* gJumpSound = NULL;
Mix_Chunk* gLieSound = NULL;
Mix_Chunk* gLevelUp = NULL;
Mix_Chunk* gGameOver = NULL;

int j = 0;
int i = 0;

int score = 0;

bool jump = false;
bool lie = false;

int type[1005];
int dis[1005];
int frame[1005];
int x[1005];


void loadMedia()
{

    // load background;
    dog.loadIMG(Figure_Run[Global::Character_number], Global::render, DOG_WIDTH * 6, DOG_HEIGHT, 6);
    dog_lie.loadIMG(Figure_Lie[Global::Character_number], Global::render, DOG_LIE_WIDTH, DOG_LIE_HEIGHT, 1);
    rat1.loadIMG(Figure_impediment[0], Global::render, rat_WIDTH * 4, rat_HEIGHT, 4);
    bird1.loadIMG(Figure_impediment[2], Global::render, bird_WIDTH * 6, bird_HEIGHT, 6);
    rat2.loadIMG(Figure_impediment[1], Global::render, rat_WIDTH * 4, rat_HEIGHT, 4);
    bird2.loadIMG(Figure_impediment[3], Global::render, bird_WIDTH * 6, bird_HEIGHT, 6);
    background.loadIMG(Scene[Global::Background_number], Global::render, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    
    //Handle animation
    dog.Handle_Clip();
    rat1.Handle_Clip();
    bird1.Handle_Clip();
    rat2.Handle_Clip();
    bird2.Handle_Clip();

    // Load music
    gMusic = Mix_LoadMUS( "sound/beat.wav" );
    
    //Load sound effects
    gJumpSound = Mix_LoadWAV( "sound/jump.wav" );
    gLieSound = Mix_LoadWAV("sound/lie.wav");
    gLevelUp = Mix_LoadWAV("Sound/LevelUp.mp3");
    gGameOver = Mix_LoadWAV("Sound/Gameover.wav");

    Mix_PlayMusic( gMusic, -1 );
}

void Play()
{
    
    int j = 0;
    int i = 0;

    int y = -DELTA;
    int z = 17;
    
    int dog_frame = 0;
    int DELAY = 30;
    
   int scrollingOffset = 0;

    std::ifstream file("score.txt");
    int highScore;
    file >> highScore;

    bool quit = false;
    bool pause = false;

    type[0] = 0;
    dis[0] = 1000;
    frame[0] = 0;
    x[0] = 0;
    
    loadMedia();

    while(!quit)
    {   
        // Scrolling map
        SDL_SetRenderDrawColor( Global::render, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( Global::render );
        SDL_Rect rect_data_1 = {scrollingOffset, 0, SCREEN_WIDTH-scrollingOffset, SCREEN_HEIGHT};
		SDL_Rect rect_data_2 = {0, 0, scrollingOffset, SCREEN_HEIGHT};

        background.Render(Global::render, 0, 0, &rect_data_1);
		background.Render(Global::render, SCREEN_WIDTH-scrollingOffset, 0, &rect_data_2);
        
        if(pause == false)
        {
		scrollingOffset += 5;
        if(scrollingOffset == SCREEN_WIDTH) scrollingOffset = 0;
        }
        
        //Score 
        if((score/15) % 100 == 0 && (score/15) != 0 && score%15 == 0)
        {
        Mix_PlayChannel(-1, gLevelUp, 0);
        ScoreFont = TTF_OpenFont("font/arial.ttf", 60);
        SDL_Color ScoreColor = {255, 255, 255};
        std::string text = "Score: " + convertItoStr(score/15);
        ScoreText.loadText(text , Global::render, 200, 50, ScoreFont, ScoreColor);
        ScoreText.Render(Global::render, 300, 0, NULL);
        }
        else
        {
        ScoreFont = TTF_OpenFont("font/arial.ttf", 20);
        SDL_Color ScoreColor = {255, 255, 255};
        std::string text = "Score: " + convertItoStr(score/15);
        ScoreText.loadText(text , Global::render, 100, 30, ScoreFont, ScoreColor);
        ScoreText.Render(Global::render, 300, 0, NULL);
        }

        if((score/15) <= highScore)
        {
            ScoreFont = TTF_OpenFont("font/arial.ttf", 30);
            SDL_Color ScoreColor = {255, 255, 255};
            std::string text = "High Score: " + convertItoStr(highScore);
            HighScoreText.loadText(text , Global::render, 150, 30, ScoreFont, ScoreColor);
            HighScoreText.Render(Global::render, 550, 0, NULL);
        }
        else
        {
            ScoreFont = TTF_OpenFont("font/arial.ttf", 30);
            SDL_Color ScoreColor = {255, 255, 255};
            std::string text = "High Score: " + convertItoStr(score/15);
            HighScoreText.loadText(text , Global::render, 150, 30, ScoreFont, ScoreColor);
            HighScoreText.Render(Global::render, 550, 0, NULL);
        }

       if(pause == false) score += 5;
        
        //Handle animation for dog
        if(lie == false)
        {
        SDL_Rect* dog_CurrentClip = &dog.clip[dog_frame];
        dog.Render(Global::render, DOG_COORDINATES_WIDTH, DOG_COORDINATES_HEIGHT - DELTA + abs(y), dog_CurrentClip);
        }
        else
        {
        dog_lie.Render(Global::render, DOG_LIE_COORDINATES_WIDTH, DOG_LIE_COORDINATES_HEIGHT, NULL);
        }

        if(jump == false)
        {
        if(pause == false)
        {
        ++dog_frame;
        if(dog_frame == dog.WALKING_ANIMATION_FRAMES) dog_frame = 0;
        }
        }
        

        //Handle animation for impediment
        PositionRect rect1;
        PositionRect rect2;

        if(lie == false)
            rect1.setup(DOG_COORDINATES_WIDTH, DOG_COORDINATES_HEIGHT-DELTA+abs(y), DOG_COORDINATES_WIDTH+DOG_WIDTH-1, DOG_COORDINATES_HEIGHT-DELTA+abs(y)+DOG_HEIGHT-1);
        else 
            rect1.setup(DOG_LIE_COORDINATES_WIDTH, DOG_LIE_COORDINATES_HEIGHT, DOG_LIE_COORDINATES_WIDTH+DOG_LIE_WIDTH-1, DOG_LIE_COORDINATES_HEIGHT+DOG_LIE_HEIGHT-1);

        for(int k = i; k <= j; ++k)
        {
            switch(type[k])
            {
                case 0: 
                {
                    SDL_Rect* rat1_CurrentClip = &rat1.clip[frame[k]];
                    rat1.Render(Global::render, dis[k]-x[k], rat_COORDINATES_HEIGHT, rat1_CurrentClip);

                    rect2.setup(dis[k]-x[k], rat_COORDINATES_HEIGHT, dis[k]-x[k]+rat_WIDTH-1, rat_COORDINATES_HEIGHT+rat_HEIGHT-1);

                    if(!UnCollision(rect1, rect2)) 
                    {
                        //Pause the music
                        Mix_PauseMusic();
                        quit = true;
                    }

                    if(pause == false)
                    {
                    ++frame[k];
                    if(frame[k] >= rat1.WALKING_ANIMATION_FRAMES) frame[k] = 0;
                    }
                    break;
                }

                case 1:
                {
                    SDL_Rect* rat2_CurrentClip = &rat2.clip[frame[k]];
                    rat2.Render(Global::render, dis[k]-x[k], rat_COORDINATES_HEIGHT, rat2_CurrentClip);

                    rect2.setup(dis[k]-x[k], rat_COORDINATES_HEIGHT, dis[k]-x[k]+rat_WIDTH-1, rat_COORDINATES_HEIGHT+rat_HEIGHT-1);

                    if(!UnCollision(rect1, rect2)) 
                    {
                        //Pause the music
                        Mix_PauseMusic();
                        quit = true;
                    }

                    if(pause == false)
                    {
                    ++frame[k];
                    if(frame[k] >= rat2.WALKING_ANIMATION_FRAMES) frame[k] = 0;
                    }
                    break;
                }

                case 2:
                {
                    SDL_Rect* bird1_CurrentClip = &bird1.clip[frame[k]];
                    bird1.Render(Global::render, dis[k]-x[k], bird_COORDINATES_HEIGHT, bird1_CurrentClip);

                    rect2.setup(dis[k]-x[k], bird_COORDINATES_HEIGHT, dis[k]-x[k]+bird_WIDTH-1, bird_COORDINATES_HEIGHT+bird_HEIGHT-1);

                    if(!UnCollision(rect1, rect2)) 
                    {
                        //Pause the music
                        Mix_PauseMusic();
                        quit = true;
                    }
                    
                    if(pause == false)
                    {
                    ++frame[k];
                    if(frame[k] >= bird1.WALKING_ANIMATION_FRAMES) frame[k] = 0;
                    }
                    break;
                }

                case 3:
                {
                    SDL_Rect* bird2_CurrentClip = &bird2.clip[frame[k]];
                    bird2.Render(Global::render, dis[k]-x[k], bird_COORDINATES_HEIGHT, bird2_CurrentClip);

                    rect2.setup(dis[k]-x[k], bird_COORDINATES_HEIGHT, dis[k]-x[k]+bird_WIDTH-1, bird_COORDINATES_HEIGHT+bird_HEIGHT-1);

                    if(!UnCollision(rect1, rect2)) 
                    {
                        //Pause the music
                        Mix_PauseMusic();
                        quit = true;
                    }

                    if(pause == false)
                    {
                    ++frame[k];
                    if(frame[k] >= bird2.WALKING_ANIMATION_FRAMES) frame[k] = 0;
                    }
                    break;
                }
            }
            if(quit == true) break;
            if(pause == false) x[k] += 10;
        }
        
        //xu ly phan sinh ra chuong ngai vat
        if(dis[i]-x[i] < 0) ++i;
        if(dis[j] - x[j] <= SCREEN_WIDTH && dis[j] - x[j] + 10 >= SCREEN_WIDTH)
        {
            ++j;
            type[j] = rand()%4;
            dis[j] = rand()%201 + 1600;
            frame[j] = 0;
            x[j] = 0;
        }

        SDL_RenderPresent(Global::render);
       
        if(quit == false) 
        {   
            // xu ly tang do kho cho game
            if((score/15) % 100 == 0 && (score/15) != 0 && score%15 == 0)
                if(DELAY >= 10) DELAY -= 2;
            SDL_Delay(DELAY);
        }
        else 
        {   
            //gameover
            SDL_Delay(200);
            break;
        }

        if(SDL_PollEvent(&Global::e) != 0)
        {
            if( Global::e.type == SDL_QUIT || (Global::e.type == SDL_KEYDOWN && Global::e.key.keysym.sym == SDLK_RETURN))
            {
                //Stop the music
                Mix_HaltMusic();
                quit = true;
            }

            if(Global::e.type == SDL_KEYDOWN && Global::e.key.keysym.sym == SDLK_UP)
            {
                if(jump == false)
                {
                    jump = true;
                    y = -DELTA;
                    z = 17;
                    dog_frame = 4;
                    //Play sound effect
                    Mix_PlayChannel( -1, gJumpSound, 0 );
                }
            }

            if(Global::e.type == SDL_KEYDOWN && Global::e.key.keysym.sym == SDLK_DOWN)
            {
                if(lie == false)
                {
                    lie = true;
                    jump = false;
                    y = -DELTA;
                    z = 17;
                    Mix_PlayChannel(-1, gLieSound, 0);
                }
            }

            if(Global::e.type == SDL_KEYDOWN && Global::e.key.keysym.sym == SDLK_ESCAPE)
            {
                Mix_PlayChannel(-1, Global::click, 0);
                if(pause == false)
                {
                    Mix_PauseMusic();
                    pause = true;
                }
                else
                { 
                    Mix_ResumeMusic();
                    pause = false;
                }
            }

            if(Global::e.type == SDL_KEYUP && Global::e.key.keysym.sym == SDLK_DOWN)
            {
                lie = false;
            }

        }

        if(jump == true)
        {
            if(pause == false)
            {
            y += abs(z);
            --z;
            if(y == DELTA) 
            {
                jump = false;
                y = -DELTA;
            }
            if(y == 0)
            {
                dog_frame = 5;
            }
            }
        }

    }
    if(score/15 > highScore)
    {
        std::ofstream out("score.txt");
        out << score/15;
    }
}

void End()
{
    Button_quit.loadIMG("img/button/quit.png", Global::render, 200, 75, 1);
    Button_Replay.loadIMG("img/button/replay.png", Global::render, 200, 75, 1);

    std::ifstream file("score.txt");
    int highScore;
    file >> highScore;
    
    background.loadIMG(Scene[0], Global::render, SCREEN_WIDTH, SCREEN_HEIGHT, 1);

    bool quit = false;
    bool ok = true;
    while(!quit)
    {
        if(ok == true)
        {
            Mix_PlayChannel(-1, gGameOver, 0);
            ok = false;
        }    
        SDL_SetRenderDrawColor( Global::render, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( Global::render );
        background.Render(Global::render, 0, 0, NULL);
        gameover.loadIMG("img/gameover.png", Global::render, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, 1);
        gameover.Render(Global::render, GAMEOVER_COORDINATES_WIDTH, GAMEOVER_COORDINATES_HEIGHT, NULL);

        Button_Replay.Render(Global::render, 250, 450, NULL);
        Button_quit.Render(Global::render, 550, 450, NULL);
        SDL_Rect rect_1 = {250, 450, 200, 75};
        SDL_Rect rect_2 = {550, 450, 200, 75};

        ScoreFont = TTF_OpenFont("font/arial.ttf", 40);
        SDL_Color ScoreColor = {0, 0, 0};
        std::string text = "Score: " + convertItoStr(score/15);
        ScoreText.loadText(text , Global::render, 100, 30, ScoreFont, ScoreColor);
        ScoreText.Render(Global::render, 450, 345, NULL);

        text = "High Score: " + convertItoStr(highScore);
        HighScoreText.loadText(text , Global::render, 150, 30, ScoreFont, ScoreColor);
        HighScoreText.Render(Global::render, 425, 300, NULL);

        SDL_RenderPresent(Global::render);

        while(SDL_PollEvent(&Global::e) != 0)
        {
            if(Global::e.type == SDL_QUIT) 
            {
                quit = true;
                Global::REPLAY = false;
            }
            if(Global::e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(Global::e.button.x >= rect_1.x && Global::e.button.x <= rect_1.x + rect_1.w &&
                Global::e.button.y >= rect_1.y && Global::e.button.y <= rect_1.y + rect_1.h)
                {
                    Global::REPLAY = true;
                    Mix_PlayChannel(-1, Global::click, 0);
                    quit = true;
                }
                if (Global::e.button.x >= rect_2.x && Global::e.button.x <= rect_2.x + rect_2.w &&
                Global::e.button.y >= rect_2.y && Global::e.button.y <= rect_2.y + rect_2.h)
                {
                    Global::REPLAY = false;
                    Mix_PlayChannel(-1, Global::click, 0);
                    quit = true;
                }
            }
        }
    }
}

void FreePlay()
{
    background.Free();
    dog.Free();
    dog_lie.Free();
    rat1.Free();
    bird1.Free();
    rat2.Free();
    bird2.Free();
    gameover.Free();
    ScoreText.Free();
    Button_Replay.Free();
    Button_quit.Free();
    HighScoreText.Free();
    TTF_CloseFont(ScoreFont);

    Mix_FreeMusic(gMusic);
    Mix_FreeChunk(gJumpSound);
    Mix_FreeChunk(gLieSound);
    Mix_FreeChunk(gLevelUp);
    Mix_FreeChunk(gGameOver);

    gMusic = NULL;
    gJumpSound = NULL;
    gLieSound = NULL;
    gLevelUp = NULL;
    gGameOver = NULL;

    j = 0;
    i = 0;

    score = 0;

    jump = false;
    lie = false;

}