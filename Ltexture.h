#ifndef LTEXTURE_H_
#define LTEXTURE_H_

#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

class Ltexture
{
    private:
        int w ,h;
        SDL_Texture* texture;

    public:
        int WALKING_ANIMATION_FRAMES;
        SDL_Rect clip[6];
        Ltexture();
        ~Ltexture();
        bool loadIMG(std::string path, SDL_Renderer* screen, int _w, int _h, int animation_frame);
        bool loadText(std::string text, SDL_Renderer* screen, int _w, int _h, TTF_Font* Font, SDL_Color);
        void Render(SDL_Renderer* screen, int x, int y, SDL_Rect* RectClip);
        void Free();
        void Handle_Clip();
};

struct PositionRect
{
     int x1, y1, x2, y2;
     PositionRect(int _x1, int _y1, int _x2, int _y2)
     {
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;
     }
     void setup(int _x1, int _y1, int _x2, int _y2);
     PositionRect(){};
};
bool UnCollision(PositionRect rect1, PositionRect rect2);

std::string convertItoStr(int x);
#endif 

