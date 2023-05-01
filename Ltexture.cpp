#include "Ltexture.h"

Ltexture::Ltexture()
{
    texture = NULL;
    w = 0;
    h = 0;
}

Ltexture::~Ltexture()
{
    Free();
}

bool Ltexture::loadIMG(std::string path, SDL_Renderer* screen, int _w, int _h, int animation_frame)
{
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if(load_surface != NULL)
    {
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB( load_surface->format, 255, 255, 255));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if(new_texture != NULL)
        {
            w = _w;
            h = _h;
            WALKING_ANIMATION_FRAMES = animation_frame;
        }
        SDL_FreeSurface(load_surface);
    }
    texture = new_texture;
    return texture != NULL;
}

bool Ltexture::loadText(std::string text, SDL_Renderer* screen, int _w, int _h, TTF_Font* Font, SDL_Color textColor)
{
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = TTF_RenderText_Solid( Font, text.c_str(), textColor );
    if(load_surface != NULL)
    {
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if(new_texture != NULL)
        {
            w = _w;
            h = _h;
        }
        SDL_FreeSurface(load_surface);
    }
    texture = new_texture;
    return texture != NULL;
}

void Ltexture::Render(SDL_Renderer* screen, int x, int y, SDL_Rect* RectClip)
{
    SDL_Rect rect = {x, y, w, h};
    if( RectClip != NULL )
	{
		rect.w = RectClip->w;
		rect.h = RectClip->h;
	}
    SDL_RenderCopy(screen, texture, RectClip, &rect);
}

void Ltexture::Free()
{
    if(texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
        w = 0;
        h = 0;
        for(int i = 0; i < WALKING_ANIMATION_FRAMES; ++i)
        {
            clip[i].x = 0;
            clip[i].y = 0;
            clip[i].w = 0;
            clip[i].h = 0;
        }
        WALKING_ANIMATION_FRAMES = 0;
    }
}

void Ltexture::Handle_Clip()
{   
    int value = 0;
    for(int i = 0; i < WALKING_ANIMATION_FRAMES; ++i)
    {
        clip[i].x = value;
        clip[i].y = 0;
        clip[i].w = w/WALKING_ANIMATION_FRAMES;
        clip[i].h = h;
        value += w/WALKING_ANIMATION_FRAMES;
    }
}

void PositionRect :: setup(int _x1, int _y1, int _x2, int _y2)
{
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;
}

bool UnCollision(PositionRect rect1, PositionRect rect2)
{
    if(rect1.x2 <= rect2.x1 || rect1.y2 <= rect2.y1 || rect1.x1 >= rect2.x2 || rect1.y1 >= rect2.y2) return true;
    return false;
}

std::string convertItoStr(int x)
{
    if(x == 0) return "0";
    std::string answer = "";
    while(x > 0)
    {
        int y = x%10;
        answer = char(y + '0') + answer;
        x /= 10;
    }
    return answer;
}
