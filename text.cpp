#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "text.h"
#include "SDL/SDL.h"	
#include "SDL/SDL_ttf.h"

using namespace std;

TTF_Font * currFont;


void initFonts(std::string fontName, int size){
	TTF_Init();
	currFont = TTF_OpenFont(fontName.c_str(), size);
}

void changeFont(std::string fontName, int size){
	currFont = TTF_OpenFont(fontName.c_str(), size);
}

void drawtextutil(std::string text, SDL_Surface *surfDraw, int x, int y){
    SDL_Color tmpfontcolor = {0,0,0,0};
    SDL_Surface * textSurf = TTF_RenderText_Solid(currFont, text.c_str(), tmpfontcolor);
    SDL_Rect place;
	place.x = x;
    place.y = y;
	SDL_BlitSurface(textSurf, NULL, surfDraw, &place );
}